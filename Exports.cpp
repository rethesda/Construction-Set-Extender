#include "[Common]\ComponentDLLInterface.h"
#include "[Common]\CLIWrapper.h"

#include "WindowManager.h"
#include "Hooks\CompilerErrorDetours.h"
#include "Hooks\Misc.h"
#include "Hooks\ScriptEditor.h"
#include "Hooks\TESFile.h"

using namespace Hooks;
using namespace ComponentDLLInterface;

extern ComponentDLLInterface::CSEInterfaceTable g_InteropInterface;

extern "C"
{
	__declspec(dllexport) void* QueryInterface(void)
	{
		return &g_InteropInterface;
	}
}

void DeleteNativeHeapPointer( void* Pointer, bool IsArray )
{
	if (IsArray)
		delete [] Pointer;
	else
		delete Pointer;
}

/**** BEGIN EDITORAPI SUBINTERFACE ****/
#pragma region EditorAPI
void ComponentDLLDebugPrint(UInt8 Source, const char* Message)
{
	DebugPrint(Source, Message);
}

const char* GetAppPath(void)
{
	return g_APPPath.c_str();
}

void WriteToStatusBar(int PanelIndex, const char* Message)
{
	if (PanelIndex < 0 || PanelIndex > 2)
		PanelIndex = 2;

	TESDialog::WriteToStatusBar(MAKEWPARAM(PanelIndex, 0), (LPARAM)Message);
}

HWND GetCSMainWindowHandle(void)
{
	return *g_HWND_CSParent;
}

HWND GetRenderWindowHandle(void)
{
	return *g_HWND_RenderWindow;
}

FormData* LookupFormByEditorID(const char* EditorID)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);
	FormData* Result = NULL;

	if (Form)
	{
		Result = new FormData();
		Result->FillFormData(Form);
	}

	return Result;
}

ScriptData* LookupScriptableByEditorID(const char* EditorID)
{
	ScriptData* Result = NULL;
	TESForm* Form = TESForm::LookupByEditorID(EditorID);

	if (Form)
	{
		if (Form->IsReference())
		{
			TESObjectREFR* Ref =  CS_CAST(Form, TESForm, TESObjectREFR);
			if (Ref)
				Form = Ref->baseForm;
		}

		if (Form->formType == TESForm::kFormType_Script)
		{
			Result = new ScriptData();
			Result->FillScriptData(CS_CAST(Form, TESForm, Script));
			Result->ParentID = NULL;
		}
		else
		{
			TESScriptableForm* ScriptableForm = CS_CAST(Form, TESForm, TESScriptableForm);
			if (ScriptableForm)
			{
				Script* FormScript = ScriptableForm->script;
				if (FormScript)
				{
					Result = new ScriptData();
					Result->FillScriptData(FormScript);
					Result->ParentID = Form->editorID.c_str();				// EditorID of the script's parent form
				}
			}
		}
	}

	return Result;
}

bool GetIsFormReference(const char* EditorID)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);
	bool Result = false;

	if (Form)
		Result = Form->IsReference();

	return Result;
}

void LoadFormForEdit(const char* EditorID)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);
	if (Form)
	{
		switch (Form->formType)
		{
		case TESForm::kFormType_Script:
			TESDialog::ShowScriptEditorDialog(Form);
			break;
		case TESForm::kFormType_REFR:
			_TES->LoadCellIntoViewPort((CS_CAST(Form, TESForm, TESObjectREFR))->GetPosition(), CS_CAST(Form, TESForm, TESObjectREFR));
			break;
		default:
			TESDialog::ShowFormEditDialog(Form);
			break;
		}
	}
}

FormData* ShowPickReferenceDialog(HWND Parent)
{
	TESObjectREFR* Ref = TESDialog::ShowSelectReferenceDialog(Parent, NULL);
	if (!Ref)
		return NULL;
	else
		return new FormData(Ref);
}

void ShowUseReportDialog(const char* EditorID)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);
	if (Form)
		CreateDialogParam(*g_TESCS_Instance, (LPCSTR)TESDialog::kDialogTemplate_UseReport, NULL, g_FormUseReport_DlgProc, (LPARAM)Form);
}

void SaveActivePlugin(void)
{
	SendMessage(*g_HWND_CSParent, WM_COMMAND, 0x9CD2, NULL);
}

void ReadFromINI(const char* Setting, const char* Section, const char* Default, char* OutBuffer, UInt32 Size)
{
	g_INIManager->DirectReadFromINI(Setting, Section, Default, OutBuffer, Size);
}

void WriteToINI(const char* Setting, const char* Section, const char* Value)
{
	g_INIManager->DirectWriteToINI(Setting, Section, Value);
}
#pragma endregion
/**** END EDITORAPI SUBINTERFACE ****/

