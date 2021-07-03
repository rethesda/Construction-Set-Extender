#pragma once

#include "Macros.h"
#include "IScriptEditorController.h"
#include "ScriptEditorControllerImplComponents.h"

namespace cse
{


namespace scriptEditor
{


namespace controllerImpl
{


using namespace controller;

ref struct ActiveDocumentActionCollection
{
	property BasicAction^ Copy;
	property BasicAction^ Paste;
	property BasicAction^ Comment;
	property BasicAction^ Uncomment;
	property BasicAction^ AddBookmark;
	property BasicAction^ GoToLine;

	property BasicAction^ AddVarInteger;
	property BasicAction^ AddVarFloat;
	property BasicAction^ AddVarReference;
	property BasicAction^ AddVarString;
	property BasicAction^ AddVarArray;


	ActiveDocumentActionCollection();
	~ActiveDocumentActionCollection();

	void CreateDefaultKeyBindings(components::InputManager^ InputManager);
};

ref struct ViewActionCollection
{
	property BasicAction^ CurrentTabNewScript;
	property BasicAction^ CurrentTabOpenScript;
	property BasicAction^ CurrentTabSaveScript;
	property BasicAction^ CurrentTabPreviousScript;
	property BasicAction^ CurrentTabNextScript;
	property BasicAction^ SaveAllTabs;

	property BasicAction^ NewTabWithNewScript;
	property BasicAction^ NewTabWithExistingScript;
	property BasicAction^ PreviousTab;
	property BasicAction^ NextTab;
	property BasicAction^ CloseCurrentTab;

	property BasicAction^ ShowFindReplacePane;

	ViewActionCollection();
	~ViewActionCollection();

	void CreateDefaultKeyBindings(components::InputManager^ InputManager);
};

ref struct NewTabCreationParams
{
	static enum class eInitOperation
	{
		NewScript,
		LoadExistingScript,
		LoadFileFromDisk,
	};

	eInitOperation InitOperation;
	String^ ExistingScriptEditorId;
	String^ DiskFilePath;
	bool BindAfterInit;

	NewTabCreationParams();
};


ref class ScriptEditorController : public IScriptEditorController
{
	delegate void DeferredUiActionDelegate();

	static property String^ UnsavedScriptDisplayText
	{
		String^ get() { return "Unsaved Script"; }
	}

	view::IScriptEditorView^ ChildView;
	model::IScriptEditorModel^ ChildModel;
	model::IScriptDocument^ BoundDocument;

	view::IFactory^ ViewFactory;
	model::IFactory^ ModelFactory;
	controller::IFactory^ ControllerFactory;

	components::DocumentNavigationHelper^ DocumentNavigationHelper;
	components::FindReplaceHelper^ FindReplaceHelper;
	components::InputManager^ InputManager;
	ActiveDocumentActionCollection^ ActiveDocumentActions;
	ViewActionCollection^ ViewActions;
	Timer^ DeferredUiActionTimer;

	view::IScriptEditorView::EventHandler^ DelegateViewComponentEvent;
	model::IScriptDocument::StateChangeEventHandler^ DelegateModelDocumentStateChanged;
	KeyEventHandler^ DelegateModelKeyDown;
	textEditor::TextEditorMouseClickEventHandler^ DelegateModelMouseClick;
	model::components::INavigationHelper::NavigationChangedEventHandler^ DelegateModelNavigationChanged;
	EventHandler^ DelegateDeferredUiActionTimerTick;
	DeferredUiActionDelegate^ DelegateDeferredUiAction;

	bool DisableDocumentActivationOnTabSwitch;

	void ActiveDocumentAction_Copy();
	void ActiveDocumentAction_Paste();
	void ActiveDocumentAction_Comment();
	void ActiveDocumentAction_Uncomment();
	void ActiveDocumentAction_AddBookmark();
	void ActiveDocumentAction_GoToLine();

	void ActiveDocumentAction_AddVarInteger();
	void ActiveDocumentAction_AddVarFloat();
	void ActiveDocumentAction_AddVarReference();
	void ActiveDocumentAction_AddVarString();
	void ActiveDocumentAction_AddVarArray();

	void ViewAction_CurrentTabNewScript();
	void ViewAction_CurrentTabOpenScript();
	void ViewAction_CurrentTabSaveScript();
	void ViewAction_CurrentTabPreviousScript();
	void ViewAction_CurrentTabNextScript();
	void ViewAction_SaveAllTabs();
	void ViewAction_NewTabWithNewScript();
	void ViewAction_NewTabWithExistingScript();
	void ViewAction_PreviousTab();
	void ViewAction_NextTab();
	void ViewAction_CloseCurrentTab();
	void ViewAction_ShowFindReplacePane();

	void SetBoundDocument(model::IScriptDocument^ Document);
	void UnbindBoundDocument();

	void SetDocumentDependentViewComponentsEnabled(bool Enabled);
	void SetDocumentPreprocessorOutputDisplayDependentViewComponentsEnabled(bool Enabled);
	void ResetViewComponentsToUnboundState();

	view::ITabStripItem^ LookupTabStripItem(model::IScriptDocument^ Document);
	void SetDocumentScriptTypeFromDropdown(model::IScriptDocument^ Document, view::components::IComboBox^ Dropdown);
	void SetScriptTypeDropdown(view::components::IComboBox^ Dropdown, model::IScriptDocument::eScriptType ScriptType);

	bool HandleVolatileDocumentStateBeforeDestructiveOperation(model::IScriptDocument^ Document);
	bool HandleVolatileDocumentStateBeforeDestructiveOperation(model::IScriptDocument^ Document, bool% OutSaveOperationCancelled);

	void AttachDocumentToView(model::IScriptDocument^ Document);
	void DetachDocumentFromView(model::IScriptDocument^ Document);
	void ActivateDocumentInView(model::IScriptDocument^ Document);

	void DisposeSelfOnViewClosure();
	model::IScriptDocument^ CreateNewTab(NewTabCreationParams^ Params);
	model::IScriptDocument^ ImportDocumentFromDisk(String^ DiskFilePath, bool ImportAsExistingScript);

	void AllowDocumentBindingAfterTabMove();

	void LoadNewUnsavedScriptIntoDocument(model::IScriptDocument^ Document);
	void LoadExistingScriptIntoDocument(model::IScriptDocument^ Document, String^ ExistingScriptEditorId);
	void LoadExistingScriptIntoDocument(model::IScriptDocument^ Document, DisposibleDataAutoPtr<componentDLLInterface::ScriptData> ExistingScriptData);
	bool SaveDocument(model::IScriptDocument^ Document, model::IScriptDocument::eSaveOperation SaveOperation);
	void LoadNextScriptIntoDocument(model::IScriptDocument^ Document);
	void LoadPreviousScriptIntoDocument(model::IScriptDocument^ Document);
	bool CloseAndRemoveDocument(model::IScriptDocument^ Document);
	bool CloseAndRemoveDocument(model::IScriptDocument^ Document, bool% OutOperationCancelled);

	void ValidateDocumentSyncingStatus(model::IScriptDocument^ Document);
	bool ShouldUseAutoRecoveryFile(String^ ScriptEditorId);

	void DeferredUiActionTimer_Tick(Object^ Sender, EventArgs^ E);
	void ViewEventHandler_ComponentEvent(Object^ Sender, view::ViewComponentEvent^ E);

	void ViewEventHandler_MainWindow(view::ViewComponentEvent^ E);
	void ViewEventHandler_MainTabStrip(view::ViewComponentEvent^ E);
	void ViewEventHandler_MainToolbar(view::ViewComponentEvent^ E);
	void ViewEventHandler_MainToolbarMenuEdit(view::ViewComponentEvent^ E);
	void ViewEventHandler_MainToolbarMenuView(view::ViewComponentEvent^ E);
	void ViewEventHandler_MainToolbarMenuTools(view::ViewComponentEvent^ E);
	void ViewEventHandler_MainToolbarMenuHelp(view::ViewComponentEvent^ E);
	void ViewEventHandler_MessagesPanel(view::ViewComponentEvent^ E);
	void ViewEventHandler_BookmarksPanel(view::ViewComponentEvent^ E);
	void ViewEventHandler_TextEditorContextMenu(view::ViewComponentEvent^ E);
	void ViewEventHandler_EmptyWorkspacePanel(view::ViewComponentEvent^ E);

	void ModelEventHandler_DocumentStateChanged(Object^ Sender, model::IScriptDocument::StateChangeEventArgs^ E);
	void ModelEventHandler_KeyDown(Object^ Sender, KeyEventArgs^ E);
	void ModelEventHandler_MouseClick(Object^ Sender, textEditor::TextEditorMouseClickEventArgs^ E);
	void ModelEventHandler_NavigationChanged(Object^ Sender, model::components::INavigationHelper::NavigationChangedEventArgs^ E);

	void InitViewComponents();
	void ProcessInstantiationParameters(IScriptEditorController::InstantiationParams^ Params);

	void QueueDeferredUiAction(DeferredUiActionDelegate^ Action, UInt32 TimeoutInMs);
public:
	ScriptEditorController(model::IFactory^ ModelFactory, view::IFactory^ ViewFactory);
	ScriptEditorController(model::IFactory^ ModelFactory, view::IFactory^ ViewFactory, IScriptEditorController::InstantiationParams^ InitParams);
	virtual ~ScriptEditorController();

	ImplPropertyGetOnly(model::IScriptEditorModel^, Model, ChildModel);
	ImplPropertyGetOnly(view::IScriptEditorView^, View, ChildView);
	property model::IScriptDocument^ ActiveDocument
	{
		virtual model::IScriptDocument^ get() { return BoundDocument; }
		virtual void set(model::IScriptDocument^ v);
	}

	virtual IScriptEditorController^ New();
	virtual IScriptEditorController^ New(IScriptEditorController::InstantiationParams^ Params);
	virtual void RelocateDocument(model::IScriptDocument^ Document, IScriptEditorController^ Source);
	virtual void ActivateOrCreateNewDocument(String^ ScriptEditorId);
};


ref struct ScriptEditorControllerFactory : public controller::IFactory
{
public:
	virtual controller::IScriptEditorController^ NewController(model::IFactory^ ModelFactory, view::IFactory^ ViewFactory);
	virtual controller::IScriptEditorController^ NewController(model::IFactory^ ModelFactory, view::IFactory^ ViewFactory, IScriptEditorController::InstantiationParams^ InitParams);

	static ScriptEditorControllerFactory^ NewFactory();
};


} // namespace controllerImpl


} // namespace scriptEditor


} // namespace cse