#include "ScriptListDialog.h"
#include "Globals.h"
#include "Common\NativeWrapper.h"
#include "ScriptEditorManager.h"
#include "Common\ListViewUtilities.h"


ScriptListDialog::ScriptListDialog(UInt32 AllocatedIndex)
{
	ParentIndex = AllocatedIndex;
	ScriptBox = gcnew Form();								
	PreviewBox = gcnew TextBox();
	ScriptList = gcnew ListView();
	ScriptListCFlags = gcnew ColumnHeader();
	ScriptListCScriptName = gcnew ColumnHeader();
	ScriptListCFormID = gcnew ColumnHeader();
	ScriptListCScriptType= gcnew ColumnHeader();	
	FilterBox = gcnew Button();
	SearchBox = gcnew TextBox();

	if (!FlagIcons->Images->Count) {
		FlagIcons->TransparentColor = Color::White;

		FlagIcons->Images->Add(GLOB->SLDDeletedImg);
		FlagIcons->Images->Add(GLOB->SLDActiveImg);
	}

	PreviewBox->Font = gcnew Font("Consolas", 9, FontStyle::Regular);
	PreviewBox->Location = Point(375, 12);
	PreviewBox->Multiline = true;
	PreviewBox->ReadOnly = true;
	PreviewBox->ScrollBars = ScrollBars::Both;
	PreviewBox->WordWrap = false;
	PreviewBox->Size = Size(357, 427);

	ScriptList->Columns->AddRange(gcnew cli::array< ColumnHeader^  >(4) {ScriptListCFlags,
																		 ScriptListCScriptName, 
																		 ScriptListCFormID,
																		 ScriptListCScriptType});
	ScriptList->Font = gcnew Font("Consolas", 9, FontStyle::Regular);
	ScriptList->Location = Point(12, 12);
	ScriptList->Size = Size(357, 391);
	ScriptList->UseCompatibleStateImageBehavior = false;
	ScriptList->View = View::Details;
	ScriptList->AutoSize = false;
	ScriptList->MultiSelect = false;
	ScriptList->SelectedIndexChanged += gcnew EventHandler(this, &ScriptListDialog::ScriptList_SelectedIndexChanged);
	ScriptList->KeyDown += gcnew KeyEventHandler(this, &ScriptListDialog::ScriptList_KeyDown);
	ScriptList->MouseDoubleClick += gcnew MouseEventHandler(this, &ScriptListDialog::ScriptList_MouseDoubleClick);
	ScriptList->ColumnClick += gcnew ColumnClickEventHandler(this, &ScriptListDialog::ScriptList_ColumnClick);
	ScriptList->MouseUp += gcnew MouseEventHandler(this, &ScriptListDialog::ScriptList_MouseUp);
	ScriptList->CheckBoxes = false;
	ScriptList->FullRowSelect = true;
	ScriptList->HideSelection = false;
	ScriptList->SmallImageList = FlagIcons;

	ScriptListCFlags->Text = "";
	ScriptListCFlags->Width = 20;

	ScriptListCScriptName->Text = "Name";
	ScriptListCScriptName->Width = 196;

	ScriptListCFormID->Text = "FormID";
	ScriptListCFormID->Width = 73;

	ScriptListCScriptType->Text = "Type";
	ScriptListCScriptType->Width = 87;

	SearchBox->Font = gcnew Font("Consolas", 14.25F, FontStyle::Regular);
	SearchBox->Location = Point(13, 409);
	SearchBox->MaxLength = 512;
	SearchBox->Size = Size(242, 30);
	SearchBox->TextChanged += gcnew EventHandler(this, &ScriptListDialog::SearchBox_TextChanged);
	SearchBox->KeyDown += gcnew KeyEventHandler(this, &ScriptListDialog::SearchBox_KeyDown);

	FilterBox->Font = gcnew Font("Consolas", 6);
	FilterBox->Enabled = false;
	FilterBox->Location = Point(261, 409);
	FilterBox->Text = "<< Filter String";
	FilterBox->Size = Size(108, 30);

	ScriptBox->ClientSize = Size(744, 451);
	ScriptBox->Controls->Add(ScriptList);
	ScriptBox->Controls->Add(PreviewBox);
	ScriptBox->Controls->Add(FilterBox);
	ScriptBox->Controls->Add(SearchBox);
	ScriptBox->FormBorderStyle = FormBorderStyle::FixedDialog;
	ScriptBox->StartPosition = FormStartPosition::CenterScreen;
	ScriptBox->MaximizeBox = false;
	ScriptBox->MinimizeBox = false;
	ScriptBox->Text = "Select Script";
	ScriptBox->Closing += gcnew CancelEventHandler(this, &ScriptListDialog::ScriptBox_Cancel);

	ScriptBox->Hide();
	LastSortColumn = -1;
}

void ScriptListDialog::Show(Operation Op)
{
	CurrentOp = Op;

	ScriptList->BeginUpdate();
	NativeWrapper::ScriptEditor_GetScriptListData(ParentIndex);
	ScriptList->EndUpdate();

	if (ScriptList->Items->Count > 0) {
		String^ CurrentScript = dynamic_cast<String^>(SEMGR->GetAllocatedWorkspace(ParentIndex)->ParentStrip->EditorForm->Tag);
		if (CurrentScript != "New Script")
			SearchBox->Text = CurrentScript;
	}
	else {
		ScriptList->Enabled = false;
		SearchBox->Enabled = false;
	}

	ScriptBox->ShowDialog();
	SearchBox->Focus();
}