/**** BEGIN SCRIPTEDITOR SUBINTERFACE ****/
#pragma region ScriptEditor
ScriptData* CreateNewScript(void)
{
	Script* NewInstance = CS_CAST(TESForm::CreateInstance(TESForm::kFormType_Script), TESForm, Script);
	ScriptData* Data = new ScriptData(NewInstance);
	NewInstance->SetFromActiveFile(true);
	_DATAHANDLER->scripts.AddAt(NewInstance, eListEnd);
	_DATAHANDLER->SortScripts();

	return Data;
}

bool CompileScript(ScriptCompileData* Data)
{
	Script* ScriptForm = CS_CAST(Data->Script.ParentForm, TESForm, Script);

	if ((ScriptForm->formFlags & TESForm::kFormFlags_Deleted))
	{
		MessageBox(*g_HWND_CSParent,
					PrintToBuffer("Script %s {%08X} has been deleted and therefore cannot be compiled", ScriptForm->editorID.c_str(), ScriptForm->formID),
					"CSE Script Editor",
					MB_OK|MB_ICONEXCLAMATION|MB_TOPMOST|MB_SETFOREGROUND);
		Data->CompileResult = false;
	}
	else
	{
		BSStringT* OldText = BSStringT::CreateInstance(ScriptForm->text);

		ScriptForm->info.type = Data->Script.Type;
		ScriptForm->UpdateUsageInfo();
		ScriptForm->SetText(Data->Script.Text);
		ScriptForm->SetFromActiveFile(true);
		ScriptForm->compileResult = Data->CompileResult = ScriptForm->Compile();
		if (ScriptForm->compileResult)
		{
			_DATAHANDLER->SortScripts();
			Data->Script.FillScriptData(ScriptForm);
		}
		else
		{
			Data->CompileErrorData.Count = g_CompilerErrorListBuffer.size();
			if (g_CompilerErrorListBuffer.size())
			{
				Data->CompileErrorData.ErrorListHead = new ScriptErrorListData::ErrorData[Data->CompileErrorData.Count];

				for (int i = 0; i < Data->CompileErrorData.Count; i++)
				{
					CompilerErrorData* Error = &g_CompilerErrorListBuffer[i];
					Data->CompileErrorData.ErrorListHead[i].Line = Error->Line;
					Data->CompileErrorData.ErrorListHead[i].Message = Error->Message.c_str();
				}
			}
			else
				Data->CompileErrorData.ErrorListHead = NULL;

			ScriptForm->SetText(OldText->c_str());
		}

		OldText->DeleteInstance();
	}

	return Data->CompileResult;
}

void RecompileScripts(void)
{
	g_PreventScriptCompileErrorRerouting = true;

	DebugPrint("Recompiling active scripts...");
	CONSOLE->Indent();

	for (tList<Script>::Iterator Itr = _DATAHANDLER->scripts.Begin(); !Itr.End() && Itr.Get(); ++Itr)
	{
		Script* ScriptForm = Itr.Get();
		if ((ScriptForm->formFlags & TESForm::kFormFlags_Deleted) == 0 &&
			(ScriptForm->formFlags & TESForm::kFormFlags_FromActiveFile))
		{
			DebugPrint(Console::e_CS, "Script '%s' {%08X}:", ScriptForm->editorID.c_str(), ScriptForm->formID);
			CONSOLE->Indent();
			ScriptForm->Compile();
			CONSOLE->Exdent();
		}
	}

	CONSOLE->Exdent();
	DebugPrint("Recompile active scripts operation completed!");

	g_PreventScriptCompileErrorRerouting = false;
}

void ToggleScriptCompilation(bool State)
{
	TESScriptCompiler::ToggleScriptCompilation(State);
}

void DeleteScript(const char* EditorID)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);
	if (Form)
	{
		Script* ScriptForm = CS_CAST(Form, TESForm, Script);
		if (ScriptForm)
		{
			ScriptForm->SetDeleted(true);
		}
	}
}

ScriptData* GetPreviousScriptInList(void* CurrentScript)
{
	Script* ScriptForm = CS_CAST(CurrentScript, TESForm, Script);
	ScriptData* Result = NULL;

	if (_DATAHANDLER->scripts.Count())
	{
		Result = new ScriptData();
		if (ScriptForm)
		{
			int Index = _DATAHANDLER->scripts.IndexOf(ScriptForm);
			if (--Index < 0)
				Result->FillScriptData(_DATAHANDLER->scripts.GetLastItem());
			else
				Result->FillScriptData(_DATAHANDLER->scripts.GetNthItem(Index));
		}
		else
			Result->FillScriptData(_DATAHANDLER->scripts.GetLastItem());
	}

	return Result;
}

ScriptData* GetNextScriptInList(void* CurrentScript)
{
	Script* ScriptForm = CS_CAST(CurrentScript, TESForm, Script);
	ScriptData* Result = NULL;

	if (_DATAHANDLER->scripts.Count())
	{
		Result = new ScriptData();
		if (ScriptForm)
		{
			int Index = _DATAHANDLER->scripts.IndexOf(ScriptForm);
			if (++Index < _DATAHANDLER->scripts.Count())
				Result->FillScriptData(_DATAHANDLER->scripts.GetNthItem(Index));
			else
				Result->FillScriptData(_DATAHANDLER->scripts.GetNthItem(0));
		}
		else
			Result->FillScriptData(_DATAHANDLER->scripts.GetNthItem(0));
	}

	return Result;
}

void DestroyScriptInstance(void* CurrentScript)
{
	Script* ScriptForm = CS_CAST(CurrentScript, TESForm, Script);
	_DATAHANDLER->scripts.Remove(ScriptForm);
	ScriptForm->DeleteInstance();
}

void SaveEditorBoundsToINI(UInt32 Top, UInt32 Left, UInt32 Width, UInt32 Height)
{
	WritePrivateProfileString("General", "Script Edit X", PrintToBuffer("%d", Left), g_CSINIPath);
	WritePrivateProfileString("General", "Script Edit Y", PrintToBuffer("%d", Top), g_CSINIPath);
	WritePrivateProfileString("General", "Script Edit W", PrintToBuffer("%d", Width), g_CSINIPath);
	WritePrivateProfileString("General", "Script Edit H", PrintToBuffer("%d", Height), g_CSINIPath);
}

ScriptListData* GetScriptList(void)
{
	ScriptListData* Result = new ScriptListData();
	if (_DATAHANDLER->scripts.Count())
	{
		Result->ScriptCount = _DATAHANDLER->scripts.Count();
		Result->ScriptListHead = new ScriptData[Result->ScriptCount];
		int i = 0;
		for (tList<Script>::Iterator Itr = _DATAHANDLER->scripts.Begin(); !Itr.End() && Itr.Get(); ++Itr)
		{
			Script* ScriptForm = Itr.Get();
			Result->ScriptListHead[i].FillScriptData(ScriptForm);
			i++;
		}
	}

	return Result;
}

ScriptVarListData* GetScriptVarList(const char* EditorID)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);
	ScriptVarListData* Result = new ScriptVarListData();

	if (Form)
	{
		Script* ScriptForm = CS_CAST(Form, TESForm, Script);
		if (ScriptForm && ScriptForm->varList.Count())
		{
			Result->ScriptVarListCount = ScriptForm->varList.Count();
			Result->ScriptVarListHead = new ScriptVarListData::ScriptVarInfo[Result->ScriptVarListCount];

			int i = 0;
			for (Script::VariableListT::Iterator Itr = ScriptForm->varList.Begin(); !Itr.End() && Itr.Get(); ++Itr)
			{
				Script::VariableInfo* Variable = Itr.Get();

				Result->ScriptVarListHead[i].Name = Variable->name.c_str();
				Result->ScriptVarListHead[i].Type = Variable->type;
				Result->ScriptVarListHead[i].Index = Variable->index;

				if (Result->ScriptVarListHead[i].Type == Script::kVariableTypes_Float)
				{
					for (Script::RefVariableListT::Iterator ItrEx = ScriptForm->refList.Begin(); !ItrEx.End() && ItrEx.Get(); ++ItrEx)
					{
						if (ItrEx.Get()->variableIndex == Variable->index)
						{
							Result->ScriptVarListHead[i].Type = 2;		// ref var
							break;
						}
					}
				}

				i++;
			}
		}
	}

	return Result;
}

bool UpdateScriptVarIndices(const char* EditorID, ScriptVarListData* Data)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);
	bool Result = false;

	if (Form)
	{
		Script* ScriptForm = CS_CAST(Form, TESForm, Script);

		if (ScriptForm)
		{
			for (int i = 0; i < Data->ScriptVarListCount; i++)
			{
				ScriptVarListData::ScriptVarInfo* VarInfo = &Data->ScriptVarListHead[i];
				Script::VariableInfo* ScriptVar = ScriptForm->LookupVariableInfoByName(VarInfo->Name);

				if (ScriptVar)
				{
					if (VarInfo->Type == 2)
					{
						Script::RefVariable* RefVar = ScriptForm->LookupRefVariableByIndex(ScriptVar->index);
						if (RefVar)
							RefVar->variableIndex = VarInfo->Index;
					}

					ScriptVar->index = VarInfo->Index;
				}
			}

			Result = true;
			ScriptForm->SetFromActiveFile(true);
		}
	}

	return Result;
}