void ScriptListDialog::Close()
{
	ScriptList->Items->Clear();
	ScriptList->Enabled = true;
	SearchBox->Enabled = true;
	PreviewBox->Text = "";
	SearchBox->Text = "";
	ScriptBox->Hide();
}

void ScriptListDialog::AddScript(String^% ScriptName, String^% FormID, String^% ScriptType, UInt32 Flags)
{
	ListViewItem^ NewScript = gcnew ListViewItem("");
	NewScript->SubItems->Add(ScriptName);
	NewScript->SubItems->Add(FormID);
	NewScript->SubItems->Add(ScriptType);
	
	if (Flags & 0x00000020)
		NewScript->ImageIndex = (int)Icon::e_Deleted;
	else if (Flags & 0x00000002)
		NewScript->ImageIndex = (int)Icon::e_Active;

	ScriptList->Items->Add(NewScript);
}

void ScriptListDialog::OpenScript()
{
	if (GetListViewSelectedItem(ScriptList) == nullptr)		return;

	CStringWrapper^ CEID = gcnew CStringWrapper(GetListViewSelectedItem(ScriptList)->SubItems[1]->Text);
	NativeWrapper::ScriptEditor_SetScriptListResult(CEID->String());
	ScriptBox->Close();

	ScriptEditorManager::OperationParams^ Parameters = gcnew ScriptEditorManager::OperationParams();
	Parameters->VanillaHandleIndex = ParentIndex;

	switch (CurrentOp)
	{
	case Operation::e_Open:
		Parameters->ParameterList->Add(ScriptEditorManager::SendReceiveMessageType::e_Open);
		break;
	case Operation::e_Delete:
		Parameters->ParameterList->Add(ScriptEditorManager::SendReceiveMessageType::e_Delete);
		break;
	}

	SEMGR->PerformOperation(ScriptEditorManager::OperationType::e_SendMessage, Parameters);
}

void ScriptListDialog::GetUseReport()
{
	if (GetListViewSelectedItem(ScriptList) == nullptr)		return;

	CStringWrapper^ CEID = gcnew CStringWrapper(GetListViewSelectedItem(ScriptList)->SubItems[1]->Text);
	NativeWrapper::ScriptEditor_GetUseReportForForm(CEID->String());
}




void ScriptListDialog::ScriptBox_Cancel(Object^ Sender, CancelEventArgs^ E)
{
	bool Destroy = SEMGR->GetAllocatedWorkspace(ParentIndex)->Destroying;
	Close();
	if (!Destroy)
		E->Cancel = true;
}


void ScriptListDialog::ScriptList_SelectedIndexChanged(Object^ Sender, EventArgs^ E)
{
	if (GetListViewSelectedItem(ScriptList) == nullptr)		return;

	CStringWrapper^ CEID = gcnew CStringWrapper(GetListViewSelectedItem(ScriptList)->SubItems[1]->Text);
	PreviewBox->Text = gcnew String(NativeWrapper::ScriptEditor_GetScriptListItemText(CEID->String()));
}

void ScriptListDialog::ScriptList_KeyDown(Object^ Sender, KeyEventArgs^ E)
{
	switch (E->KeyCode)
	{
	case Keys::Enter:
		OpenScript();
		break;
	case Keys::F1:
		GetUseReport();
		break;
	case Keys::Escape:
		ScriptBox->Close();
		break;
	}
}

void ScriptListDialog::ScriptList_MouseDoubleClick(Object^ Sender, MouseEventArgs^ E)
{
	OpenScript();
}

void ScriptListDialog::ScriptList_MouseUp(Object^ Sender, MouseEventArgs^ E)
{
	if (!SearchBox->Focused)	SearchBox->Focus();
}

void ScriptListDialog::ScriptList_ColumnClick(Object^ Sender, ColumnClickEventArgs^ E)
{
	if (E->Column != LastSortColumn) {
		LastSortColumn = E->Column;
		ScriptList->Sorting = SortOrder::Descending;
	} else {
		if (ScriptList->Sorting == SortOrder::Ascending)
			ScriptList->Sorting = SortOrder::Descending;
		else
			ScriptList->Sorting = SortOrder::Ascending;
	}

	ScriptList->Sort();
	System::Collections::IComparer^ Sorter;
	switch (E->Column)
	{
	case 0:							// Flags
		Sorter = gcnew CSEListViewImgSorter(E->Column, ScriptList->Sorting);
		break;
	case 2:							// FormID
		Sorter = gcnew CSEListViewIntSorter(E->Column, ScriptList->Sorting, true);
		break;
	default:
		Sorter = gcnew CSEListViewStringSorter(E->Column, ScriptList->Sorting);
		break;
	}
	ScriptList->ListViewItemSorter = Sorter;
}

void ScriptListDialog::SearchBox_TextChanged(Object^ Sender, EventArgs^ E)
{
	if (SearchBox->Text != "") {
		ListViewItem^% Result = ScriptList->FindItemWithText(SearchBox->Text, true, 0);
		if (Result != nullptr) {
			Result->Selected = true;
			ScriptList->TopItem = Result; 
		}
		else {
			Result = GetListViewSelectedItem(ScriptList);
			if (Result != nullptr)		Result->Selected = false;
			PreviewBox->Text = "";
		}
	}
}

void ScriptListDialog::SearchBox_KeyDown(Object^ Sender, KeyEventArgs^ E)
{
	ScriptListDialog::ScriptList_KeyDown(nullptr, E);
}