void CompileCrossReferencedForms(TESForm* Form)
{
	DebugPrint("Parsing object use list of %08X...", Form->formID);
	CONSOLE->Indent();

	std::vector<Script*> ScriptDepends;		// updating usage info inside an use list loop invalidates the list.
	std::vector<TESTopicInfo*> InfoDepends; // so store the objects ptrs and parse them later
	std::vector<TESQuest*> QuestDepends;

	for (FormCrossReferenceListT::Iterator Itr = Form->GetCrossReferenceList()->Begin(); !Itr.End() && Itr.Get(); ++Itr)
	{
		TESForm* Depends = Itr.Get()->GetForm();
		switch (Depends->formType)
		{
		case TESForm::kFormType_TopicInfo:
		{
			InfoDepends.push_back(CS_CAST(Depends, TESForm, TESTopicInfo));
			break;
		}
		case TESForm::kFormType_Quest:
		{
			QuestDepends.push_back(CS_CAST(Depends, TESForm, TESQuest));
			break;
		}
		case TESForm::kFormType_Script:
		{
			ScriptDepends.push_back(CS_CAST(Depends, TESForm, Script));
			break;
		}
		default:	// ### any other type that needs handling ?
			break;
		}
	}

	// scripts
	for (std::vector<Script*>::const_iterator Itr = ScriptDepends.begin(); Itr != ScriptDepends.end(); Itr++)
	{
		DebugPrint("Script %s {%08X}:", (*Itr)->editorID.c_str(), (*Itr)->formID);
		CONSOLE->Indent();

		if ((*Itr)->info.dataLength > 0)
		{
			if (!(*Itr)->Compile())
			{
				DebugPrint("Script failed to compile due to errors!");
			}
		}

		CONSOLE->Exdent();
	}

	// quests
	for (std::vector<TESQuest*>::const_iterator Itr = QuestDepends.begin(); Itr != QuestDepends.end(); Itr++)
	{
		DebugPrint("Quest %s {%08X}:", (*Itr)->editorID.c_str(), (*Itr)->formID);
		CONSOLE->Indent();

		for (TESQuest::StageListT::Iterator i = (*Itr)->stageList.Begin(); !i.End(); ++i)
		{
			TESQuest::StageData* Stage = i.Get();
			if (!Stage)
				break;

			int Count = 0;
			for (TESQuest::StageData::StageItemListT::Iterator j = Stage->stageItemList.Begin(); !j.End(); ++j, ++Count)
			{
				TESQuest::StageData::QuestStageItem* StageItem = j.Get();
				if (!StageItem)
					break;

				if (StageItem->resultScript.info.dataLength > 0)
				{
					if (!StageItem->resultScript.Compile(true))
					{
						DebugPrint("Result script in stage item %d-%d failed to compile due to errors!", Stage->index, Count);
					}
				}

				DebugPrint("Found %d conditions in stage item %d-%d that referenced source script",
					TESConditionItem::GetScriptableFormConditionCount(&StageItem->conditions, Form), Stage->index, Count);
			}
		}

		for (TESQuest::TargetListT::Iterator j = (*Itr)->targetList.Begin(); !j.End(); ++j)
		{
			TESQuest::TargetData* Target = j.Get();
			if (!Target)
				break;

			DebugPrint("Found %d conditions in target entry {%08X} that referenced source script",
						TESConditionItem::GetScriptableFormConditionCount(&Target->conditionList, Form), Target->target->formID);
		}

		(*Itr)->UpdateUsageInfo();
		CONSOLE->Exdent();
	}

	// topic infos
	for (std::vector<TESTopicInfo*>::const_iterator Itr = InfoDepends.begin(); Itr != InfoDepends.end(); Itr++)
	{
		DebugPrint("Topic info %08X:", (*Itr)->formID);
		CONSOLE->Indent();

		if ((*Itr)->resultScript.info.dataLength > 0)
		{
			if (!(*Itr)->resultScript.Compile(true))
			{
				DebugPrint("Result script failed to compile due to errors!");
			}
		}

		DebugPrint("Found %d conditions that referenced source script",
					TESConditionItem::GetScriptableFormConditionCount(&(*Itr)->conditions, Form));

		(*Itr)->UpdateUsageInfo();
		CONSOLE->Exdent();
	}

	CONSOLE->Exdent();
}

void CompileDependencies(const char* EditorID)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);
	if (!Form)						return;
	Script* ScriptForm = CS_CAST(Form, TESForm, Script);
	if (!ScriptForm)				return;

	DebugPrint("Recompiling dependencies of script %s {%08X}...", ScriptForm->editorID.c_str(), ScriptForm->formID);
	CONSOLE->Indent();

	DebugPrint("Resolving script parent...");
	CONSOLE->Indent();
	switch (ScriptForm->info.type)
	{
	case Script::kScriptType_Object:
	{
		DebugPrint("Script type = Object");
		for (FormCrossReferenceListT::Iterator Itr = Form->GetCrossReferenceList()->Begin(); !Itr.End() && Itr.Get(); ++Itr)
		{
			TESForm* Parent = Itr.Get()->GetForm();
			TESScriptableForm* ValidParent = CS_CAST(Parent, TESForm, TESScriptableForm);

			if (ValidParent)
			{
				DebugPrint("Scriptable Form %s ; Type = %d:", Parent->editorID.c_str(), Parent->formType);
				DebugPrint("Parsing cell use list...");
				CONSOLE->Indent();

				TESCellUseList* UseList = CS_CAST(Form, TESForm, TESCellUseList);
				for (TESCellUseList::CellUseInfoListT::Iterator Itr = UseList->cellUses.Begin(); !Itr.End(); ++Itr)
				{
					TESCellUseList::CellUseInfo* Data = Itr.Get();
					if (!Data)
						break;

					for (TESObjectCELL::ObjectREFRList::Iterator Itr = Data->cell->objectList.Begin(); !Itr.End(); ++Itr)
					{
						TESObjectREFR* ThisReference = Itr.Get();
						if (!ThisReference)
							break;

						if (ThisReference->baseForm == Parent)
							CompileCrossReferencedForms((TESForm*)ThisReference);
					}
				}
				CONSOLE->Exdent();
			}
		}
		break;
	}
	case Script::kScriptType_Quest:
	{
		DebugPrint("Script type = Quest");
		for (FormCrossReferenceListT::Iterator Itr = Form->GetCrossReferenceList()->Begin(); !Itr.End() && Itr.Get(); ++Itr)
		{
			TESForm* Parent = Itr.Get()->GetForm();
			if (Parent->formType == TESForm::kFormType_Quest)
			{
				DebugPrint("Quest %s:", Parent->editorID.c_str());
				CompileCrossReferencedForms(Parent);
			}
		}
		break;
	}
	}
	CONSOLE->Exdent();

	DebugPrint("Parsing direct dependencies...");
	CompileCrossReferencedForms(Form);

	CONSOLE->Exdent();
	DebugPrint("Recompile dependencies operation completed!");
}

IntelliSenseUpdateData* GetIntelliSenseUpdateData(void)
{
	IntelliSenseUpdateData* Data = new IntelliSenseUpdateData();

	UInt32 QuestCount = _DATAHANDLER->quests.Count(),
			ScriptCount = 0,
			GlobalCount = _DATAHANDLER->globals.Count(),
			EditorIDFormCount = 0;

	ScriptData TestData;
	for (tList<Script>::Iterator Itr = _DATAHANDLER->scripts.Begin(); !Itr.End() && Itr.Get(); ++Itr)
	{
		TestData.FillScriptData(Itr.Get());
		if (TestData.UDF)	ScriptCount++;
	}

	void* Unk01 = thisCall<void*>(0x0051F920, g_FormEditorIDMap);
	while (Unk01)
	{
		const char*	 EditorID = NULL;
		TESForm* Form = NULL;

		thisCall<UInt32>(0x005E0F90, g_FormEditorIDMap, &Unk01, &EditorID, &Form);
		if (EditorID)
		{
			if (Form->formType != TESForm::kFormType_GMST &&
				Form->formType != TESForm::kFormType_Global &&
				Form->formType != TESForm::kFormType_Quest)
			{
				EditorIDFormCount++;
			}
		}
	}

	Data->QuestListHead = new QuestData[QuestCount];
	Data->QuestCount = QuestCount;
	Data->ScriptListHead = new ScriptData[ScriptCount];
	Data->ScriptCount = ScriptCount;
	Data->GlobalListHead = new GlobalData[GlobalCount];
	Data->GlobalCount = GlobalCount;
	Data->EditorIDListHead = new FormData[EditorIDFormCount];
	Data->EditorIDCount = EditorIDFormCount;

	QuestCount = 0, ScriptCount = 0, GlobalCount = 0, EditorIDFormCount = 0;
	for (tList<TESQuest>::Iterator Itr = _DATAHANDLER->quests.Begin(); !Itr.End() && Itr.Get(); ++Itr)
	{
		Data->QuestListHead[QuestCount].FillFormData(Itr.Get());
		Data->QuestListHead[QuestCount].FullName = Itr.Get()->name.c_str();
		Data->QuestListHead[QuestCount].ScriptName = NULL;
		if (Itr.Get()->script)
			Data->QuestListHead[QuestCount].ScriptName = Itr.Get()->script->editorID.c_str();
		QuestCount++;
	}

	for (tList<Script>::Iterator Itr = _DATAHANDLER->scripts.Begin(); !Itr.End() && Itr.Get(); ++Itr)
	{
		TestData.FillScriptData(Itr.Get());
		if (TestData.UDF)
		{
			Data->ScriptListHead[ScriptCount].FillScriptData(Itr.Get());
			ScriptCount++;
		}
	}

	for (tList<TESGlobal>::Iterator Itr = _DATAHANDLER->globals.Begin(); !Itr.End() && Itr.Get(); ++Itr)
	{
		Data->GlobalListHead[GlobalCount].FillFormData(Itr.Get());
		Data->GlobalListHead[GlobalCount].FillVariableData(Itr.Get());
		GlobalCount++;
	}

	Unk01 = thisCall<void*>(0x0051F920, g_FormEditorIDMap);
	while (Unk01)
	{
		const char*	 EditorID = NULL;
		TESForm* Form = NULL;

		thisCall<UInt32>(0x005E0F90, g_FormEditorIDMap, &Unk01, &EditorID, &Form);
		if (EditorID)
		{
			if (Form->formType != TESForm::kFormType_GMST &&
				Form->formType != TESForm::kFormType_Global &&
				Form->formType != TESForm::kFormType_Quest)
			{
				Data->EditorIDListHead[EditorIDFormCount].FillFormData(Form);
				EditorIDFormCount++;
			}
		}
	}

	return Data;
}

void BindScript(const char* EditorID, HWND Parent)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);
	if (!Form)						return;
	Script* ScriptForm = CS_CAST(Form, TESForm, Script);
	if (!ScriptForm)				return;

	Form = (TESForm*)DialogBox(g_DLLInstance, MAKEINTRESOURCE(DLG_BINDSCRIPT), Parent, (DLGPROC)BindScriptDlgProc);

	if (Form)
	{
		TESQuest* Quest = CS_CAST(Form, TESForm, TESQuest);
		TESBoundObject* BoundObj = CS_CAST(Form, TESForm, TESBoundObject);
		TESScriptableForm* ScriptableForm = CS_CAST(Form, TESForm, TESScriptableForm);

		if ((Quest && ScriptForm->info.type != Script::kScriptType_Quest) ||
			(BoundObj && ScriptForm->info.type != Script::kScriptType_Object))
		{
			MessageBox(Parent, "Script type doesn't correspond to binding form.", "CSE Script Editor", MB_OK|MB_ICONEXCLAMATION);
		}
		else if (ScriptableForm == NULL)
			MessageBox(Parent, "Binding form isn't scriptable.", "CSE Script Editor", MB_OK|MB_ICONEXCLAMATION);
		else
		{
			ScriptableForm->script = ScriptForm;
			ScriptForm->AddCrossReference(Form);
			Form->SetFromActiveFile(true);

			sprintf_s(g_TextBuffer, sizeof(g_TextBuffer), "Script '%s' bound to form '%s'", ScriptForm->editorID.c_str(), Form->editorID.c_str());
			MessageBox(Parent, g_TextBuffer, "CSE Script Editor", MB_OK|MB_ICONINFORMATION);
		}
	}
}

void SetScriptText(void* CurrentScript, const char* ScriptText)
{
	Script* ScriptForm = CS_CAST(CurrentScript, TESForm, Script);
	ScriptForm->SetText(ScriptText);
}

void UpdateScriptVarNames(const char* EditorID, ComponentDLLInterface::ScriptVarRenameData* Data)
{
	TESForm* Form = TESForm::LookupByEditorID(EditorID);

	if (Form)
	{
		Script* ScriptForm = CS_CAST(Form, TESForm, Script);

		if (ScriptForm)
		{
			DebugPrint("Updating script '%s' variable names...", ScriptForm->editorID.c_str());
			CONSOLE->Indent();
			for (int i = 0; i < Data->ScriptVarListCount; i++)
			{
				ScriptVarRenameData::ScriptVarInfo* VarInfo = &Data->ScriptVarListHead[i];
				Script::VariableInfo* ScriptVar = ScriptForm->LookupVariableInfoByName(VarInfo->OldName);

				if (ScriptVar)
				{
					ScriptVar->name.Set(VarInfo->NewName);
					DebugPrint("Variable '%s' renamed to '%s'", VarInfo->OldName, VarInfo->NewName);

					Script::RefVariable* RefVar = ScriptForm->LookupRefVariableByIndex(ScriptVar->index);
					if (RefVar && !RefVar->form)
						RefVar->name.Set(VarInfo->NewName);
				}
			}

			CONSOLE->Exdent();
			ScriptForm->SetFromActiveFile(true);
		}
	}
}

bool CanUpdateIntelliSenseDatabase(void)
{
	return g_LoadingSavingPlugins == false;
}
#pragma endregion
/**** END SCRIPTEDITOR SUBINTERFACE ****/

/**** BEGIN USEINFOLIST SUBINTERFACE ****/
#pragma region UseInfoList
template <typename tData>
void AddLinkedListContentsToFormList(tList<tData>* List, FormListData* FormList, UInt32& CurrentIndex)
{
	for (tList<tData>::Iterator Itr = List->Begin(); !Itr.End() && Itr.Get(); ++Itr)
	{
		FormData* ThisForm = &FormList->FormListHead[CurrentIndex];
		ThisForm->FillFormData(Itr.Get());
		CurrentIndex++;
	}
}

UseInfoListFormData* GetLoadedForms(void)
{
	UseInfoListFormData* Result = new UseInfoListFormData();

	UInt32 TotalFormCount = _DATAHANDLER->objects->objectCount;
	TotalFormCount += _DATAHANDLER->packages.Count();
	TotalFormCount += _DATAHANDLER->worldSpaces.Count();
	TotalFormCount += _DATAHANDLER->climates.Count();
	TotalFormCount += _DATAHANDLER->weathers.Count();
	TotalFormCount += _DATAHANDLER->enchantmentItems.Count();
	TotalFormCount += _DATAHANDLER->spellItems.Count();
	TotalFormCount += _DATAHANDLER->hairs.Count();
	TotalFormCount += _DATAHANDLER->eyes.Count();
	TotalFormCount += _DATAHANDLER->races.Count();
	TotalFormCount += _DATAHANDLER->landTextures.Count();
	TotalFormCount += _DATAHANDLER->classes.Count();
	TotalFormCount += _DATAHANDLER->factions.Count();
	TotalFormCount += _DATAHANDLER->scripts.Count();
	TotalFormCount += _DATAHANDLER->sounds.Count();
	TotalFormCount += _DATAHANDLER->globals.Count();
	TotalFormCount += _DATAHANDLER->topics.Count();
	TotalFormCount += _DATAHANDLER->quests.Count();
	TotalFormCount += _DATAHANDLER->birthsigns.Count();
	TotalFormCount += _DATAHANDLER->combatStyles.Count();
	TotalFormCount += _DATAHANDLER->loadScreens.Count();
	TotalFormCount += _DATAHANDLER->waterForms.Count();
	TotalFormCount += _DATAHANDLER->effectShaders.Count();
	TotalFormCount += _DATAHANDLER->objectAnios.Count();

	Result->FormCount = TotalFormCount;
	Result->FormListHead = new FormData[Result->FormCount];

	UInt32 Index = 0;
	for (TESObject* Itr = _DATAHANDLER->objects->first; Itr; Itr = Itr->next)
	{
		FormData* ThisForm = &Result->FormListHead[Index];
		ThisForm->FillFormData(Itr);
		Index++;
	}

	AddLinkedListContentsToFormList(&_DATAHANDLER->packages, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->worldSpaces, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->climates, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->weathers, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->enchantmentItems, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->spellItems, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->hairs, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->eyes, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->races, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->landTextures, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->classes, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->factions, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->scripts, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->sounds, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->globals, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->topics, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->quests, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->birthsigns, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->combatStyles, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->loadScreens, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->waterForms, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->effectShaders, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->objectAnios, (FormListData*)Result, Index);

	return Result;
}

UseInfoListCrossRefData* GetCrossRefDataForForm(const char* EditorID)
{
	UseInfoListCrossRefData* Result = new UseInfoListCrossRefData();
	TESForm* Form = TESForm::LookupByEditorID(EditorID);

	if (Form)
	{
		FormCrossReferenceListT* CrossRefList = Form->GetCrossReferenceList();
		if (CrossRefList->Count())
		{
			Result->FormCount = CrossRefList->Count();
			Result->FormListHead = new FormData[Result->FormCount];
			int i = 0;
			for (FormCrossReferenceListT::Iterator Itr = CrossRefList->Begin(); !Itr.End() && Itr.Get(); ++Itr)
			{
				TESForm* Reference = Itr.Get()->GetForm();
				Result->FormListHead[i].FillFormData(Reference);
				i++;
			}
		}
	}

	return Result;
}

UseInfoListCellItemListData* GetCellRefDataForForm(const char* EditorID)
{
	UseInfoListCellItemListData* Result = new UseInfoListCellItemListData();
	TESForm* Form = TESForm::LookupByEditorID(EditorID);

	if (Form)
	{
		TESCellUseList* UseList = CS_CAST(Form, TESForm, TESCellUseList);
		if (UseList && UseList->cellUses.Count())
		{
			TESCellUseList::CellUseInfoListT* CellUseList = &UseList->cellUses;
			if (CellUseList->Count())
			{
				Result->UseInfoListCellItemListCount = CellUseList->Count();
				Result->UseInfoListCellItemListHead = new UseInfoListCellItemData[Result->UseInfoListCellItemListCount];
				int i = 0;
				for (TESCellUseList::CellUseInfoListT::Iterator Itr = CellUseList->Begin(); !Itr.End() && Itr.Get(); ++Itr)
				{
					TESCellUseList::CellUseInfo* Data = Itr.Get();
					TESObjectREFR* FirstRef = Data->cell->LookupRefByBaseForm(Form, true);
					TESWorldSpace* WorldSpace = Data->cell->GetParentWorldSpace();

					Result->UseInfoListCellItemListHead[i].EditorID = Data->cell->editorID.c_str();
					Result->UseInfoListCellItemListHead[i].FormID = Data->cell->formID;
					Result->UseInfoListCellItemListHead[i].Flags = Data->cell->cellFlags24 & TESObjectCELL::kCellFlags_Interior;
					Result->UseInfoListCellItemListHead[i].WorldEditorID = ((!WorldSpace)?"Interior":WorldSpace->editorID.c_str());
					Result->UseInfoListCellItemListHead[i].RefEditorID = ((!FirstRef || !FirstRef->editorID.c_str())?"<Unnamed>":FirstRef->editorID.c_str());
					Result->UseInfoListCellItemListHead[i].XCoord = Data->cell->cellData.coords->x;
					Result->UseInfoListCellItemListHead[i].YCoord = Data->cell->cellData.coords->y;
					Result->UseInfoListCellItemListHead[i].UseCount = Data->count;

					i++;
				}
			}
		}
	}

	return Result;
}
/**** END USEINFOLIST SUBINTERFACE ****/
#pragma endregion

/**** BEGIN BATCHREFEDITOR SUBINTERFACE ****/
#pragma region BatchRefEditor
BatchRefOwnerFormData* GetOwnershipData(void)
{
	BatchRefOwnerFormData* Result = new BatchRefOwnerFormData();

	UInt32 TotalFormCount = 0;
	TotalFormCount += _DATAHANDLER->factions.Count();
	TotalFormCount += _DATAHANDLER->globals.Count();
	for (TESObject* Itr = _DATAHANDLER->objects->first; Itr; Itr = Itr->next)
	{
		if (Itr->formType == TESForm::kFormType_NPC)
			TotalFormCount++;
	}

	Result->FormCount = TotalFormCount;
	Result->FormListHead = new FormData[Result->FormCount];

	UInt32 Index = 0;
	for (TESObject* Itr = _DATAHANDLER->objects->first; Itr; Itr = Itr->next)
	{
		if (Itr->formType == TESForm::kFormType_NPC)
		{
			FormData* ThisForm = &Result->FormListHead[Index];
			ThisForm->FillFormData(Itr);
			Index++;
		}
	}

	AddLinkedListContentsToFormList(&_DATAHANDLER->factions, (FormListData*)Result, Index);
	AddLinkedListContentsToFormList(&_DATAHANDLER->globals, (FormListData*)Result, Index);

	return Result;
}
#pragma endregion
/**** END USEINFOLIST SUBINTERFACE ****/

/**** BEGIN TAGBROWSER SUBINTERFACE ****/
#pragma region TagBrowser
void InstantiateObjects(TagBrowserInstantiationData* Data)
{
	HWND Window = WindowFromPoint(Data->InsertionPoint);
	if (Window)
	{
		bool ValidRecipient = false;
		for (int i = 0; i < Data->FormCount; i++)
		{
			FormData* ThisData = &Data->FormListHead[i];
			UInt32 FormID = ThisData->FormID;

			TESForm* Form = TESForm::LookupByFormID(FormID);
			if (Form && TESDialog::GetIsWindowDragDropRecipient(Form->formType, Window))
			{
				ValidRecipient = true;
				break;
			}
		}

		if (ValidRecipient)
		{
			(*g_TESRenderSelectionPrimary)->ClearSelection(true);

			for (int i = 0; i < Data->FormCount; i++)
			{
				FormData* ThisData = &Data->FormListHead[i];
				UInt32 FormID = ThisData->FormID;

				TESForm* Form = TESForm::LookupByFormID(FormID);
				if (!Form)
				{
					DebugPrint(Console::e_TAG, "Couldn't find form '%08X'!", FormID);
					continue;
				}
				(*g_TESRenderSelectionPrimary)->AddToSelection(Form);
			}

			HWND Parent = GetParent(Window);
			if (!Parent || Parent == *g_HWND_CSParent)
				SendMessage(Window, 0x407, NULL, (LPARAM)&Data->InsertionPoint);
			else
				SendMessage(Parent, 0x407, NULL, (LPARAM)&Data->InsertionPoint);
		}
	}
}
#pragma endregion
/**** END TAGBROWSER SUBINTERFACE ****/

ComponentDLLInterface::CSEInterfaceTable g_InteropInterface =
{
	DeleteNativeHeapPointer,
	{
		ComponentDLLDebugPrint,
		WriteToStatusBar,
		GetAppPath,
		GetCSMainWindowHandle,
		GetRenderWindowHandle,
		LookupFormByEditorID,
		LookupScriptableByEditorID,
		GetIsFormReference,
		LoadFormForEdit,
		ShowPickReferenceDialog,
		ShowUseReportDialog,
		SaveActivePlugin,
		ReadFromINI,
		WriteToINI,
	},
	{
		CreateNewScript,
		DestroyScriptInstance,
		CompileScript,
		RecompileScripts,
		ToggleScriptCompilation,
		DeleteScript,
		GetPreviousScriptInList,
		GetNextScriptInList,
		SaveEditorBoundsToINI,
		GetScriptList,
		GetScriptVarList,
		UpdateScriptVarIndices,
		CompileDependencies,
		GetIntelliSenseUpdateData,
		BindScript,
		SetScriptText,
		UpdateScriptVarNames,
		CanUpdateIntelliSenseDatabase,
	},
	{
		GetLoadedForms,
		GetCrossRefDataForForm,
		GetCellRefDataForForm,
	},
	{
		GetOwnershipData,
	},
	{
		InstantiateObjects,
	}
};