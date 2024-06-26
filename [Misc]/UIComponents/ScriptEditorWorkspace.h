﻿#pragma once
#include "ScriptSelectionDialog.h"
#include "ScriptSyncDialog.h"
#include "PreferencesDialog.h"

namespace UIComponents {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace DevComponents::DotNetBar;

	/// <summary>
	/// Summary for ScriptEditorWorkspace
	/// </summary>
	public ref class ScriptEditorWorkspace : public Metro::MetroForm
	{
	public:
		ScriptEditorWorkspace(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ScriptEditorWorkspace()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: DevComponents::DotNetBar::SuperTabControl^ MainTabStrip;


	private: DevComponents::DotNetBar::Bar^ ContainerMainToolbar;

	private: DevComponents::DotNetBar::ButtonItem^ ToolbarNewScript;
	private: DevComponents::DotNetBar::ButtonItem^ ToolbarOpenScript;
	private: DevComponents::DotNetBar::ButtonItem^ ToolbarSaveScriptDropdown;

	private: DevComponents::DotNetBar::ButtonItem^ ToolbarSaveScriptAndActivePlugin;
	private: DevComponents::DotNetBar::ButtonItem^ ToolbarSaveScriptNoCompile;
	private: DevComponents::DotNetBar::ButtonItem^ ToolbarPreviousScript;
	private: DevComponents::DotNetBar::ButtonItem^ ToolbarNextScript;

	private: DevComponents::DotNetBar::ButtonItem^ ToolbarSaveAllScripts;
	private: DevComponents::DotNetBar::LabelItem^ ToolbarLabelScriptType;
	private: DevComponents::DotNetBar::ComboBoxItem^ ToolbarScriptTypeDropdown;
	private: DevComponents::DotNetBar::DotNetBarManager^ DockManager;
	private: DevComponents::DotNetBar::DockSite^ DockSiteBottom;
	private: DevComponents::DotNetBar::DockSite^ DockSiteLeftEx;
	private: DevComponents::DotNetBar::DockSite^ DockSiteRightEx;



	private: DevComponents::DotNetBar::DockSite^ DockSiteTop;
	private: DevComponents::DotNetBar::DockSite^ DockSiteLeft;
	private: DevComponents::DotNetBar::DockSite^ DockSiteRight;
	private: DevComponents::DotNetBar::DockSite^ DockSiteTopEx;
	private: DevComponents::DotNetBar::DockSite^ DockSiteBottomEx;








	private: DevComponents::Editors::ComboItem^ DropdownScriptTypeObject;
	private: DevComponents::Editors::ComboItem^ DropdownScriptTypeQuest;
	private: DevComponents::Editors::ComboItem^ DropdownScriptTypeMagicEffect;



	private: DevComponents::DotNetBar::ButtonItem^ ToolbarMenuEdit;
	private: DevComponents::DotNetBar::ButtonItem^ EditMenuFindReplace;
	private: DevComponents::DotNetBar::ButtonItem^ EditMenuGoToLine;

	private: DevComponents::DotNetBar::ButtonItem^ EditMenuAddBookmark;

	private: DevComponents::DotNetBar::ButtonItem^ ToolbarMenuView;
	private: DevComponents::DotNetBar::ButtonItem^ ViewMenuPreprocessorOutputBytecodeOffsets;


	private: DevComponents::DotNetBar::ButtonItem^ ViewMenuIconMargin;
	private: DevComponents::DotNetBar::ButtonItem^ ToolbarMenuTools;
	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuSanitiseScript;
	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuAttachScript;
	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuCompileDepends;



	private: DevComponents::DotNetBar::ButtonItem^ TextEditorContextMenuAddVar;
	private: DevComponents::DotNetBar::ButtonItem^ MenuAddVarInteger;
	private: DevComponents::DotNetBar::ButtonItem^ MenuAddVarFloat;
	private: DevComponents::DotNetBar::ButtonItem^ MenuAddVarReference;
	private: DevComponents::DotNetBar::ButtonItem^ MenuAddVarString;
	private: DevComponents::DotNetBar::ButtonItem^ MenuAddVarArray;





	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuImport;
	private: DevComponents::DotNetBar::ButtonItem^ MenuImportCurrentTab;
	private: DevComponents::DotNetBar::ButtonItem^ MenuImportMultipleTabs;
	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuExport;
	private: DevComponents::DotNetBar::ButtonItem^ MenuExportCurrentTab;
	private: DevComponents::DotNetBar::ButtonItem^ MenuExportAllTabs;
	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuCompileActiveFileScripts;


	private: DevComponents::DotNetBar::ButtonItem^ ViewMenuDarkMode;
	private: DevComponents::DotNetBar::ButtonItem^ ViewMenuMessages;
	private: DevComponents::DotNetBar::ButtonItem^ ViewMenuFindResults;
	private: DevComponents::DotNetBar::ButtonItem^ ViewMenuBookmarks;
	private: DevComponents::DotNetBar::ButtonItem^ ViewMenuGlobalFindResults;
	private: DevComponents::DotNetBar::ButtonItem^ ViewMenuOutline;
	private: DevComponents::DotNetBar::ButtonItem^ ViewMenuNavBreadcrumb;
	private: DevComponents::DotNetBar::Bar^ DockableBarFindInTabsResults;

	private: DevComponents::DotNetBar::PanelDockContainer^ PanelDockContainerBookmarks;
	private: BrightIdeasSoftware::FastObjectListView^ BookmarksList;


	private: DevComponents::DotNetBar::Bar^ BookmarksToolbar;
	private: DevComponents::DotNetBar::ButtonItem^ BookmarksToolbarAdd;
	private: DevComponents::DotNetBar::ButtonItem^ BookmarksToolbarRemove;
	private: DevComponents::DotNetBar::PanelDockContainer^ PanelDockContainerMessageList;
	private: BrightIdeasSoftware::FastObjectListView^ MessagesList;




	private: DevComponents::DotNetBar::DockContainerItem^ DockContainerItemMessageList;
	private: DevComponents::DotNetBar::DockContainerItem^ DockContainerItemBookmarks;
	private: DevComponents::DotNetBar::PanelDockContainer^ PanelDockContainerFindResults;
	private: BrightIdeasSoftware::FastObjectListView^ FindResultsList;



	private: DevComponents::DotNetBar::Bar^ FindResultsToolbar;
	private: DevComponents::DotNetBar::LabelItem^ FindResultsToolbarLabel;
	private: DevComponents::DotNetBar::LabelItem^ FindResultsListToolbarLabelQuery;
	private: DevComponents::DotNetBar::PanelDockContainer^ PanelDockContainerGlobalFindResults;
	private: BrightIdeasSoftware::TreeListView^ GlobalFindResultsList;



	private: DevComponents::DotNetBar::DockContainerItem^ DockContainerItemFindResults;
	private: DevComponents::DotNetBar::DockContainerItem^ DockContainerItemGlobalFindResults;
	private: DevComponents::DotNetBar::Bar^ DockableBarFindReplace;




	private: DevComponents::DotNetBar::PanelDockContainer^ PanelDockContainerOutline;
	private: DevComponents::DotNetBar::DockContainerItem^ DockContainerItemOutline;

	private: DevComponents::DotNetBar::PanelDockContainer^ PanelDockContainerFindReplace;
	private: DevComponents::DotNetBar::DockContainerItem^ DockContainerItemFindReplace;



















	private: BrightIdeasSoftware::TreeListView^ OutlineTreeView;
	private: DevComponents::DotNetBar::Layout::LayoutControl^ FindWindowLayoutControl;

	private: DevComponents::DotNetBar::Controls::ComboBoxEx^ FindWindowDropdownFind;
	private: DevComponents::DotNetBar::Controls::ComboBoxEx^ FindWindowDropdownReplace;
	private: DevComponents::DotNetBar::Controls::CheckBoxX^ FindWindowCheckboxMatchCase;
	private: DevComponents::DotNetBar::Controls::CheckBoxX^ FindWindowCheckboxUseRegEx;
	private: DevComponents::DotNetBar::Controls::CheckBoxX^ FindWindowCheckBoxMatchWholeWord;
	private: DevComponents::DotNetBar::Controls::ComboBoxEx^ FindWindowComboLookIn;



	private: DevComponents::DotNetBar::ButtonX^ FindWindowButtonFind;
	private: DevComponents::DotNetBar::ButtonX^ FindWindowButtonReplace;
	private: DevComponents::DotNetBar::ButtonX^ FindWindowButtonCountMatches;
	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCIFindDropdown;
	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCIReplaceDropdown;
	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCILookIn;
	private: DevComponents::DotNetBar::Layout::LayoutGroup^ FindWindowLayoutGroupSettings;
	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCIMatchCase;
	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCIMatchWholeWord;
	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCIUseRegEx;
	private: DevComponents::DotNetBar::Layout::LayoutGroup^ FindWindowLayouyGroupButtons;
	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCIFindButton;
	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCIReplaceButton;
	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCICountMatches;
	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuDeleteScripts;
	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuScriptSync;
	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuCodeSnippets;
	private: DevComponents::DotNetBar::ButtonItem^ ToolsMenuPreferences;
	private: DevComponents::DotNetBar::Bar^ StatusBar;
	private: DevComponents::DotNetBar::LabelItem^ StatusBarPreprocessorOutputFlag;
	private: DevComponents::DotNetBar::DockSite^ DockSiteCenter;
	private: DevComponents::DotNetBar::Bar^ CenterDockBar;
	private: System::Windows::Forms::Panel^ PanelDocumentContent;
	private: DevComponents::DotNetBar::CrumbBar^ NavigationBar;
	private: DevComponents::DotNetBar::SuperTabControlPanel^ DummySuperTabControlPanel2;

	private: DevComponents::DotNetBar::SuperTabItem^ AnotherDummyTabItem;
	private: DevComponents::DotNetBar::SuperTabControlPanel^ DummySuperTabControlPanel1;

	private: DevComponents::DotNetBar::SuperTabItem^ DummyTabItem;


private: DevComponents::DotNetBar::LabelItem^ StatusBarDocumentDescription;
	private: DevComponents::DotNetBar::LabelItem^ StatusBarLineNumber;
	private: DevComponents::DotNetBar::LabelItem^ StatusBarColumnNumber;
	private: DevComponents::DotNetBar::CircularProgressItem^ StatusBarScriptBytecodeLength;
	private: DevComponents::DotNetBar::ContextMenuBar^ ContextMenuProvider;
	private: DevComponents::DotNetBar::ButtonItem^ ContextMenuTextEditor;
	private: DevComponents::DotNetBar::ButtonItem^ TextEditorContextMenuCopy;
	private: DevComponents::DotNetBar::ButtonItem^ TextEditorContextMenuPaste;







	private: DevComponents::DotNetBar::ButtonItem^ ToolbarMenuHelp;
	private: DevComponents::DotNetBar::ButtonItem^ HelpMenuWiki;
	private: DevComponents::DotNetBar::ButtonItem^ HelpMenuObseDocs;

	private: DevComponents::DotNetBar::ButtonItem^ TextEditorContextMenuJumpToScript;

	private: DevComponents::DotNetBar::Bar^ DockableBarOutlineView;
	private: DevComponents::DotNetBar::Bar^ DockableBarMessages;
	private: DevComponents::DotNetBar::Bar^ DockableBarBookmarks;
	private: DevComponents::DotNetBar::Bar^ DockableBarFindReplaceResults;
	private: DevComponents::DotNetBar::Controls::CheckBoxX^ FindWindowCheckBoxIgnoreComments;

	private: DevComponents::DotNetBar::Layout::LayoutControlItem^ FindWindowLCIIgnoreComments;

private: DevComponents::DotNetBar::ButtonItem^ EditMenuComment;
private: DevComponents::DotNetBar::ButtonItem^ EditMenuUncomment;
private: DevComponents::DotNetBar::ButtonItem^ ToolbarSaveScript;
private: DevComponents::DotNetBar::PanelEx^ EmptyWorkspacePanel;
private: DevComponents::DotNetBar::ButtonX^ GetStartedButtonOpenScript;

private: DevComponents::DotNetBar::ButtonX^ GetStartedButtonNewScript;
private: DevComponents::DotNetBar::ButtonItem^ ContextMenuTabStrip;
private: DevComponents::DotNetBar::ButtonItem^ TabStripContextMenuTabLayout;
private: DevComponents::DotNetBar::ButtonItem^ TabStripContextMenuCloseAllOthers;
private: DevComponents::DotNetBar::ButtonItem^ TabStripContextMenuCloseThis;
private: DevComponents::DotNetBar::ButtonItem^ TabStripContextMenuCloseSaved;
private: DevComponents::DotNetBar::ButtonItem^ TabStripContextMenuCloseAll;
private: DevComponents::DotNetBar::ButtonItem^ MenuTabLayoutTop;
private: DevComponents::DotNetBar::ButtonItem^ MenuTabLayoutBottom;
private: DevComponents::DotNetBar::ButtonItem^ MenuTabLayoutLeft;
private: DevComponents::DotNetBar::ButtonItem^ MenuTabLayoutRight;
private: DevComponents::DotNetBar::ButtonItem^ TabStripContextMenuPopOut;
private: DevComponents::DotNetBar::Bar^ MessagesToolbar;
private: DevComponents::DotNetBar::ButtonItem^ MessagesToolbarErrors;
private: DevComponents::DotNetBar::ButtonItem^ MessagesToolbarWarnings;
private: DevComponents::DotNetBar::ButtonItem^ MessagesToolbarInfos;
private: DevComponents::DotNetBar::ButtonItem^ StatusBarErrorCount;
private: DevComponents::DotNetBar::ButtonItem^ StatusBarWarningCount;
private: DevComponents::DotNetBar::ButtonItem^ StatusBarNoIssuesIndicator;
private: DevComponents::DotNetBar::ButtonItem^ MessagesToolbarMenuSuppressedWarnings;
private: DevComponents::DotNetBar::ControlContainerItem^ MenuSuppressedWarningsListViewWrapper;

private: BrightIdeasSoftware::FastObjectListView^ SuppressibleWarningsList;
private: DevComponents::DotNetBar::ItemContainer^ MenuSuppressedWarningsListViewContainer;
















































	protected:

	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		//System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager("UIComponents.ScriptEditor-Workspace", System::Reflection::Assembly::GetExecutingAssembly());
		//

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ScriptEditorWorkspace::typeid));
			this->MainTabStrip = (gcnew DevComponents::DotNetBar::SuperTabControl());
			this->DummySuperTabControlPanel1 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->DummyTabItem = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->DummySuperTabControlPanel2 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->AnotherDummyTabItem = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->ContainerMainToolbar = (gcnew DevComponents::DotNetBar::Bar());
			this->ToolbarNewScript = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarOpenScript = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarSaveScript = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarSaveScriptDropdown = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarSaveScriptAndActivePlugin = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarSaveScriptNoCompile = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarSaveAllScripts = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarPreviousScript = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarNextScript = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarLabelScriptType = (gcnew DevComponents::DotNetBar::LabelItem());
			this->ToolbarScriptTypeDropdown = (gcnew DevComponents::DotNetBar::ComboBoxItem());
			this->DropdownScriptTypeObject = (gcnew DevComponents::Editors::ComboItem());
			this->DropdownScriptTypeQuest = (gcnew DevComponents::Editors::ComboItem());
			this->DropdownScriptTypeMagicEffect = (gcnew DevComponents::Editors::ComboItem());
			this->ToolbarMenuEdit = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->EditMenuFindReplace = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->EditMenuGoToLine = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->EditMenuAddBookmark = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->EditMenuComment = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->EditMenuUncomment = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarMenuView = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ViewMenuPreprocessorOutputBytecodeOffsets = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ViewMenuMessages = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ViewMenuBookmarks = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ViewMenuOutline = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ViewMenuFindResults = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ViewMenuGlobalFindResults = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ViewMenuNavBreadcrumb = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ViewMenuIconMargin = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ViewMenuDarkMode = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarMenuTools = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuSanitiseScript = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuAttachScript = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuCompileDepends = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuImport = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuImportCurrentTab = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuImportMultipleTabs = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuExport = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuExportCurrentTab = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuExportAllTabs = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuCompileActiveFileScripts = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuDeleteScripts = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuScriptSync = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuCodeSnippets = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolsMenuPreferences = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ToolbarMenuHelp = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->HelpMenuWiki = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->HelpMenuObseDocs = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TextEditorContextMenuAddVar = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuAddVarInteger = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuAddVarFloat = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuAddVarReference = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuAddVarString = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuAddVarArray = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->DockManager = (gcnew DevComponents::DotNetBar::DotNetBarManager(this->components));
			this->DockSiteBottom = (gcnew DevComponents::DotNetBar::DockSite());
			this->DockableBarMessages = (gcnew DevComponents::DotNetBar::Bar());
			this->PanelDockContainerMessageList = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->MessagesList = (gcnew BrightIdeasSoftware::FastObjectListView());
			this->MessagesToolbar = (gcnew DevComponents::DotNetBar::Bar());
			this->MessagesToolbarErrors = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MessagesToolbarWarnings = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MessagesToolbarInfos = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MessagesToolbarMenuSuppressedWarnings = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->DockContainerItemMessageList = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->DockableBarBookmarks = (gcnew DevComponents::DotNetBar::Bar());
			this->PanelDockContainerBookmarks = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->BookmarksList = (gcnew BrightIdeasSoftware::FastObjectListView());
			this->BookmarksToolbar = (gcnew DevComponents::DotNetBar::Bar());
			this->BookmarksToolbarAdd = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->BookmarksToolbarRemove = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->DockContainerItemBookmarks = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->DockableBarFindReplaceResults = (gcnew DevComponents::DotNetBar::Bar());
			this->PanelDockContainerFindResults = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->FindResultsList = (gcnew BrightIdeasSoftware::FastObjectListView());
			this->FindResultsToolbar = (gcnew DevComponents::DotNetBar::Bar());
			this->FindResultsToolbarLabel = (gcnew DevComponents::DotNetBar::LabelItem());
			this->FindResultsListToolbarLabelQuery = (gcnew DevComponents::DotNetBar::LabelItem());
			this->DockContainerItemFindResults = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->DockableBarFindInTabsResults = (gcnew DevComponents::DotNetBar::Bar());
			this->PanelDockContainerGlobalFindResults = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->GlobalFindResultsList = (gcnew BrightIdeasSoftware::TreeListView());
			this->DockContainerItemGlobalFindResults = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->DockSiteLeftEx = (gcnew DevComponents::DotNetBar::DockSite());
			this->DockableBarOutlineView = (gcnew DevComponents::DotNetBar::Bar());
			this->PanelDockContainerOutline = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->OutlineTreeView = (gcnew BrightIdeasSoftware::TreeListView());
			this->DockContainerItemOutline = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->DockSiteRightEx = (gcnew DevComponents::DotNetBar::DockSite());
			this->DockableBarFindReplace = (gcnew DevComponents::DotNetBar::Bar());
			this->PanelDockContainerFindReplace = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->FindWindowLayoutControl = (gcnew DevComponents::DotNetBar::Layout::LayoutControl());
			this->FindWindowDropdownFind = (gcnew DevComponents::DotNetBar::Controls::ComboBoxEx());
			this->FindWindowDropdownReplace = (gcnew DevComponents::DotNetBar::Controls::ComboBoxEx());
			this->FindWindowComboLookIn = (gcnew DevComponents::DotNetBar::Controls::ComboBoxEx());
			this->FindWindowCheckboxMatchCase = (gcnew DevComponents::DotNetBar::Controls::CheckBoxX());
			this->FindWindowCheckboxUseRegEx = (gcnew DevComponents::DotNetBar::Controls::CheckBoxX());
			this->FindWindowCheckBoxMatchWholeWord = (gcnew DevComponents::DotNetBar::Controls::CheckBoxX());
			this->FindWindowCheckBoxIgnoreComments = (gcnew DevComponents::DotNetBar::Controls::CheckBoxX());
			this->FindWindowButtonFind = (gcnew DevComponents::DotNetBar::ButtonX());
			this->FindWindowButtonReplace = (gcnew DevComponents::DotNetBar::ButtonX());
			this->FindWindowButtonCountMatches = (gcnew DevComponents::DotNetBar::ButtonX());
			this->FindWindowLCIFindDropdown = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->FindWindowLCIReplaceDropdown = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->FindWindowLCILookIn = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->FindWindowLayoutGroupSettings = (gcnew DevComponents::DotNetBar::Layout::LayoutGroup());
			this->FindWindowLCIMatchCase = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->FindWindowLCIMatchWholeWord = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->FindWindowLCIUseRegEx = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->FindWindowLCIIgnoreComments = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->FindWindowLayouyGroupButtons = (gcnew DevComponents::DotNetBar::Layout::LayoutGroup());
			this->FindWindowLCIFindButton = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->FindWindowLCIReplaceButton = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->FindWindowLCICountMatches = (gcnew DevComponents::DotNetBar::Layout::LayoutControlItem());
			this->DockContainerItemFindReplace = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->DockSiteBottomEx = (gcnew DevComponents::DotNetBar::DockSite());
			this->DockSiteLeft = (gcnew DevComponents::DotNetBar::DockSite());
			this->DockSiteRight = (gcnew DevComponents::DotNetBar::DockSite());
			this->DockSiteTopEx = (gcnew DevComponents::DotNetBar::DockSite());
			this->DockSiteTop = (gcnew DevComponents::DotNetBar::DockSite());
			this->DockSiteCenter = (gcnew DevComponents::DotNetBar::DockSite());
			this->CenterDockBar = (gcnew DevComponents::DotNetBar::Bar());
			this->PanelDocumentContent = (gcnew System::Windows::Forms::Panel());
			this->EmptyWorkspacePanel = (gcnew DevComponents::DotNetBar::PanelEx());
			this->GetStartedButtonOpenScript = (gcnew DevComponents::DotNetBar::ButtonX());
			this->GetStartedButtonNewScript = (gcnew DevComponents::DotNetBar::ButtonX());
			this->ContextMenuProvider = (gcnew DevComponents::DotNetBar::ContextMenuBar());
			this->ContextMenuTabStrip = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TabStripContextMenuCloseThis = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TabStripContextMenuCloseAllOthers = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TabStripContextMenuCloseSaved = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TabStripContextMenuCloseAll = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TabStripContextMenuPopOut = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TabStripContextMenuTabLayout = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuTabLayoutTop = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuTabLayoutBottom = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuTabLayoutLeft = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->MenuTabLayoutRight = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ContextMenuTextEditor = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TextEditorContextMenuCopy = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TextEditorContextMenuPaste = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TextEditorContextMenuJumpToScript = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->NavigationBar = (gcnew DevComponents::DotNetBar::CrumbBar());
			this->StatusBar = (gcnew DevComponents::DotNetBar::Bar());
			this->StatusBarDocumentDescription = (gcnew DevComponents::DotNetBar::LabelItem());
			this->StatusBarErrorCount = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->StatusBarWarningCount = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->StatusBarNoIssuesIndicator = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->StatusBarLineNumber = (gcnew DevComponents::DotNetBar::LabelItem());
			this->StatusBarColumnNumber = (gcnew DevComponents::DotNetBar::LabelItem());
			this->StatusBarPreprocessorOutputFlag = (gcnew DevComponents::DotNetBar::LabelItem());
			this->StatusBarScriptBytecodeLength = (gcnew DevComponents::DotNetBar::CircularProgressItem());
			this->SuppressibleWarningsList = (gcnew BrightIdeasSoftware::FastObjectListView());
			this->MenuSuppressedWarningsListViewWrapper = (gcnew DevComponents::DotNetBar::ControlContainerItem());
			this->MenuSuppressedWarningsListViewContainer = (gcnew DevComponents::DotNetBar::ItemContainer());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MainTabStrip))->BeginInit();
			this->MainTabStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ContainerMainToolbar))->BeginInit();
			this->DockSiteBottom->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarMessages))->BeginInit();
			this->DockableBarMessages->SuspendLayout();
			this->PanelDockContainerMessageList->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MessagesList))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MessagesToolbar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarBookmarks))->BeginInit();
			this->DockableBarBookmarks->SuspendLayout();
			this->PanelDockContainerBookmarks->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BookmarksList))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BookmarksToolbar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarFindReplaceResults))->BeginInit();
			this->DockableBarFindReplaceResults->SuspendLayout();
			this->PanelDockContainerFindResults->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FindResultsList))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FindResultsToolbar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarFindInTabsResults))->BeginInit();
			this->DockableBarFindInTabsResults->SuspendLayout();
			this->PanelDockContainerGlobalFindResults->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GlobalFindResultsList))->BeginInit();
			this->DockSiteLeftEx->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarOutlineView))->BeginInit();
			this->DockableBarOutlineView->SuspendLayout();
			this->PanelDockContainerOutline->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OutlineTreeView))->BeginInit();
			this->DockSiteRightEx->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarFindReplace))->BeginInit();
			this->DockableBarFindReplace->SuspendLayout();
			this->PanelDockContainerFindReplace->SuspendLayout();
			this->FindWindowLayoutControl->SuspendLayout();
			this->DockSiteCenter->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CenterDockBar))->BeginInit();
			this->CenterDockBar->SuspendLayout();
			this->PanelDocumentContent->SuspendLayout();
			this->EmptyWorkspacePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ContextMenuProvider))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StatusBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SuppressibleWarningsList))->BeginInit();
			this->SuspendLayout();
			// 
			// MainTabStrip
			// 
			this->MainTabStrip->BackColor = System::Drawing::Color::White;
			this->MainTabStrip->CloseButtonOnTabsAlwaysDisplayed = false;
			this->MainTabStrip->CloseButtonOnTabsVisible = true;
			this->ContextMenuProvider->SetContextMenuEx(this->MainTabStrip, this->ContextMenuTabStrip);
			// 
			// 
			// 
			// 
			// 
			// 
			this->MainTabStrip->ControlBox->CloseBox->Name = L"";
			// 
			// 
			// 
			this->MainTabStrip->ControlBox->MenuBox->AutoHide = true;
			this->MainTabStrip->ControlBox->MenuBox->Name = L"";
			this->MainTabStrip->ControlBox->MenuBox->Visible = false;
			this->MainTabStrip->ControlBox->Name = L"";
			this->MainTabStrip->ControlBox->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {
				this->MainTabStrip->ControlBox->MenuBox,
					this->MainTabStrip->ControlBox->CloseBox
			});
			this->MainTabStrip->Controls->Add(this->DummySuperTabControlPanel1);
			this->MainTabStrip->Controls->Add(this->DummySuperTabControlPanel2);
			this->MainTabStrip->Dock = System::Windows::Forms::DockStyle::Top;
			this->MainTabStrip->ForeColor = System::Drawing::Color::Black;
			this->MainTabStrip->ItemPadding->Bottom = 5;
			this->MainTabStrip->ItemPadding->Left = 5;
			this->MainTabStrip->ItemPadding->Right = 5;
			this->MainTabStrip->ItemPadding->Top = 5;
			this->MainTabStrip->Location = System::Drawing::Point(0, 0);
			this->MainTabStrip->Name = L"MainTabStrip";
			this->MainTabStrip->ReorderTabsEnabled = true;
			this->MainTabStrip->SelectedTabFont = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MainTabStrip->SelectedTabIndex = 0;
			this->MainTabStrip->Size = System::Drawing::Size(1030, 30);
			this->MainTabStrip->TabFont = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MainTabStrip->TabIndex = 1;
			this->MainTabStrip->Tabs->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) { this->DummyTabItem, this->AnotherDummyTabItem });
			this->MainTabStrip->TabStop = false;
			this->MainTabStrip->TabStyle = DevComponents::DotNetBar::eSuperTabStyle::Office2010BackstageBlue;
			this->MainTabStrip->Text = L"Suppressed Warnings";
			this->MainTabStrip->TextAlignment = DevComponents::DotNetBar::eItemAlignment::Far;
			// 
			// DummySuperTabControlPanel1
			// 
			this->DummySuperTabControlPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DummySuperTabControlPanel1->Location = System::Drawing::Point(0, 30);
			this->DummySuperTabControlPanel1->Name = L"DummySuperTabControlPanel1";
			this->DummySuperTabControlPanel1->Size = System::Drawing::Size(1030, 0);
			this->DummySuperTabControlPanel1->TabIndex = 0;
			this->DummySuperTabControlPanel1->TabItem = this->DummyTabItem;
			// 
			// DummyTabItem
			// 
			this->DummyTabItem->AttachedControl = this->DummySuperTabControlPanel1;
			this->DummyTabItem->GlobalItem = false;
			this->DummyTabItem->ImageAlignment = DevComponents::DotNetBar::ImageAlignment::MiddleCenter;
			this->DummyTabItem->Name = L"DummyTabItem";
			this->DummyTabItem->Text = L"Dummy Tab";
			// 
			// DummySuperTabControlPanel2
			// 
			this->DummySuperTabControlPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DummySuperTabControlPanel2->Location = System::Drawing::Point(0, 30);
			this->DummySuperTabControlPanel2->Name = L"DummySuperTabControlPanel2";
			this->DummySuperTabControlPanel2->Size = System::Drawing::Size(1030, 0);
			this->DummySuperTabControlPanel2->TabIndex = 0;
			this->DummySuperTabControlPanel2->TabItem = this->AnotherDummyTabItem;
			// 
			// AnotherDummyTabItem
			// 
			this->AnotherDummyTabItem->AttachedControl = this->DummySuperTabControlPanel2;
			this->AnotherDummyTabItem->GlobalItem = false;
			this->AnotherDummyTabItem->Name = L"AnotherDummyTabItem";
			this->AnotherDummyTabItem->Text = L"Yet Another Dummy Tab";
			// 
			// ContainerMainToolbar
			// 
			this->ContainerMainToolbar->AccessibleDescription = L"DotNetBar Bar (ContainerMainToolbar)";
			this->ContainerMainToolbar->AccessibleName = L"DotNetBar Bar";
			this->ContainerMainToolbar->AccessibleRole = System::Windows::Forms::AccessibleRole::MenuBar;
			this->ContainerMainToolbar->AntiAlias = true;
			this->ContainerMainToolbar->CanDockBottom = false;
			this->ContainerMainToolbar->CanDockLeft = false;
			this->ContainerMainToolbar->CanDockRight = false;
			this->ContainerMainToolbar->CanDockTab = false;
			this->ContainerMainToolbar->CanMove = false;
			this->ContainerMainToolbar->CanUndock = false;
			this->ContainerMainToolbar->Dock = System::Windows::Forms::DockStyle::Top;
			this->ContainerMainToolbar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->ContainerMainToolbar->IsMaximized = false;
			this->ContainerMainToolbar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(13) {
				this->ToolbarNewScript,
					this->ToolbarOpenScript, this->ToolbarSaveScript, this->ToolbarSaveScriptDropdown, this->ToolbarSaveAllScripts, this->ToolbarPreviousScript,
					this->ToolbarNextScript, this->ToolbarLabelScriptType, this->ToolbarScriptTypeDropdown, this->ToolbarMenuEdit, this->ToolbarMenuView,
					this->ToolbarMenuTools, this->ToolbarMenuHelp
			});
			this->ContainerMainToolbar->ItemSpacing = 5;
			this->ContainerMainToolbar->Location = System::Drawing::Point(0, 30);
			this->ContainerMainToolbar->Margin = System::Windows::Forms::Padding(5);
			this->ContainerMainToolbar->MenuBar = true;
			this->ContainerMainToolbar->Name = L"ContainerMainToolbar";
			this->ContainerMainToolbar->PaddingBottom = 7;
			this->ContainerMainToolbar->PaddingLeft = 0;
			this->ContainerMainToolbar->PaddingRight = 0;
			this->ContainerMainToolbar->PaddingTop = 7;
			this->ContainerMainToolbar->Size = System::Drawing::Size(1030, 40);
			this->ContainerMainToolbar->Stretch = true;
			this->ContainerMainToolbar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ContainerMainToolbar->TabIndex = 2;
			this->ContainerMainToolbar->TabStop = false;
			// 
			// ToolbarNewScript
			// 
			this->ToolbarNewScript->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarNewScript.Image")));
			this->ToolbarNewScript->ImagePaddingHorizontal = 15;
			this->ToolbarNewScript->ImagePaddingVertical = 10;
			this->ToolbarNewScript->Name = L"ToolbarNewScript";
			this->ToolbarNewScript->Text = L"New Script";
			this->ToolbarNewScript->Tooltip = L"New Script";
			// 
			// ToolbarOpenScript
			// 
			this->ToolbarOpenScript->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarOpenScript.Image")));
			this->ToolbarOpenScript->ImagePaddingHorizontal = 15;
			this->ToolbarOpenScript->ImagePaddingVertical = 10;
			this->ToolbarOpenScript->Name = L"ToolbarOpenScript";
			this->ToolbarOpenScript->Text = L"Open Script";
			this->ToolbarOpenScript->Tooltip = L"Open Script";
			// 
			// ToolbarSaveScript
			// 
			this->ToolbarSaveScript->BeginGroup = true;
			this->ToolbarSaveScript->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarSaveScript.Image")));
			this->ToolbarSaveScript->ImagePaddingHorizontal = 10;
			this->ToolbarSaveScript->ImagePosition = DevComponents::DotNetBar::eImagePosition::Right;
			this->ToolbarSaveScript->Name = L"ToolbarSaveScript";
			this->ToolbarSaveScript->Text = L"Save Script";
			this->ToolbarSaveScript->Tooltip = L"Save Script";
			// 
			// ToolbarSaveScriptDropdown
			// 
			this->ToolbarSaveScriptDropdown->AutoExpandOnClick = true;
			this->ToolbarSaveScriptDropdown->ImagePaddingHorizontal = 0;
			this->ToolbarSaveScriptDropdown->ImagePaddingVertical = 0;
			this->ToolbarSaveScriptDropdown->Name = L"ToolbarSaveScriptDropdown";
			this->ToolbarSaveScriptDropdown->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {
				this->ToolbarSaveScriptAndActivePlugin,
					this->ToolbarSaveScriptNoCompile
			});
			this->ToolbarSaveScriptDropdown->Symbol = L"58836";
			this->ToolbarSaveScriptDropdown->SymbolSet = DevComponents::DotNetBar::eSymbolSet::Material;
			this->ToolbarSaveScriptDropdown->SymbolSize = 12;
			this->ToolbarSaveScriptDropdown->Text = L"<expand/>";
			this->ToolbarSaveScriptDropdown->Tooltip = L"More Save Operations...";
			// 
			// ToolbarSaveScriptAndActivePlugin
			// 
			this->ToolbarSaveScriptAndActivePlugin->Name = L"ToolbarSaveScriptAndActivePlugin";
			this->ToolbarSaveScriptAndActivePlugin->Text = L"Save Script and Active Plugin";
			// 
			// ToolbarSaveScriptNoCompile
			// 
			this->ToolbarSaveScriptNoCompile->Name = L"ToolbarSaveScriptNoCompile";
			this->ToolbarSaveScriptNoCompile->Text = L"Save Script (Do Not Compile)";
			// 
			// ToolbarSaveAllScripts
			// 
			this->ToolbarSaveAllScripts->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarSaveAllScripts.Image")));
			this->ToolbarSaveAllScripts->ImagePaddingHorizontal = 15;
			this->ToolbarSaveAllScripts->ImagePaddingVertical = 10;
			this->ToolbarSaveAllScripts->Name = L"ToolbarSaveAllScripts";
			this->ToolbarSaveAllScripts->Text = L"Save All Open Scripts";
			this->ToolbarSaveAllScripts->Tooltip = L"Save All Open Scripts";
			// 
			// ToolbarPreviousScript
			// 
			this->ToolbarPreviousScript->BeginGroup = true;
			this->ToolbarPreviousScript->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarPreviousScript.Image")));
			this->ToolbarPreviousScript->ImagePaddingHorizontal = 15;
			this->ToolbarPreviousScript->ImagePaddingVertical = 10;
			this->ToolbarPreviousScript->Name = L"ToolbarPreviousScript";
			this->ToolbarPreviousScript->Text = L"Previous Script";
			this->ToolbarPreviousScript->Tooltip = L"Previous Script";
			// 
			// ToolbarNextScript
			// 
			this->ToolbarNextScript->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarNextScript.Image")));
			this->ToolbarNextScript->ImagePaddingHorizontal = 15;
			this->ToolbarNextScript->ImagePaddingVertical = 10;
			this->ToolbarNextScript->Name = L"ToolbarNextScript";
			this->ToolbarNextScript->Text = L"Next Script";
			this->ToolbarNextScript->Tooltip = L"Next Script";
			// 
			// ToolbarLabelScriptType
			// 
			this->ToolbarLabelScriptType->BeginGroup = true;
			this->ToolbarLabelScriptType->ItemAlignment = DevComponents::DotNetBar::eItemAlignment::Center;
			this->ToolbarLabelScriptType->Name = L"ToolbarLabelScriptType";
			this->ToolbarLabelScriptType->PaddingLeft = 5;
			this->ToolbarLabelScriptType->Text = L"Script Type";
			// 
			// ToolbarScriptTypeDropdown
			// 
			this->ToolbarScriptTypeDropdown->ComboWidth = 150;
			this->ToolbarScriptTypeDropdown->DropDownHeight = 106;
			this->ToolbarScriptTypeDropdown->DropDownWidth = 150;
			this->ToolbarScriptTypeDropdown->ItemHeight = 18;
			this->ToolbarScriptTypeDropdown->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				this->DropdownScriptTypeObject,
					this->DropdownScriptTypeQuest, this->DropdownScriptTypeMagicEffect
			});
			this->ToolbarScriptTypeDropdown->Name = L"ToolbarScriptTypeDropdown";
			// 
			// DropdownScriptTypeObject
			// 
			this->DropdownScriptTypeObject->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropdownScriptTypeObject.Image")));
			this->DropdownScriptTypeObject->Text = L"Object Script";
			// 
			// DropdownScriptTypeQuest
			// 
			this->DropdownScriptTypeQuest->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropdownScriptTypeQuest.Image")));
			this->DropdownScriptTypeQuest->Text = L"Quest Script";
			// 
			// DropdownScriptTypeMagicEffect
			// 
			this->DropdownScriptTypeMagicEffect->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropdownScriptTypeMagicEffect.Image")));
			this->DropdownScriptTypeMagicEffect->Text = L"Magic Effect Script";
			// 
			// ToolbarMenuEdit
			// 
			this->ToolbarMenuEdit->AutoExpandOnClick = true;
			this->ToolbarMenuEdit->BeginGroup = true;
			this->ToolbarMenuEdit->ImageFixedSize = System::Drawing::Size(12, 12);
			this->ToolbarMenuEdit->ImagePaddingHorizontal = 15;
			this->ToolbarMenuEdit->ImagePaddingVertical = 10;
			this->ToolbarMenuEdit->ItemAlignment = DevComponents::DotNetBar::eItemAlignment::Center;
			this->ToolbarMenuEdit->Name = L"ToolbarMenuEdit";
			this->ToolbarMenuEdit->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(5) {
				this->EditMenuFindReplace,
					this->EditMenuGoToLine, this->EditMenuAddBookmark, this->EditMenuComment, this->EditMenuUncomment
			});
			this->ToolbarMenuEdit->Text = L"&EDIT";
			// 
			// EditMenuFindReplace
			// 
			this->EditMenuFindReplace->AlternateShortCutText = L"Ctrl+Shift+F";
			this->EditMenuFindReplace->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"EditMenuFindReplace.Image")));
			this->EditMenuFindReplace->Name = L"EditMenuFindReplace";
			this->EditMenuFindReplace->Text = L"&Find and Replace";
			// 
			// EditMenuGoToLine
			// 
			this->EditMenuGoToLine->AlternateShortCutText = L"Ctrl + G";
			this->EditMenuGoToLine->BeginGroup = true;
			this->EditMenuGoToLine->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"EditMenuGoToLine.Image")));
			this->EditMenuGoToLine->Name = L"EditMenuGoToLine";
			this->EditMenuGoToLine->Text = L"Go To &Line";
			// 
			// EditMenuAddBookmark
			// 
			this->EditMenuAddBookmark->AlternateShortCutText = L"Ctrl + B";
			this->EditMenuAddBookmark->BeginGroup = true;
			this->EditMenuAddBookmark->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"EditMenuAddBookmark.Image")));
			this->EditMenuAddBookmark->Name = L"EditMenuAddBookmark";
			this->EditMenuAddBookmark->Text = L"Add &Bookmark";
			// 
			// EditMenuComment
			// 
			this->EditMenuComment->BeginGroup = true;
			this->EditMenuComment->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"EditMenuComment.Image")));
			this->EditMenuComment->Name = L"EditMenuComment";
			this->EditMenuComment->Text = L"&Comment Selection";
			// 
			// EditMenuUncomment
			// 
			this->EditMenuUncomment->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"EditMenuUncomment.Image")));
			this->EditMenuUncomment->Name = L"EditMenuUncomment";
			this->EditMenuUncomment->Text = L"&Uncomment Selection";
			// 
			// ToolbarMenuView
			// 
			this->ToolbarMenuView->AutoExpandOnClick = true;
			this->ToolbarMenuView->ImageFixedSize = System::Drawing::Size(12, 12);
			this->ToolbarMenuView->Name = L"ToolbarMenuView";
			this->ToolbarMenuView->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(9) {
				this->ViewMenuPreprocessorOutputBytecodeOffsets,
					this->ViewMenuMessages, this->ViewMenuBookmarks, this->ViewMenuOutline, this->ViewMenuFindResults, this->ViewMenuGlobalFindResults,
					this->ViewMenuNavBreadcrumb, this->ViewMenuIconMargin, this->ViewMenuDarkMode
			});
			this->ToolbarMenuView->Text = L"&VIEW";
			// 
			// ViewMenuPreprocessorOutputBytecodeOffsets
			// 
			this->ViewMenuPreprocessorOutputBytecodeOffsets->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewMenuPreprocessorOutputBytecodeOffsets.Image")));
			this->ViewMenuPreprocessorOutputBytecodeOffsets->Name = L"ViewMenuPreprocessorOutputBytecodeOffsets";
			this->ViewMenuPreprocessorOutputBytecodeOffsets->Text = L"&Preprocessed Script Text &amp;<br/>Script Bytecode Offsets";
			// 
			// ViewMenuMessages
			// 
			this->ViewMenuMessages->BeginGroup = true;
			this->ViewMenuMessages->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewMenuMessages.Image")));
			this->ViewMenuMessages->Name = L"ViewMenuMessages";
			this->ViewMenuMessages->Text = L"&Messages";
			// 
			// ViewMenuBookmarks
			// 
			this->ViewMenuBookmarks->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewMenuBookmarks.Image")));
			this->ViewMenuBookmarks->Name = L"ViewMenuBookmarks";
			this->ViewMenuBookmarks->Text = L"&Bookmarks";
			// 
			// ViewMenuOutline
			// 
			this->ViewMenuOutline->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewMenuOutline.Image")));
			this->ViewMenuOutline->Name = L"ViewMenuOutline";
			this->ViewMenuOutline->Text = L"&Outline View";
			// 
			// ViewMenuFindResults
			// 
			this->ViewMenuFindResults->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewMenuFindResults.Image")));
			this->ViewMenuFindResults->Name = L"ViewMenuFindResults";
			this->ViewMenuFindResults->Text = L"&Find and Replace Results";
			// 
			// ViewMenuGlobalFindResults
			// 
			this->ViewMenuGlobalFindResults->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewMenuGlobalFindResults.Image")));
			this->ViewMenuGlobalFindResults->Name = L"ViewMenuGlobalFindResults";
			this->ViewMenuGlobalFindResults->Text = L"Find in &Tabs Results";
			// 
			// ViewMenuNavBreadcrumb
			// 
			this->ViewMenuNavBreadcrumb->BeginGroup = true;
			this->ViewMenuNavBreadcrumb->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewMenuNavBreadcrumb.Image")));
			this->ViewMenuNavBreadcrumb->Name = L"ViewMenuNavBreadcrumb";
			this->ViewMenuNavBreadcrumb->Text = L"&Navigation Bar";
			// 
			// ViewMenuIconMargin
			// 
			this->ViewMenuIconMargin->Name = L"ViewMenuIconMargin";
			this->ViewMenuIconMargin->Text = L"&Icon Margin";
			// 
			// ViewMenuDarkMode
			// 
			this->ViewMenuDarkMode->BeginGroup = true;
			this->ViewMenuDarkMode->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewMenuDarkMode.Image")));
			this->ViewMenuDarkMode->Name = L"ViewMenuDarkMode";
			this->ViewMenuDarkMode->Text = L"&Dark Mode";
			// 
			// ToolbarMenuTools
			// 
			this->ToolbarMenuTools->AutoExpandOnClick = true;
			this->ToolbarMenuTools->Name = L"ToolbarMenuTools";
			this->ToolbarMenuTools->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(10) {
				this->ToolsMenuSanitiseScript,
					this->ToolsMenuAttachScript, this->ToolsMenuCompileDepends, this->ToolsMenuImport, this->ToolsMenuExport, this->ToolsMenuCompileActiveFileScripts,
					this->ToolsMenuDeleteScripts, this->ToolsMenuScriptSync, this->ToolsMenuCodeSnippets, this->ToolsMenuPreferences
			});
			this->ToolbarMenuTools->Text = L"&TOOLS";
			// 
			// ToolsMenuSanitiseScript
			// 
			this->ToolsMenuSanitiseScript->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolsMenuSanitiseScript.Image")));
			this->ToolsMenuSanitiseScript->Name = L"ToolsMenuSanitiseScript";
			this->ToolsMenuSanitiseScript->Text = L"&Sanitise Script";
			// 
			// ToolsMenuAttachScript
			// 
			this->ToolsMenuAttachScript->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolsMenuAttachScript.Image")));
			this->ToolsMenuAttachScript->Name = L"ToolsMenuAttachScript";
			this->ToolsMenuAttachScript->Text = L"&Attach Script...";
			// 
			// ToolsMenuCompileDepends
			// 
			this->ToolsMenuCompileDepends->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolsMenuCompileDepends.Image")));
			this->ToolsMenuCompileDepends->Name = L"ToolsMenuCompileDepends";
			this->ToolsMenuCompileDepends->Text = L"Recompile Script &Dependencies";
			// 
			// ToolsMenuImport
			// 
			this->ToolsMenuImport->BeginGroup = true;
			this->ToolsMenuImport->Name = L"ToolsMenuImport";
			this->ToolsMenuImport->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {
				this->MenuImportCurrentTab,
					this->MenuImportMultipleTabs
			});
			this->ToolsMenuImport->Text = L"&Import";
			// 
			// MenuImportCurrentTab
			// 
			this->MenuImportCurrentTab->Name = L"MenuImportCurrentTab";
			this->MenuImportCurrentTab->Text = L"Import File into &Current Script";
			// 
			// MenuImportMultipleTabs
			// 
			this->MenuImportMultipleTabs->Name = L"MenuImportMultipleTabs";
			this->MenuImportMultipleTabs->Text = L"Import &Multiple Files...";
			// 
			// ToolsMenuExport
			// 
			this->ToolsMenuExport->Name = L"ToolsMenuExport";
			this->ToolsMenuExport->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {
				this->MenuExportCurrentTab,
					this->MenuExportAllTabs
			});
			this->ToolsMenuExport->Text = L"&Export";
			// 
			// MenuExportCurrentTab
			// 
			this->MenuExportCurrentTab->Name = L"MenuExportCurrentTab";
			this->MenuExportCurrentTab->Text = L"Save &Current Script to Disk";
			// 
			// MenuExportAllTabs
			// 
			this->MenuExportAllTabs->Name = L"MenuExportAllTabs";
			this->MenuExportAllTabs->Text = L"Save &All Open Scripts to Disk";
			// 
			// ToolsMenuCompileActiveFileScripts
			// 
			this->ToolsMenuCompileActiveFileScripts->BeginGroup = true;
			this->ToolsMenuCompileActiveFileScripts->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolsMenuCompileActiveFileScripts.Image")));
			this->ToolsMenuCompileActiveFileScripts->Name = L"ToolsMenuCompileActiveFileScripts";
			this->ToolsMenuCompileActiveFileScripts->Text = L"Recompile All Scripts in Active &File";
			// 
			// ToolsMenuDeleteScripts
			// 
			this->ToolsMenuDeleteScripts->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolsMenuDeleteScripts.Image")));
			this->ToolsMenuDeleteScripts->Name = L"ToolsMenuDeleteScripts";
			this->ToolsMenuDeleteScripts->Text = L"&Delete Scripts...";
			// 
			// ToolsMenuScriptSync
			// 
			this->ToolsMenuScriptSync->BeginGroup = true;
			this->ToolsMenuScriptSync->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolsMenuScriptSync.Image")));
			this->ToolsMenuScriptSync->Name = L"ToolsMenuScriptSync";
			this->ToolsMenuScriptSync->Text = L"S&ync Scripts to Disk...";
			// 
			// ToolsMenuCodeSnippets
			// 
			this->ToolsMenuCodeSnippets->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolsMenuCodeSnippets.Image")));
			this->ToolsMenuCodeSnippets->Name = L"ToolsMenuCodeSnippets";
			this->ToolsMenuCodeSnippets->Text = L"Code &Snippets...";
			// 
			// ToolsMenuPreferences
			// 
			this->ToolsMenuPreferences->BeginGroup = true;
			this->ToolsMenuPreferences->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolsMenuPreferences.Image")));
			this->ToolsMenuPreferences->Name = L"ToolsMenuPreferences";
			this->ToolsMenuPreferences->Text = L"Script Editor &Preferences...";
			// 
			// ToolbarMenuHelp
			// 
			this->ToolbarMenuHelp->AutoExpandOnClick = true;
			this->ToolbarMenuHelp->Name = L"ToolbarMenuHelp";
			this->ToolbarMenuHelp->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {
				this->HelpMenuWiki,
					this->HelpMenuObseDocs
			});
			this->ToolbarMenuHelp->Text = L"&HELP";
			// 
			// HelpMenuWiki
			// 
			this->HelpMenuWiki->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"HelpMenuWiki.Image")));
			this->HelpMenuWiki->Name = L"HelpMenuWiki";
			this->HelpMenuWiki->Text = L"&Wiki";
			// 
			// HelpMenuObseDocs
			// 
			this->HelpMenuObseDocs->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"HelpMenuObseDocs.Image")));
			this->HelpMenuObseDocs->Name = L"HelpMenuObseDocs";
			this->HelpMenuObseDocs->Text = L"&OBSE Manual";
			// 
			// TextEditorContextMenuAddVar
			// 
			this->TextEditorContextMenuAddVar->AutoExpandOnClick = true;
			this->TextEditorContextMenuAddVar->BeginGroup = true;
			this->TextEditorContextMenuAddVar->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TextEditorContextMenuAddVar.Image")));
			this->TextEditorContextMenuAddVar->Name = L"TextEditorContextMenuAddVar";
			this->TextEditorContextMenuAddVar->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(5) {
				this->MenuAddVarInteger,
					this->MenuAddVarFloat, this->MenuAddVarReference, this->MenuAddVarString, this->MenuAddVarArray
			});
			this->TextEditorContextMenuAddVar->Text = L"Add &Variable";
			// 
			// MenuAddVarInteger
			// 
			this->MenuAddVarInteger->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::TextOnlyAlways;
			this->MenuAddVarInteger->Name = L"MenuAddVarInteger";
			this->MenuAddVarInteger->Text = L"&Integer";
			// 
			// MenuAddVarFloat
			// 
			this->MenuAddVarFloat->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::TextOnlyAlways;
			this->MenuAddVarFloat->Name = L"MenuAddVarFloat";
			this->MenuAddVarFloat->Text = L"&Float";
			// 
			// MenuAddVarReference
			// 
			this->MenuAddVarReference->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::TextOnlyAlways;
			this->MenuAddVarReference->Name = L"MenuAddVarReference";
			this->MenuAddVarReference->Text = L"&Reference";
			// 
			// MenuAddVarString
			// 
			this->MenuAddVarString->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::TextOnlyAlways;
			this->MenuAddVarString->Name = L"MenuAddVarString";
			this->MenuAddVarString->Text = L"&String";
			// 
			// MenuAddVarArray
			// 
			this->MenuAddVarArray->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::TextOnlyAlways;
			this->MenuAddVarArray->Name = L"MenuAddVarArray";
			this->MenuAddVarArray->Text = L"&Array";
			// 
			// DockManager
			// 
			this->DockManager->AllowUserBarCustomize = false;
			this->DockManager->AlwaysShowFullMenus = true;
			this->DockManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::F1);
			this->DockManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlC);
			this->DockManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlA);
			this->DockManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlV);
			this->DockManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlX);
			this->DockManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlZ);
			this->DockManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlY);
			this->DockManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::Del);
			this->DockManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::Ins);
			this->DockManager->BottomDockSite = this->DockSiteBottom;
			this->DockManager->DockSplitterSize = 7;
			this->DockManager->EnableFullSizeDock = false;
			this->DockManager->LeftDockSite = this->DockSiteLeftEx;
			this->DockManager->ParentForm = this;
			this->DockManager->PopupAnimation = DevComponents::DotNetBar::ePopupAnimation::Fade;
			this->DockManager->RightDockSite = this->DockSiteRightEx;
			this->DockManager->ShowCustomizeContextMenu = false;
			this->DockManager->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->DockManager->ToolbarBottomDockSite = this->DockSiteBottomEx;
			this->DockManager->ToolbarLeftDockSite = this->DockSiteLeft;
			this->DockManager->ToolbarRightDockSite = this->DockSiteRight;
			this->DockManager->ToolbarTopDockSite = this->DockSiteTopEx;
			this->DockManager->TopDockSite = this->DockSiteTop;
			// 
			// DockSiteBottom
			// 
			this->DockSiteBottom->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->DockSiteBottom->BackColor = System::Drawing::Color::White;
			this->DockSiteBottom->Controls->Add(this->DockableBarMessages);
			this->DockSiteBottom->Controls->Add(this->DockableBarBookmarks);
			this->DockSiteBottom->Controls->Add(this->DockableBarFindReplaceResults);
			this->DockSiteBottom->Controls->Add(this->DockableBarFindInTabsResults);
			this->DockSiteBottom->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->DockSiteBottom->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer(gcnew cli::array< DevComponents::DotNetBar::DocumentBaseContainer^  >(4) {
				(cli::safe_cast<DevComponents::DotNetBar::DocumentBaseContainer^>((gcnew DevComponents::DotNetBar::DocumentBarContainer(this->DockableBarMessages,
					396, 193)))), (cli::safe_cast<DevComponents::DotNetBar::DocumentBaseContainer^>((gcnew DevComponents::DotNetBar::DocumentBarContainer(this->DockableBarBookmarks,
						214, 193)))), (cli::safe_cast<DevComponents::DotNetBar::DocumentBaseContainer^>((gcnew DevComponents::DotNetBar::DocumentBarContainer(this->DockableBarFindReplaceResults,
							204, 193)))), (cli::safe_cast<DevComponents::DotNetBar::DocumentBaseContainer^>((gcnew DevComponents::DotNetBar::DocumentBarContainer(this->DockableBarFindInTabsResults,
								195, 193))))
			}, DevComponents::DotNetBar::eOrientation::Horizontal));
			this->DockSiteBottom->ForeColor = System::Drawing::Color::Black;
			this->DockSiteBottom->Location = System::Drawing::Point(0, 660);
			this->DockSiteBottom->Name = L"DockSiteBottom";
			this->DockSiteBottom->Size = System::Drawing::Size(1030, 200);
			this->DockSiteBottom->TabIndex = 7;
			this->DockSiteBottom->TabStop = false;
			// 
			// DockableBarMessages
			// 
			this->DockableBarMessages->AccessibleDescription = L"DotNetBar Bar (DockableBarMessages)";
			this->DockableBarMessages->AccessibleName = L"DotNetBar Bar";
			this->DockableBarMessages->AccessibleRole = System::Windows::Forms::AccessibleRole::Grouping;
			this->DockableBarMessages->AutoHide = true;
			this->DockableBarMessages->AutoSyncBarCaption = true;
			this->DockableBarMessages->BarType = DevComponents::DotNetBar::eBarType::DockWindow;
			this->DockableBarMessages->CanDockTop = false;
			this->DockableBarMessages->CanHide = true;
			this->DockableBarMessages->CloseSingleTab = true;
			this->DockableBarMessages->Controls->Add(this->PanelDockContainerMessageList);
			this->DockableBarMessages->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DockableBarMessages->GrabHandleStyle = DevComponents::DotNetBar::eGrabHandleStyle::Caption;
			this->DockableBarMessages->IsMaximized = false;
			this->DockableBarMessages->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) { this->DockContainerItemMessageList });
			this->DockableBarMessages->LayoutType = DevComponents::DotNetBar::eLayoutType::DockContainer;
			this->DockableBarMessages->Location = System::Drawing::Point(0, 7);
			this->DockableBarMessages->Name = L"DockableBarMessages";
			this->DockableBarMessages->Size = System::Drawing::Size(396, 193);
			this->DockableBarMessages->Stretch = true;
			this->DockableBarMessages->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->DockableBarMessages->TabIndex = 1;
			this->DockableBarMessages->TabStop = false;
			this->DockableBarMessages->Text = L"Messages";
			// 
			// PanelDockContainerMessageList
			// 
			this->PanelDockContainerMessageList->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->PanelDockContainerMessageList->Controls->Add(this->MessagesList);
			this->PanelDockContainerMessageList->Controls->Add(this->MessagesToolbar);
			this->PanelDockContainerMessageList->DisabledBackColor = System::Drawing::Color::Empty;
			this->PanelDockContainerMessageList->Location = System::Drawing::Point(3, 23);
			this->PanelDockContainerMessageList->Name = L"PanelDockContainerMessageList";
			this->PanelDockContainerMessageList->Size = System::Drawing::Size(390, 167);
			this->PanelDockContainerMessageList->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->PanelDockContainerMessageList->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->PanelDockContainerMessageList->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->PanelDockContainerMessageList->Style->GradientAngle = 90;
			this->PanelDockContainerMessageList->TabIndex = 0;
			// 
			// MessagesList
			// 
			this->MessagesList->BackColor = System::Drawing::Color::White;
			this->MessagesList->CellEditUseWholeCell = false;
			this->MessagesList->Cursor = System::Windows::Forms::Cursors::Default;
			this->MessagesList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->MessagesList->EmptyListMsg = L"Doesn\'t look like anything to me...";
			this->MessagesList->EmptyListMsgFont = (gcnew System::Drawing::Font(L"Segoe UI caps", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MessagesList->ForeColor = System::Drawing::Color::Black;
			this->MessagesList->FullRowSelect = true;
			this->MessagesList->HideSelection = false;
			this->MessagesList->Location = System::Drawing::Point(0, 25);
			this->MessagesList->MultiSelect = false;
			this->MessagesList->Name = L"MessagesList";
			this->MessagesList->ShowFilterMenuOnRightClick = false;
			this->MessagesList->ShowGroups = false;
			this->MessagesList->Size = System::Drawing::Size(390, 142);
			this->MessagesList->TabIndex = 0;
			this->MessagesList->TabStop = false;
			this->MessagesList->UseCompatibleStateImageBehavior = false;
			this->MessagesList->UseFiltering = true;
			this->MessagesList->View = System::Windows::Forms::View::Details;
			this->MessagesList->VirtualMode = true;
			// 
			// MessagesToolbar
			// 
			this->MessagesToolbar->AccessibleDescription = L"DotNetBar Bar (MessagesToolbar)";
			this->MessagesToolbar->AccessibleName = L"DotNetBar Bar";
			this->MessagesToolbar->AccessibleRole = System::Windows::Forms::AccessibleRole::ToolBar;
			this->MessagesToolbar->AntiAlias = true;
			this->MessagesToolbar->CanMove = false;
			this->MessagesToolbar->CanUndock = false;
			this->MessagesToolbar->Dock = System::Windows::Forms::DockStyle::Top;
			this->MessagesToolbar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->MessagesToolbar->IsMaximized = false;
			this->MessagesToolbar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(4) {
				this->MessagesToolbarErrors,
					this->MessagesToolbarWarnings, this->MessagesToolbarInfos, this->MessagesToolbarMenuSuppressedWarnings
			});
			this->MessagesToolbar->Location = System::Drawing::Point(0, 0);
			this->MessagesToolbar->Name = L"MessagesToolbar";
			this->MessagesToolbar->RoundCorners = false;
			this->MessagesToolbar->Size = System::Drawing::Size(390, 25);
			this->MessagesToolbar->Stretch = true;
			this->MessagesToolbar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->MessagesToolbar->TabIndex = 1;
			this->MessagesToolbar->TabStop = false;
			// 
			// MessagesToolbarErrors
			// 
			this->MessagesToolbarErrors->BeginGroup = true;
			this->MessagesToolbarErrors->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->MessagesToolbarErrors->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MessagesToolbarErrors.Image")));
			this->MessagesToolbarErrors->ImagePaddingHorizontal = 12;
			this->MessagesToolbarErrors->Name = L"MessagesToolbarErrors";
			this->MessagesToolbarErrors->Text = L"Errors";
			// 
			// MessagesToolbarWarnings
			// 
			this->MessagesToolbarWarnings->BeginGroup = true;
			this->MessagesToolbarWarnings->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->MessagesToolbarWarnings->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MessagesToolbarWarnings.Image")));
			this->MessagesToolbarWarnings->ImagePaddingHorizontal = 12;
			this->MessagesToolbarWarnings->Name = L"MessagesToolbarWarnings";
			this->MessagesToolbarWarnings->Text = L"Warnings";
			// 
			// MessagesToolbarInfos
			// 
			this->MessagesToolbarInfos->BeginGroup = true;
			this->MessagesToolbarInfos->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->MessagesToolbarInfos->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MessagesToolbarInfos.Image")));
			this->MessagesToolbarInfos->ImagePaddingHorizontal = 12;
			this->MessagesToolbarInfos->Name = L"MessagesToolbarInfos";
			this->MessagesToolbarInfos->Text = L"Messages";
			// 
			// MessagesToolbarMenuSuppressedWarnings
			// 
			this->MessagesToolbarMenuSuppressedWarnings->AutoExpandOnClick = true;
			this->MessagesToolbarMenuSuppressedWarnings->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->MessagesToolbarMenuSuppressedWarnings->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MessagesToolbarMenuSuppressedWarnings.Image")));
			this->MessagesToolbarMenuSuppressedWarnings->ItemAlignment = DevComponents::DotNetBar::eItemAlignment::Far;
			this->MessagesToolbarMenuSuppressedWarnings->Name = L"MessagesToolbarMenuSuppressedWarnings";
			this->MessagesToolbarMenuSuppressedWarnings->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) { this->MenuSuppressedWarningsListViewContainer });
			this->MessagesToolbarMenuSuppressedWarnings->Text = L"Suppressed Warnings";
			// 
			// DockContainerItemMessageList
			// 
			this->DockContainerItemMessageList->Control = this->PanelDockContainerMessageList;
			this->DockContainerItemMessageList->Name = L"DockContainerItemMessageList";
			this->DockContainerItemMessageList->Text = L"Messages";
			// 
			// DockableBarBookmarks
			// 
			this->DockableBarBookmarks->AccessibleDescription = L"DotNetBar Bar (DockableBarBookmarks)";
			this->DockableBarBookmarks->AccessibleName = L"DotNetBar Bar";
			this->DockableBarBookmarks->AccessibleRole = System::Windows::Forms::AccessibleRole::Grouping;
			this->DockableBarBookmarks->AutoHide = true;
			this->DockableBarBookmarks->AutoSyncBarCaption = true;
			this->DockableBarBookmarks->BarType = DevComponents::DotNetBar::eBarType::DockWindow;
			this->DockableBarBookmarks->CanDockTop = false;
			this->DockableBarBookmarks->CanHide = true;
			this->DockableBarBookmarks->CloseSingleTab = true;
			this->DockableBarBookmarks->Controls->Add(this->PanelDockContainerBookmarks);
			this->DockableBarBookmarks->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DockableBarBookmarks->GrabHandleStyle = DevComponents::DotNetBar::eGrabHandleStyle::Caption;
			this->DockableBarBookmarks->IsMaximized = false;
			this->DockableBarBookmarks->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) { this->DockContainerItemBookmarks });
			this->DockableBarBookmarks->LayoutType = DevComponents::DotNetBar::eLayoutType::DockContainer;
			this->DockableBarBookmarks->Location = System::Drawing::Point(403, 7);
			this->DockableBarBookmarks->Name = L"DockableBarBookmarks";
			this->DockableBarBookmarks->Size = System::Drawing::Size(214, 193);
			this->DockableBarBookmarks->Stretch = true;
			this->DockableBarBookmarks->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->DockableBarBookmarks->TabIndex = 2;
			this->DockableBarBookmarks->TabStop = false;
			this->DockableBarBookmarks->Text = L"Bookmarks";
			// 
			// PanelDockContainerBookmarks
			// 
			this->PanelDockContainerBookmarks->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->PanelDockContainerBookmarks->Controls->Add(this->BookmarksList);
			this->PanelDockContainerBookmarks->Controls->Add(this->BookmarksToolbar);
			this->PanelDockContainerBookmarks->DisabledBackColor = System::Drawing::Color::Empty;
			this->PanelDockContainerBookmarks->Location = System::Drawing::Point(3, 23);
			this->PanelDockContainerBookmarks->Name = L"PanelDockContainerBookmarks";
			this->PanelDockContainerBookmarks->Size = System::Drawing::Size(208, 167);
			this->PanelDockContainerBookmarks->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->PanelDockContainerBookmarks->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->PanelDockContainerBookmarks->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->PanelDockContainerBookmarks->Style->GradientAngle = 90;
			this->PanelDockContainerBookmarks->TabIndex = 5;
			// 
			// BookmarksList
			// 
			this->BookmarksList->BackColor = System::Drawing::Color::White;
			this->BookmarksList->CellEditUseWholeCell = false;
			this->BookmarksList->Cursor = System::Windows::Forms::Cursors::Default;
			this->BookmarksList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BookmarksList->EmptyListMsg = L"Doesn\'t look like anything to me...";
			this->BookmarksList->EmptyListMsgFont = (gcnew System::Drawing::Font(L"Segoe UI caps", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->BookmarksList->ForeColor = System::Drawing::Color::Black;
			this->BookmarksList->FullRowSelect = true;
			this->BookmarksList->HideSelection = false;
			this->BookmarksList->Location = System::Drawing::Point(28, 0);
			this->BookmarksList->MultiSelect = false;
			this->BookmarksList->Name = L"BookmarksList";
			this->BookmarksList->ShowGroups = false;
			this->BookmarksList->Size = System::Drawing::Size(180, 167);
			this->BookmarksList->TabIndex = 0;
			this->BookmarksList->TabStop = false;
			this->BookmarksList->UseCompatibleStateImageBehavior = false;
			this->BookmarksList->View = System::Windows::Forms::View::Details;
			this->BookmarksList->VirtualMode = true;
			// 
			// BookmarksToolbar
			// 
			this->BookmarksToolbar->AntiAlias = true;
			this->BookmarksToolbar->CanMove = false;
			this->BookmarksToolbar->CanUndock = false;
			this->BookmarksToolbar->Dock = System::Windows::Forms::DockStyle::Left;
			this->BookmarksToolbar->DockOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->BookmarksToolbar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->BookmarksToolbar->IsMaximized = false;
			this->BookmarksToolbar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {
				this->BookmarksToolbarAdd,
					this->BookmarksToolbarRemove
			});
			this->BookmarksToolbar->ItemSpacing = 5;
			this->BookmarksToolbar->Location = System::Drawing::Point(0, 0);
			this->BookmarksToolbar->Name = L"BookmarksToolbar";
			this->BookmarksToolbar->RoundCorners = false;
			this->BookmarksToolbar->Size = System::Drawing::Size(28, 167);
			this->BookmarksToolbar->Stretch = true;
			this->BookmarksToolbar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->BookmarksToolbar->TabIndex = 0;
			this->BookmarksToolbar->TabStop = false;
			// 
			// BookmarksToolbarAdd
			// 
			this->BookmarksToolbarAdd->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BookmarksToolbarAdd.Image")));
			this->BookmarksToolbarAdd->ImagePaddingHorizontal = 15;
			this->BookmarksToolbarAdd->ImagePaddingVertical = 10;
			this->BookmarksToolbarAdd->Name = L"BookmarksToolbarAdd";
			this->BookmarksToolbarAdd->Text = L"Add Bookmark on the Current Line";
			this->BookmarksToolbarAdd->Tooltip = L"Add Bookmark on the Current Line";
			// 
			// BookmarksToolbarRemove
			// 
			this->BookmarksToolbarRemove->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BookmarksToolbarRemove.Image")));
			this->BookmarksToolbarRemove->ImagePaddingHorizontal = 15;
			this->BookmarksToolbarRemove->ImagePaddingVertical = 10;
			this->BookmarksToolbarRemove->Name = L"BookmarksToolbarRemove";
			this->BookmarksToolbarRemove->Text = L"Remove Selected Bookmark";
			this->BookmarksToolbarRemove->Tooltip = L"Remove Selected Bookmark";
			// 
			// DockContainerItemBookmarks
			// 
			this->DockContainerItemBookmarks->Control = this->PanelDockContainerBookmarks;
			this->DockContainerItemBookmarks->Name = L"DockContainerItemBookmarks";
			this->DockContainerItemBookmarks->Text = L"Bookmarks";
			// 
			// DockableBarFindReplaceResults
			// 
			this->DockableBarFindReplaceResults->AccessibleDescription = L"DotNetBar Bar (DockableBarFindReplaceResults)";
			this->DockableBarFindReplaceResults->AccessibleName = L"DotNetBar Bar";
			this->DockableBarFindReplaceResults->AccessibleRole = System::Windows::Forms::AccessibleRole::Grouping;
			this->DockableBarFindReplaceResults->AutoHide = true;
			this->DockableBarFindReplaceResults->AutoSyncBarCaption = true;
			this->DockableBarFindReplaceResults->BarType = DevComponents::DotNetBar::eBarType::DockWindow;
			this->DockableBarFindReplaceResults->CanDockTop = false;
			this->DockableBarFindReplaceResults->CanHide = true;
			this->DockableBarFindReplaceResults->CloseSingleTab = true;
			this->DockableBarFindReplaceResults->Controls->Add(this->PanelDockContainerFindResults);
			this->DockableBarFindReplaceResults->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->DockableBarFindReplaceResults->GrabHandleStyle = DevComponents::DotNetBar::eGrabHandleStyle::Caption;
			this->DockableBarFindReplaceResults->IsMaximized = false;
			this->DockableBarFindReplaceResults->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) { this->DockContainerItemFindResults });
			this->DockableBarFindReplaceResults->LayoutType = DevComponents::DotNetBar::eLayoutType::DockContainer;
			this->DockableBarFindReplaceResults->Location = System::Drawing::Point(624, 7);
			this->DockableBarFindReplaceResults->Name = L"DockableBarFindReplaceResults";
			this->DockableBarFindReplaceResults->Size = System::Drawing::Size(204, 193);
			this->DockableBarFindReplaceResults->Stretch = true;
			this->DockableBarFindReplaceResults->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->DockableBarFindReplaceResults->TabIndex = 3;
			this->DockableBarFindReplaceResults->TabStop = false;
			this->DockableBarFindReplaceResults->Text = L"Find and Replace Results";
			// 
			// PanelDockContainerFindResults
			// 
			this->PanelDockContainerFindResults->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->PanelDockContainerFindResults->Controls->Add(this->FindResultsList);
			this->PanelDockContainerFindResults->Controls->Add(this->FindResultsToolbar);
			this->PanelDockContainerFindResults->DisabledBackColor = System::Drawing::Color::Empty;
			this->PanelDockContainerFindResults->Location = System::Drawing::Point(3, 23);
			this->PanelDockContainerFindResults->Name = L"PanelDockContainerFindResults";
			this->PanelDockContainerFindResults->Size = System::Drawing::Size(198, 167);
			this->PanelDockContainerFindResults->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->PanelDockContainerFindResults->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->PanelDockContainerFindResults->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->PanelDockContainerFindResults->Style->GradientAngle = 90;
			this->PanelDockContainerFindResults->TabIndex = 9;
			// 
			// FindResultsList
			// 
			this->FindResultsList->BackColor = System::Drawing::Color::White;
			this->FindResultsList->CellEditUseWholeCell = false;
			this->FindResultsList->Cursor = System::Windows::Forms::Cursors::Default;
			this->FindResultsList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->FindResultsList->EmptyListMsg = L"Doesn\'t look like anything to me...";
			this->FindResultsList->EmptyListMsgFont = (gcnew System::Drawing::Font(L"Segoe UI caps", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->FindResultsList->ForeColor = System::Drawing::Color::Black;
			this->FindResultsList->FullRowSelect = true;
			this->FindResultsList->HideSelection = false;
			this->FindResultsList->Location = System::Drawing::Point(0, 19);
			this->FindResultsList->MultiSelect = false;
			this->FindResultsList->Name = L"FindResultsList";
			this->FindResultsList->ShowGroups = false;
			this->FindResultsList->Size = System::Drawing::Size(198, 148);
			this->FindResultsList->TabIndex = 0;
			this->FindResultsList->TabStop = false;
			this->FindResultsList->UseCompatibleStateImageBehavior = false;
			this->FindResultsList->View = System::Windows::Forms::View::Details;
			this->FindResultsList->VirtualMode = true;
			// 
			// FindResultsToolbar
			// 
			this->FindResultsToolbar->AntiAlias = true;
			this->FindResultsToolbar->Dock = System::Windows::Forms::DockStyle::Top;
			this->FindResultsToolbar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->FindResultsToolbar->IsMaximized = false;
			this->FindResultsToolbar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {
				this->FindResultsToolbarLabel,
					this->FindResultsListToolbarLabelQuery
			});
			this->FindResultsToolbar->Location = System::Drawing::Point(0, 0);
			this->FindResultsToolbar->Name = L"FindResultsToolbar";
			this->FindResultsToolbar->RoundCorners = false;
			this->FindResultsToolbar->Size = System::Drawing::Size(198, 19);
			this->FindResultsToolbar->Stretch = true;
			this->FindResultsToolbar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindResultsToolbar->TabIndex = 0;
			this->FindResultsToolbar->TabStop = false;
			this->FindResultsToolbar->Text = L"bar1";
			// 
			// FindResultsToolbarLabel
			// 
			this->FindResultsToolbarLabel->Name = L"FindResultsToolbarLabel";
			this->FindResultsToolbarLabel->Text = L"Query :";
			// 
			// FindResultsListToolbarLabelQuery
			// 
			this->FindResultsListToolbarLabelQuery->Name = L"FindResultsListToolbarLabelQuery";
			this->FindResultsListToolbarLabelQuery->Text = L"Last Find/Replace Operation";
			// 
			// DockContainerItemFindResults
			// 
			this->DockContainerItemFindResults->Control = this->PanelDockContainerFindResults;
			this->DockContainerItemFindResults->Name = L"DockContainerItemFindResults";
			this->DockContainerItemFindResults->Text = L"Find and Replace Results";
			// 
			// DockableBarFindInTabsResults
			// 
			this->DockableBarFindInTabsResults->AccessibleDescription = L"DotNetBar Bar (DockableBarFindInTabsResults)";
			this->DockableBarFindInTabsResults->AccessibleName = L"DotNetBar Bar";
			this->DockableBarFindInTabsResults->AccessibleRole = System::Windows::Forms::AccessibleRole::Grouping;
			this->DockableBarFindInTabsResults->AutoHide = true;
			this->DockableBarFindInTabsResults->AutoHideTabTextAlwaysVisible = true;
			this->DockableBarFindInTabsResults->AutoSyncBarCaption = true;
			this->DockableBarFindInTabsResults->BarType = DevComponents::DotNetBar::eBarType::DockWindow;
			this->DockableBarFindInTabsResults->CanDockTop = false;
			this->DockableBarFindInTabsResults->CanHide = true;
			this->DockableBarFindInTabsResults->CloseSingleTab = true;
			this->DockableBarFindInTabsResults->Controls->Add(this->PanelDockContainerGlobalFindResults);
			this->DockableBarFindInTabsResults->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->DockableBarFindInTabsResults->GrabHandleStyle = DevComponents::DotNetBar::eGrabHandleStyle::Caption;
			this->DockableBarFindInTabsResults->IsMaximized = false;
			this->DockableBarFindInTabsResults->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) { this->DockContainerItemGlobalFindResults });
			this->DockableBarFindInTabsResults->LayoutType = DevComponents::DotNetBar::eLayoutType::DockContainer;
			this->DockableBarFindInTabsResults->Location = System::Drawing::Point(835, 7);
			this->DockableBarFindInTabsResults->Name = L"DockableBarFindInTabsResults";
			this->DockableBarFindInTabsResults->Size = System::Drawing::Size(195, 193);
			this->DockableBarFindInTabsResults->Stretch = true;
			this->DockableBarFindInTabsResults->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->DockableBarFindInTabsResults->TabIndex = 0;
			this->DockableBarFindInTabsResults->TabStop = false;
			this->DockableBarFindInTabsResults->Text = L"Find in Tabs Results";
			// 
			// PanelDockContainerGlobalFindResults
			// 
			this->PanelDockContainerGlobalFindResults->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->PanelDockContainerGlobalFindResults->Controls->Add(this->GlobalFindResultsList);
			this->PanelDockContainerGlobalFindResults->DisabledBackColor = System::Drawing::Color::Empty;
			this->PanelDockContainerGlobalFindResults->Location = System::Drawing::Point(3, 23);
			this->PanelDockContainerGlobalFindResults->Name = L"PanelDockContainerGlobalFindResults";
			this->PanelDockContainerGlobalFindResults->Size = System::Drawing::Size(189, 167);
			this->PanelDockContainerGlobalFindResults->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->PanelDockContainerGlobalFindResults->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->PanelDockContainerGlobalFindResults->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->PanelDockContainerGlobalFindResults->Style->GradientAngle = 90;
			this->PanelDockContainerGlobalFindResults->TabIndex = 13;
			// 
			// GlobalFindResultsList
			// 
			this->GlobalFindResultsList->BackColor = System::Drawing::Color::White;
			this->GlobalFindResultsList->CellEditUseWholeCell = false;
			this->GlobalFindResultsList->Cursor = System::Windows::Forms::Cursors::Default;
			this->GlobalFindResultsList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->GlobalFindResultsList->EmptyListMsg = L"Doesn\'t look like anything to me...";
			this->GlobalFindResultsList->EmptyListMsgFont = (gcnew System::Drawing::Font(L"Segoe UI caps", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->GlobalFindResultsList->ForeColor = System::Drawing::Color::Black;
			this->GlobalFindResultsList->FullRowSelect = true;
			this->GlobalFindResultsList->HideSelection = false;
			this->GlobalFindResultsList->Location = System::Drawing::Point(0, 0);
			this->GlobalFindResultsList->MultiSelect = false;
			this->GlobalFindResultsList->Name = L"GlobalFindResultsList";
			this->GlobalFindResultsList->ShowGroups = false;
			this->GlobalFindResultsList->Size = System::Drawing::Size(189, 167);
			this->GlobalFindResultsList->TabIndex = 0;
			this->GlobalFindResultsList->TabStop = false;
			this->GlobalFindResultsList->UseCompatibleStateImageBehavior = false;
			this->GlobalFindResultsList->View = System::Windows::Forms::View::Details;
			this->GlobalFindResultsList->VirtualMode = true;
			// 
			// DockContainerItemGlobalFindResults
			// 
			this->DockContainerItemGlobalFindResults->Control = this->PanelDockContainerGlobalFindResults;
			this->DockContainerItemGlobalFindResults->Name = L"DockContainerItemGlobalFindResults";
			this->DockContainerItemGlobalFindResults->Text = L"Find in Tabs Results";
			// 
			// DockSiteLeftEx
			// 
			this->DockSiteLeftEx->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->DockSiteLeftEx->BackColor = System::Drawing::Color::White;
			this->DockSiteLeftEx->Controls->Add(this->DockableBarOutlineView);
			this->DockSiteLeftEx->Dock = System::Windows::Forms::DockStyle::Left;
			this->DockSiteLeftEx->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer(gcnew cli::array< DevComponents::DotNetBar::DocumentBaseContainer^  >(1) {
				(cli::safe_cast<DevComponents::DotNetBar::DocumentBaseContainer^>((gcnew DevComponents::DotNetBar::DocumentBarContainer(this->DockableBarOutlineView,
					156, 590))))
			}, DevComponents::DotNetBar::eOrientation::Horizontal));
			this->DockSiteLeftEx->ForeColor = System::Drawing::Color::Black;
			this->DockSiteLeftEx->Location = System::Drawing::Point(0, 70);
			this->DockSiteLeftEx->Name = L"DockSiteLeftEx";
			this->DockSiteLeftEx->Size = System::Drawing::Size(163, 590);
			this->DockSiteLeftEx->TabIndex = 4;
			this->DockSiteLeftEx->TabStop = false;
			// 
			// DockableBarOutlineView
			// 
			this->DockableBarOutlineView->AccessibleDescription = L"DotNetBar Bar (DockableBarOutlineView)";
			this->DockableBarOutlineView->AccessibleName = L"DotNetBar Bar";
			this->DockableBarOutlineView->AccessibleRole = System::Windows::Forms::AccessibleRole::Grouping;
			this->DockableBarOutlineView->AutoHide = true;
			this->DockableBarOutlineView->AutoHideTabTextAlwaysVisible = true;
			this->DockableBarOutlineView->AutoSyncBarCaption = true;
			this->DockableBarOutlineView->BarType = DevComponents::DotNetBar::eBarType::DockWindow;
			this->DockableBarOutlineView->CanDockTop = false;
			this->DockableBarOutlineView->CanHide = true;
			this->DockableBarOutlineView->CloseSingleTab = true;
			this->DockableBarOutlineView->Controls->Add(this->PanelDockContainerOutline);
			this->DockableBarOutlineView->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DockableBarOutlineView->GrabHandleStyle = DevComponents::DotNetBar::eGrabHandleStyle::Caption;
			this->DockableBarOutlineView->IsMaximized = false;
			this->DockableBarOutlineView->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) { this->DockContainerItemOutline });
			this->DockableBarOutlineView->LayoutType = DevComponents::DotNetBar::eLayoutType::DockContainer;
			this->DockableBarOutlineView->Location = System::Drawing::Point(0, 0);
			this->DockableBarOutlineView->Name = L"DockableBarOutlineView";
			this->DockableBarOutlineView->Size = System::Drawing::Size(156, 590);
			this->DockableBarOutlineView->Stretch = true;
			this->DockableBarOutlineView->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->DockableBarOutlineView->TabIndex = 0;
			this->DockableBarOutlineView->TabStop = false;
			this->DockableBarOutlineView->Text = L"Outline View";
			// 
			// PanelDockContainerOutline
			// 
			this->PanelDockContainerOutline->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->PanelDockContainerOutline->Controls->Add(this->OutlineTreeView);
			this->PanelDockContainerOutline->DisabledBackColor = System::Drawing::Color::Empty;
			this->PanelDockContainerOutline->Location = System::Drawing::Point(3, 23);
			this->PanelDockContainerOutline->Name = L"PanelDockContainerOutline";
			this->PanelDockContainerOutline->Size = System::Drawing::Size(150, 564);
			this->PanelDockContainerOutline->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->PanelDockContainerOutline->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->PanelDockContainerOutline->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->PanelDockContainerOutline->Style->GradientAngle = 90;
			this->PanelDockContainerOutline->TabIndex = 0;
			// 
			// OutlineTreeView
			// 
			this->OutlineTreeView->BackColor = System::Drawing::Color::White;
			this->OutlineTreeView->CellEditUseWholeCell = false;
			this->OutlineTreeView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->OutlineTreeView->ForeColor = System::Drawing::Color::Black;
			this->OutlineTreeView->HideSelection = false;
			this->OutlineTreeView->Location = System::Drawing::Point(0, 0);
			this->OutlineTreeView->Name = L"OutlineTreeView";
			this->OutlineTreeView->ShowGroups = false;
			this->OutlineTreeView->Size = System::Drawing::Size(150, 564);
			this->OutlineTreeView->TabIndex = 0;
			this->OutlineTreeView->TabStop = false;
			this->OutlineTreeView->UseCompatibleStateImageBehavior = false;
			this->OutlineTreeView->View = System::Windows::Forms::View::Details;
			this->OutlineTreeView->VirtualMode = true;
			// 
			// DockContainerItemOutline
			// 
			this->DockContainerItemOutline->Control = this->PanelDockContainerOutline;
			this->DockContainerItemOutline->Name = L"DockContainerItemOutline";
			this->DockContainerItemOutline->Text = L"Outline View";
			// 
			// DockSiteRightEx
			// 
			this->DockSiteRightEx->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->DockSiteRightEx->BackColor = System::Drawing::Color::White;
			this->DockSiteRightEx->Controls->Add(this->DockableBarFindReplace);
			this->DockSiteRightEx->Dock = System::Windows::Forms::DockStyle::Right;
			this->DockSiteRightEx->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer(gcnew cli::array< DevComponents::DotNetBar::DocumentBaseContainer^  >(1) {
				(cli::safe_cast<DevComponents::DotNetBar::DocumentBaseContainer^>((gcnew DevComponents::DotNetBar::DocumentBarContainer(this->DockableBarFindReplace,
					288, 590))))
			}, DevComponents::DotNetBar::eOrientation::Vertical));
			this->DockSiteRightEx->ForeColor = System::Drawing::Color::Black;
			this->DockSiteRightEx->Location = System::Drawing::Point(735, 70);
			this->DockSiteRightEx->Name = L"DockSiteRightEx";
			this->DockSiteRightEx->Size = System::Drawing::Size(295, 590);
			this->DockSiteRightEx->TabIndex = 5;
			this->DockSiteRightEx->TabStop = false;
			// 
			// DockableBarFindReplace
			// 
			this->DockableBarFindReplace->AccessibleDescription = L"DotNetBar Bar (DockableBarFindReplace)";
			this->DockableBarFindReplace->AccessibleName = L"DotNetBar Bar";
			this->DockableBarFindReplace->AccessibleRole = System::Windows::Forms::AccessibleRole::Grouping;
			this->DockableBarFindReplace->AutoHide = true;
			this->DockableBarFindReplace->AutoHideTabTextAlwaysVisible = true;
			this->DockableBarFindReplace->AutoSyncBarCaption = true;
			this->DockableBarFindReplace->BarType = DevComponents::DotNetBar::eBarType::DockWindow;
			this->DockableBarFindReplace->CanDockTop = false;
			this->DockableBarFindReplace->CanHide = true;
			this->DockableBarFindReplace->CloseSingleTab = true;
			this->DockableBarFindReplace->Controls->Add(this->PanelDockContainerFindReplace);
			this->DockableBarFindReplace->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DockableBarFindReplace->GrabHandleStyle = DevComponents::DotNetBar::eGrabHandleStyle::Caption;
			this->DockableBarFindReplace->IsMaximized = false;
			this->DockableBarFindReplace->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) { this->DockContainerItemFindReplace });
			this->DockableBarFindReplace->LayoutType = DevComponents::DotNetBar::eLayoutType::DockContainer;
			this->DockableBarFindReplace->Location = System::Drawing::Point(7, 0);
			this->DockableBarFindReplace->MinimumSize = System::Drawing::Size(300, 320);
			this->DockableBarFindReplace->Name = L"DockableBarFindReplace";
			this->DockableBarFindReplace->Size = System::Drawing::Size(300, 590);
			this->DockableBarFindReplace->Stretch = true;
			this->DockableBarFindReplace->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->DockableBarFindReplace->TabIndex = 0;
			this->DockableBarFindReplace->TabStop = false;
			this->DockableBarFindReplace->Text = L"Find and Replace";
			// 
			// PanelDockContainerFindReplace
			// 
			this->PanelDockContainerFindReplace->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->PanelDockContainerFindReplace->Controls->Add(this->FindWindowLayoutControl);
			this->PanelDockContainerFindReplace->DisabledBackColor = System::Drawing::Color::Empty;
			this->PanelDockContainerFindReplace->Location = System::Drawing::Point(3, 23);
			this->PanelDockContainerFindReplace->Name = L"PanelDockContainerFindReplace";
			this->PanelDockContainerFindReplace->Size = System::Drawing::Size(282, 564);
			this->PanelDockContainerFindReplace->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->PanelDockContainerFindReplace->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->PanelDockContainerFindReplace->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->PanelDockContainerFindReplace->Style->GradientAngle = 90;
			this->PanelDockContainerFindReplace->TabIndex = 0;
			// 
			// FindWindowLayoutControl
			// 
			this->FindWindowLayoutControl->BackColor = System::Drawing::Color::White;
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowDropdownFind);
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowDropdownReplace);
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowComboLookIn);
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowCheckboxMatchCase);
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowCheckboxUseRegEx);
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowCheckBoxMatchWholeWord);
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowCheckBoxIgnoreComments);
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowButtonFind);
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowButtonReplace);
			this->FindWindowLayoutControl->Controls->Add(this->FindWindowButtonCountMatches);
			this->FindWindowLayoutControl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->FindWindowLayoutControl->ForeColor = System::Drawing::Color::Black;
			this->FindWindowLayoutControl->Location = System::Drawing::Point(0, 0);
			this->FindWindowLayoutControl->Name = L"FindWindowLayoutControl";
			// 
			// 
			// 
			this->FindWindowLayoutControl->RootGroup->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::Layout::LayoutItemBase^  >(5) {
				this->FindWindowLCIFindDropdown,
					this->FindWindowLCIReplaceDropdown, this->FindWindowLCILookIn, this->FindWindowLayoutGroupSettings, this->FindWindowLayouyGroupButtons
			});
			this->FindWindowLayoutControl->Size = System::Drawing::Size(282, 564);
			this->FindWindowLayoutControl->TabIndex = 0;
			this->FindWindowLayoutControl->TabStop = false;
			// 
			// FindWindowDropdownFind
			// 
			this->FindWindowDropdownFind->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
			this->FindWindowDropdownFind->ForeColor = System::Drawing::Color::Black;
			this->FindWindowDropdownFind->ItemHeight = 17;
			this->FindWindowDropdownFind->Location = System::Drawing::Point(50, 4);
			this->FindWindowDropdownFind->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowDropdownFind->Name = L"FindWindowDropdownFind";
			this->FindWindowDropdownFind->Size = System::Drawing::Size(228, 23);
			this->FindWindowDropdownFind->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowDropdownFind->TabIndex = 0;
			// 
			// FindWindowDropdownReplace
			// 
			this->FindWindowDropdownReplace->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
			this->FindWindowDropdownReplace->ForeColor = System::Drawing::Color::Black;
			this->FindWindowDropdownReplace->ItemHeight = 17;
			this->FindWindowDropdownReplace->Location = System::Drawing::Point(50, 34);
			this->FindWindowDropdownReplace->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowDropdownReplace->Name = L"FindWindowDropdownReplace";
			this->FindWindowDropdownReplace->Size = System::Drawing::Size(228, 23);
			this->FindWindowDropdownReplace->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowDropdownReplace->TabIndex = 1;
			// 
			// FindWindowComboLookIn
			// 
			this->FindWindowComboLookIn->DisplayMember = L"Text";
			this->FindWindowComboLookIn->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
			this->FindWindowComboLookIn->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->FindWindowComboLookIn->ForeColor = System::Drawing::Color::Black;
			this->FindWindowComboLookIn->FormattingEnabled = true;
			this->FindWindowComboLookIn->ItemHeight = 17;
			this->FindWindowComboLookIn->Location = System::Drawing::Point(50, 64);
			this->FindWindowComboLookIn->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowComboLookIn->Name = L"FindWindowComboLookIn";
			this->FindWindowComboLookIn->Size = System::Drawing::Size(228, 23);
			this->FindWindowComboLookIn->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowComboLookIn->TabIndex = 2;
			// 
			// FindWindowCheckboxMatchCase
			// 
			this->FindWindowCheckboxMatchCase->BackColor = System::Drawing::Color::White;
			// 
			// 
			// 
			this->FindWindowCheckboxMatchCase->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->FindWindowCheckboxMatchCase->ForeColor = System::Drawing::Color::Black;
			this->FindWindowCheckboxMatchCase->Location = System::Drawing::Point(8, 98);
			this->FindWindowCheckboxMatchCase->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowCheckboxMatchCase->Name = L"FindWindowCheckboxMatchCase";
			this->FindWindowCheckboxMatchCase->Size = System::Drawing::Size(266, 22);
			this->FindWindowCheckboxMatchCase->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowCheckboxMatchCase->TabIndex = 3;
			this->FindWindowCheckboxMatchCase->Text = L"Match case";
			// 
			// FindWindowCheckboxUseRegEx
			// 
			this->FindWindowCheckboxUseRegEx->BackColor = System::Drawing::Color::White;
			// 
			// 
			// 
			this->FindWindowCheckboxUseRegEx->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->FindWindowCheckboxUseRegEx->ForeColor = System::Drawing::Color::Black;
			this->FindWindowCheckboxUseRegEx->Location = System::Drawing::Point(8, 158);
			this->FindWindowCheckboxUseRegEx->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowCheckboxUseRegEx->Name = L"FindWindowCheckboxUseRegEx";
			this->FindWindowCheckboxUseRegEx->Size = System::Drawing::Size(266, 22);
			this->FindWindowCheckboxUseRegEx->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowCheckboxUseRegEx->TabIndex = 5;
			this->FindWindowCheckboxUseRegEx->Text = L"Use regular expressions";
			// 
			// FindWindowCheckBoxMatchWholeWord
			// 
			this->FindWindowCheckBoxMatchWholeWord->BackColor = System::Drawing::Color::White;
			// 
			// 
			// 
			this->FindWindowCheckBoxMatchWholeWord->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->FindWindowCheckBoxMatchWholeWord->ForeColor = System::Drawing::Color::Black;
			this->FindWindowCheckBoxMatchWholeWord->Location = System::Drawing::Point(8, 128);
			this->FindWindowCheckBoxMatchWholeWord->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowCheckBoxMatchWholeWord->Name = L"FindWindowCheckBoxMatchWholeWord";
			this->FindWindowCheckBoxMatchWholeWord->Size = System::Drawing::Size(266, 22);
			this->FindWindowCheckBoxMatchWholeWord->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowCheckBoxMatchWholeWord->TabIndex = 4;
			this->FindWindowCheckBoxMatchWholeWord->Text = L"Match whole word";
			// 
			// FindWindowCheckBoxIgnoreComments
			// 
			this->FindWindowCheckBoxIgnoreComments->BackColor = System::Drawing::Color::White;
			// 
			// 
			// 
			this->FindWindowCheckBoxIgnoreComments->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->FindWindowCheckBoxIgnoreComments->ForeColor = System::Drawing::Color::Black;
			this->FindWindowCheckBoxIgnoreComments->Location = System::Drawing::Point(8, 188);
			this->FindWindowCheckBoxIgnoreComments->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowCheckBoxIgnoreComments->Name = L"FindWindowCheckBoxIgnoreComments";
			this->FindWindowCheckBoxIgnoreComments->Size = System::Drawing::Size(266, 22);
			this->FindWindowCheckBoxIgnoreComments->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowCheckBoxIgnoreComments->TabIndex = 6;
			this->FindWindowCheckBoxIgnoreComments->Text = L"Ignore comments";
			// 
			// FindWindowButtonFind
			// 
			this->FindWindowButtonFind->AccessibleRole = System::Windows::Forms::AccessibleRole::PushButton;
			this->FindWindowButtonFind->ColorTable = DevComponents::DotNetBar::eButtonColor::OrangeWithBackground;
			this->FindWindowButtonFind->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FindWindowButtonFind.Image")));
			this->FindWindowButtonFind->ImageTextSpacing = 5;
			this->FindWindowButtonFind->Location = System::Drawing::Point(8, 248);
			this->FindWindowButtonFind->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowButtonFind->Name = L"FindWindowButtonFind";
			this->FindWindowButtonFind->Size = System::Drawing::Size(129, 28);
			this->FindWindowButtonFind->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowButtonFind->TabIndex = 8;
			this->FindWindowButtonFind->Text = L"Find";
			// 
			// FindWindowButtonReplace
			// 
			this->FindWindowButtonReplace->AccessibleRole = System::Windows::Forms::AccessibleRole::PushButton;
			this->FindWindowButtonReplace->ColorTable = DevComponents::DotNetBar::eButtonColor::OrangeWithBackground;
			this->FindWindowButtonReplace->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FindWindowButtonReplace.Image")));
			this->FindWindowButtonReplace->ImageTextSpacing = 5;
			this->FindWindowButtonReplace->Location = System::Drawing::Point(145, 248);
			this->FindWindowButtonReplace->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowButtonReplace->Name = L"FindWindowButtonReplace";
			this->FindWindowButtonReplace->Size = System::Drawing::Size(129, 28);
			this->FindWindowButtonReplace->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowButtonReplace->TabIndex = 9;
			this->FindWindowButtonReplace->Text = L"Replace";
			// 
			// FindWindowButtonCountMatches
			// 
			this->FindWindowButtonCountMatches->AccessibleRole = System::Windows::Forms::AccessibleRole::PushButton;
			this->FindWindowButtonCountMatches->ColorTable = DevComponents::DotNetBar::eButtonColor::OrangeWithBackground;
			this->FindWindowButtonCountMatches->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FindWindowButtonCountMatches.Image")));
			this->FindWindowButtonCountMatches->ImageTextSpacing = 5;
			this->FindWindowButtonCountMatches->Location = System::Drawing::Point(8, 284);
			this->FindWindowButtonCountMatches->Margin = System::Windows::Forms::Padding(0);
			this->FindWindowButtonCountMatches->Name = L"FindWindowButtonCountMatches";
			this->FindWindowButtonCountMatches->Size = System::Drawing::Size(266, 28);
			this->FindWindowButtonCountMatches->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FindWindowButtonCountMatches->TabIndex = 10;
			this->FindWindowButtonCountMatches->Text = L"Count Matches";
			// 
			// FindWindowLCIFindDropdown
			// 
			this->FindWindowLCIFindDropdown->Control = this->FindWindowDropdownFind;
			this->FindWindowLCIFindDropdown->Height = 30;
			this->FindWindowLCIFindDropdown->MinSize = System::Drawing::Size(64, 18);
			this->FindWindowLCIFindDropdown->Name = L"FindWindowLCIFindDropdown";
			this->FindWindowLCIFindDropdown->Text = L"Find";
			this->FindWindowLCIFindDropdown->Width = 100;
			this->FindWindowLCIFindDropdown->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLCIReplaceDropdown
			// 
			this->FindWindowLCIReplaceDropdown->Control = this->FindWindowDropdownReplace;
			this->FindWindowLCIReplaceDropdown->Height = 30;
			this->FindWindowLCIReplaceDropdown->MinSize = System::Drawing::Size(64, 18);
			this->FindWindowLCIReplaceDropdown->Name = L"FindWindowLCIReplaceDropdown";
			this->FindWindowLCIReplaceDropdown->Text = L"Replace";
			this->FindWindowLCIReplaceDropdown->Width = 100;
			this->FindWindowLCIReplaceDropdown->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLCILookIn
			// 
			this->FindWindowLCILookIn->Control = this->FindWindowComboLookIn;
			this->FindWindowLCILookIn->Height = 30;
			this->FindWindowLCILookIn->MinSize = System::Drawing::Size(64, 18);
			this->FindWindowLCILookIn->Name = L"FindWindowLCILookIn";
			this->FindWindowLCILookIn->Text = L"Look in";
			this->FindWindowLCILookIn->Width = 100;
			this->FindWindowLCILookIn->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLayoutGroupSettings
			// 
			this->FindWindowLayoutGroupSettings->Height = 150;
			this->FindWindowLayoutGroupSettings->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::Layout::LayoutItemBase^  >(4) {
				this->FindWindowLCIMatchCase,
					this->FindWindowLCIMatchWholeWord, this->FindWindowLCIUseRegEx, this->FindWindowLCIIgnoreComments
			});
			this->FindWindowLayoutGroupSettings->MinSize = System::Drawing::Size(120, 32);
			this->FindWindowLayoutGroupSettings->Name = L"FindWindowLayoutGroupSettings";
			this->FindWindowLayoutGroupSettings->TextPosition = DevComponents::DotNetBar::Layout::eLayoutPosition::Top;
			this->FindWindowLayoutGroupSettings->Width = 100;
			this->FindWindowLayoutGroupSettings->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLCIMatchCase
			// 
			this->FindWindowLCIMatchCase->Control = this->FindWindowCheckboxMatchCase;
			this->FindWindowLCIMatchCase->Height = 30;
			this->FindWindowLCIMatchCase->MinSize = System::Drawing::Size(64, 18);
			this->FindWindowLCIMatchCase->Name = L"FindWindowLCIMatchCase";
			this->FindWindowLCIMatchCase->Width = 100;
			this->FindWindowLCIMatchCase->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLCIMatchWholeWord
			// 
			this->FindWindowLCIMatchWholeWord->Control = this->FindWindowCheckBoxMatchWholeWord;
			this->FindWindowLCIMatchWholeWord->Height = 30;
			this->FindWindowLCIMatchWholeWord->MinSize = System::Drawing::Size(64, 18);
			this->FindWindowLCIMatchWholeWord->Name = L"FindWindowLCIMatchWholeWord";
			this->FindWindowLCIMatchWholeWord->Width = 100;
			this->FindWindowLCIMatchWholeWord->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLCIUseRegEx
			// 
			this->FindWindowLCIUseRegEx->Control = this->FindWindowCheckboxUseRegEx;
			this->FindWindowLCIUseRegEx->Height = 30;
			this->FindWindowLCIUseRegEx->MinSize = System::Drawing::Size(64, 18);
			this->FindWindowLCIUseRegEx->Name = L"FindWindowLCIUseRegEx";
			this->FindWindowLCIUseRegEx->Width = 100;
			this->FindWindowLCIUseRegEx->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLCIIgnoreComments
			// 
			this->FindWindowLCIIgnoreComments->Control = this->FindWindowCheckBoxIgnoreComments;
			this->FindWindowLCIIgnoreComments->Height = 30;
			this->FindWindowLCIIgnoreComments->MinSize = System::Drawing::Size(64, 18);
			this->FindWindowLCIIgnoreComments->Name = L"FindWindowLCIIgnoreComments";
			this->FindWindowLCIIgnoreComments->Width = 100;
			this->FindWindowLCIIgnoreComments->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLayouyGroupButtons
			// 
			this->FindWindowLayouyGroupButtons->Height = 100;
			this->FindWindowLayouyGroupButtons->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::Layout::LayoutItemBase^  >(3) {
				this->FindWindowLCIFindButton,
					this->FindWindowLCIReplaceButton, this->FindWindowLCICountMatches
			});
			this->FindWindowLayouyGroupButtons->MinSize = System::Drawing::Size(120, 32);
			this->FindWindowLayouyGroupButtons->Name = L"FindWindowLayouyGroupButtons";
			this->FindWindowLayouyGroupButtons->TextPosition = DevComponents::DotNetBar::Layout::eLayoutPosition::Top;
			this->FindWindowLayouyGroupButtons->Width = 100;
			this->FindWindowLayouyGroupButtons->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLCIFindButton
			// 
			this->FindWindowLCIFindButton->Control = this->FindWindowButtonFind;
			this->FindWindowLCIFindButton->Height = 36;
			this->FindWindowLCIFindButton->MinSize = System::Drawing::Size(32, 20);
			this->FindWindowLCIFindButton->Name = L"FindWindowLCIFindButton";
			this->FindWindowLCIFindButton->Width = 50;
			this->FindWindowLCIFindButton->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLCIReplaceButton
			// 
			this->FindWindowLCIReplaceButton->Control = this->FindWindowButtonReplace;
			this->FindWindowLCIReplaceButton->Height = 36;
			this->FindWindowLCIReplaceButton->MinSize = System::Drawing::Size(32, 20);
			this->FindWindowLCIReplaceButton->Name = L"FindWindowLCIReplaceButton";
			this->FindWindowLCIReplaceButton->Width = 50;
			this->FindWindowLCIReplaceButton->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// FindWindowLCICountMatches
			// 
			this->FindWindowLCICountMatches->Control = this->FindWindowButtonCountMatches;
			this->FindWindowLCICountMatches->Height = 36;
			this->FindWindowLCICountMatches->MinSize = System::Drawing::Size(32, 20);
			this->FindWindowLCICountMatches->Name = L"FindWindowLCICountMatches";
			this->FindWindowLCICountMatches->Width = 100;
			this->FindWindowLCICountMatches->WidthType = DevComponents::DotNetBar::Layout::eLayoutSizeType::Percent;
			// 
			// DockContainerItemFindReplace
			// 
			this->DockContainerItemFindReplace->Control = this->PanelDockContainerFindReplace;
			this->DockContainerItemFindReplace->Name = L"DockContainerItemFindReplace";
			this->DockContainerItemFindReplace->Text = L"Find and Replace";
			// 
			// DockSiteBottomEx
			// 
			this->DockSiteBottomEx->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->DockSiteBottomEx->BackColor = System::Drawing::Color::White;
			this->DockSiteBottomEx->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->DockSiteBottomEx->ForeColor = System::Drawing::Color::Black;
			this->DockSiteBottomEx->Location = System::Drawing::Point(0, 860);
			this->DockSiteBottomEx->Name = L"DockSiteBottomEx";
			this->DockSiteBottomEx->Size = System::Drawing::Size(1030, 0);
			this->DockSiteBottomEx->TabIndex = 11;
			this->DockSiteBottomEx->TabStop = false;
			// 
			// DockSiteLeft
			// 
			this->DockSiteLeft->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->DockSiteLeft->BackColor = System::Drawing::Color::White;
			this->DockSiteLeft->Dock = System::Windows::Forms::DockStyle::Left;
			this->DockSiteLeft->ForeColor = System::Drawing::Color::Black;
			this->DockSiteLeft->Location = System::Drawing::Point(0, 70);
			this->DockSiteLeft->Name = L"DockSiteLeft";
			this->DockSiteLeft->Size = System::Drawing::Size(0, 790);
			this->DockSiteLeft->TabIndex = 8;
			this->DockSiteLeft->TabStop = false;
			// 
			// DockSiteRight
			// 
			this->DockSiteRight->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->DockSiteRight->BackColor = System::Drawing::Color::White;
			this->DockSiteRight->Dock = System::Windows::Forms::DockStyle::Right;
			this->DockSiteRight->ForeColor = System::Drawing::Color::Black;
			this->DockSiteRight->Location = System::Drawing::Point(1030, 70);
			this->DockSiteRight->Name = L"DockSiteRight";
			this->DockSiteRight->Size = System::Drawing::Size(0, 790);
			this->DockSiteRight->TabIndex = 9;
			this->DockSiteRight->TabStop = false;
			// 
			// DockSiteTopEx
			// 
			this->DockSiteTopEx->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->DockSiteTopEx->BackColor = System::Drawing::Color::White;
			this->DockSiteTopEx->Dock = System::Windows::Forms::DockStyle::Top;
			this->DockSiteTopEx->Enabled = false;
			this->DockSiteTopEx->ForeColor = System::Drawing::Color::Black;
			this->DockSiteTopEx->Location = System::Drawing::Point(0, 70);
			this->DockSiteTopEx->Name = L"DockSiteTopEx";
			this->DockSiteTopEx->Size = System::Drawing::Size(1030, 0);
			this->DockSiteTopEx->TabIndex = 10;
			this->DockSiteTopEx->TabStop = false;
			// 
			// DockSiteTop
			// 
			this->DockSiteTop->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->DockSiteTop->BackColor = System::Drawing::Color::White;
			this->DockSiteTop->Dock = System::Windows::Forms::DockStyle::Top;
			this->DockSiteTop->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer());
			this->DockSiteTop->Enabled = false;
			this->DockSiteTop->ForeColor = System::Drawing::Color::Black;
			this->DockSiteTop->Location = System::Drawing::Point(0, 70);
			this->DockSiteTop->Name = L"DockSiteTop";
			this->DockSiteTop->Size = System::Drawing::Size(1030, 0);
			this->DockSiteTop->TabIndex = 6;
			this->DockSiteTop->TabStop = false;
			// 
			// DockSiteCenter
			// 
			this->DockSiteCenter->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->DockSiteCenter->BackColor = System::Drawing::Color::White;
			this->DockSiteCenter->Controls->Add(this->CenterDockBar);
			this->DockSiteCenter->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DockSiteCenter->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer(gcnew cli::array< DevComponents::DotNetBar::DocumentBaseContainer^  >(1) {
				(cli::safe_cast<DevComponents::DotNetBar::DocumentBaseContainer^>((gcnew DevComponents::DotNetBar::DocumentBarContainer(this->CenterDockBar,
					572, 590))))
			}, DevComponents::DotNetBar::eOrientation::Horizontal));
			this->DockSiteCenter->ForeColor = System::Drawing::Color::Black;
			this->DockSiteCenter->Location = System::Drawing::Point(163, 70);
			this->DockSiteCenter->Name = L"DockSiteCenter";
			this->DockSiteCenter->Size = System::Drawing::Size(572, 590);
			this->DockSiteCenter->TabIndex = 12;
			this->DockSiteCenter->TabStop = false;
			// 
			// CenterDockBar
			// 
			this->CenterDockBar->AccessibleDescription = L"DotNetBar Bar (CenterDockBar)";
			this->CenterDockBar->AccessibleName = L"DotNetBar Bar";
			this->CenterDockBar->AccessibleRole = System::Windows::Forms::AccessibleRole::Grouping;
			this->CenterDockBar->BarType = DevComponents::DotNetBar::eBarType::DockWindow;
			this->CenterDockBar->CanCustomize = false;
			this->CenterDockBar->CanDockBottom = false;
			this->CenterDockBar->CanDockDocument = true;
			this->CenterDockBar->CanDockLeft = false;
			this->CenterDockBar->CanDockRight = false;
			this->CenterDockBar->CanDockTop = false;
			this->CenterDockBar->CanHide = true;
			this->CenterDockBar->CanMove = false;
			this->CenterDockBar->CanReorderTabs = false;
			this->CenterDockBar->CanUndock = false;
			this->CenterDockBar->Controls->Add(this->PanelDocumentContent);
			this->CenterDockBar->Controls->Add(this->NavigationBar);
			this->CenterDockBar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CenterDockBar->GrabHandleStyle = DevComponents::DotNetBar::eGrabHandleStyle::Caption;
			this->CenterDockBar->IsMaximized = false;
			this->CenterDockBar->LayoutType = DevComponents::DotNetBar::eLayoutType::DockContainer;
			this->CenterDockBar->Location = System::Drawing::Point(0, 0);
			this->CenterDockBar->Name = L"CenterDockBar";
			this->CenterDockBar->Size = System::Drawing::Size(572, 590);
			this->CenterDockBar->Stretch = true;
			this->CenterDockBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->CenterDockBar->TabIndex = 0;
			this->CenterDockBar->TabStop = false;
			// 
			// PanelDocumentContent
			// 
			this->PanelDocumentContent->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(211)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(211)));
			this->ContextMenuProvider->SetContextMenuEx(this->PanelDocumentContent, this->ContextMenuTextEditor);
			this->PanelDocumentContent->Controls->Add(this->EmptyWorkspacePanel);
			this->PanelDocumentContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PanelDocumentContent->ForeColor = System::Drawing::Color::Black;
			this->PanelDocumentContent->Location = System::Drawing::Point(0, 22);
			this->PanelDocumentContent->Name = L"PanelDocumentContent";
			this->PanelDocumentContent->Size = System::Drawing::Size(572, 568);
			this->PanelDocumentContent->TabIndex = 10;
			// 
			// EmptyWorkspacePanel
			// 
			this->EmptyWorkspacePanel->CanvasColor = System::Drawing::SystemColors::Control;
			this->EmptyWorkspacePanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->EmptyWorkspacePanel->Controls->Add(this->GetStartedButtonOpenScript);
			this->EmptyWorkspacePanel->Controls->Add(this->GetStartedButtonNewScript);
			this->EmptyWorkspacePanel->Controls->Add(this->ContextMenuProvider);
			this->EmptyWorkspacePanel->DisabledBackColor = System::Drawing::Color::Empty;
			this->EmptyWorkspacePanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->EmptyWorkspacePanel->Location = System::Drawing::Point(0, 0);
			this->EmptyWorkspacePanel->Name = L"EmptyWorkspacePanel";
			this->EmptyWorkspacePanel->Size = System::Drawing::Size(572, 568);
			this->EmptyWorkspacePanel->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->EmptyWorkspacePanel->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::PanelBackground;
			this->EmptyWorkspacePanel->Style->Border = DevComponents::DotNetBar::eBorderType::SingleLine;
			this->EmptyWorkspacePanel->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::PanelBorder;
			this->EmptyWorkspacePanel->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::PanelText;
			this->EmptyWorkspacePanel->Style->GradientAngle = 90;
			this->EmptyWorkspacePanel->TabIndex = 5;
			// 
			// GetStartedButtonOpenScript
			// 
			this->GetStartedButtonOpenScript->AccessibleRole = System::Windows::Forms::AccessibleRole::PushButton;
			this->GetStartedButtonOpenScript->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->GetStartedButtonOpenScript->ColorTable = DevComponents::DotNetBar::eButtonColor::OrangeWithBackground;
			this->GetStartedButtonOpenScript->ImagePosition = DevComponents::DotNetBar::eImagePosition::Top;
			this->GetStartedButtonOpenScript->ImageTextSpacing = 10;
			this->GetStartedButtonOpenScript->Location = System::Drawing::Point(105, 299);
			this->GetStartedButtonOpenScript->Name = L"GetStartedButtonOpenScript";
			this->GetStartedButtonOpenScript->Size = System::Drawing::Size(365, 144);
			this->GetStartedButtonOpenScript->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->GetStartedButtonOpenScript->Symbol = L"";
			this->GetStartedButtonOpenScript->SymbolSize = 20;
			this->GetStartedButtonOpenScript->TabIndex = 0;
			this->GetStartedButtonOpenScript->TabStop = false;
			this->GetStartedButtonOpenScript->Text = L"<font size=\"+8\">Edit an Existing Script</font>";
			// 
			// GetStartedButtonNewScript
			// 
			this->GetStartedButtonNewScript->AccessibleRole = System::Windows::Forms::AccessibleRole::PushButton;
			this->GetStartedButtonNewScript->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->GetStartedButtonNewScript->ColorTable = DevComponents::DotNetBar::eButtonColor::OrangeWithBackground;
			this->GetStartedButtonNewScript->ImagePosition = DevComponents::DotNetBar::eImagePosition::Top;
			this->GetStartedButtonNewScript->ImageTextSpacing = 10;
			this->GetStartedButtonNewScript->Location = System::Drawing::Point(105, 133);
			this->GetStartedButtonNewScript->Name = L"GetStartedButtonNewScript";
			this->GetStartedButtonNewScript->Size = System::Drawing::Size(365, 144);
			this->GetStartedButtonNewScript->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->GetStartedButtonNewScript->Symbol = L"";
			this->GetStartedButtonNewScript->SymbolSize = 20;
			this->GetStartedButtonNewScript->TabIndex = 0;
			this->GetStartedButtonNewScript->TabStop = false;
			this->GetStartedButtonNewScript->Text = L"<font size=\"+8\">Create a New Script</font>";
			// 
			// ContextMenuProvider
			// 
			this->ContextMenuProvider->AntiAlias = true;
			this->ContextMenuProvider->DockSide = DevComponents::DotNetBar::eDockSide::Document;
			this->ContextMenuProvider->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->ContextMenuProvider->IsMaximized = false;
			this->ContextMenuProvider->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {
				this->ContextMenuTextEditor,
					this->ContextMenuTabStrip
			});
			this->ContextMenuProvider->Location = System::Drawing::Point(6, 6);
			this->ContextMenuProvider->Name = L"ContextMenuProvider";
			this->ContextMenuProvider->Size = System::Drawing::Size(113, 47);
			this->ContextMenuProvider->Stretch = true;
			this->ContextMenuProvider->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ContextMenuProvider->TabIndex = 0;
			this->ContextMenuProvider->TabStop = false;
			// 
			// ContextMenuTabStrip
			// 
			this->ContextMenuTabStrip->AutoExpandOnClick = true;
			this->ContextMenuTabStrip->Name = L"ContextMenuTabStrip";
			this->ContextMenuTabStrip->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(6) {
				this->TabStripContextMenuCloseThis,
					this->TabStripContextMenuCloseAllOthers, this->TabStripContextMenuCloseSaved, this->TabStripContextMenuCloseAll, this->TabStripContextMenuPopOut,
					this->TabStripContextMenuTabLayout
			});
			this->ContextMenuTabStrip->Text = L"Tab Strip";
			// 
			// TabStripContextMenuCloseThis
			// 
			this->TabStripContextMenuCloseThis->Name = L"TabStripContextMenuCloseThis";
			this->TabStripContextMenuCloseThis->Text = L"Close";
			// 
			// TabStripContextMenuCloseAllOthers
			// 
			this->TabStripContextMenuCloseAllOthers->Name = L"TabStripContextMenuCloseAllOthers";
			this->TabStripContextMenuCloseAllOthers->Text = L"Close Others";
			// 
			// TabStripContextMenuCloseSaved
			// 
			this->TabStripContextMenuCloseSaved->Name = L"TabStripContextMenuCloseSaved";
			this->TabStripContextMenuCloseSaved->Text = L"Close Saved";
			// 
			// TabStripContextMenuCloseAll
			// 
			this->TabStripContextMenuCloseAll->Name = L"TabStripContextMenuCloseAll";
			this->TabStripContextMenuCloseAll->Text = L"Close All";
			// 
			// TabStripContextMenuPopOut
			// 
			this->TabStripContextMenuPopOut->BeginGroup = true;
			this->TabStripContextMenuPopOut->Name = L"TabStripContextMenuPopOut";
			this->TabStripContextMenuPopOut->Text = L"Pop Out";
			// 
			// TabStripContextMenuTabLayout
			// 
			this->TabStripContextMenuTabLayout->BeginGroup = true;
			this->TabStripContextMenuTabLayout->Name = L"TabStripContextMenuTabLayout";
			this->TabStripContextMenuTabLayout->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(4) {
				this->MenuTabLayoutTop,
					this->MenuTabLayoutBottom, this->MenuTabLayoutLeft, this->MenuTabLayoutRight
			});
			this->TabStripContextMenuTabLayout->Text = L"Tab Layout";
			// 
			// MenuTabLayoutTop
			// 
			this->MenuTabLayoutTop->Name = L"MenuTabLayoutTop";
			this->MenuTabLayoutTop->Text = L"Top";
			// 
			// MenuTabLayoutBottom
			// 
			this->MenuTabLayoutBottom->Name = L"MenuTabLayoutBottom";
			this->MenuTabLayoutBottom->Text = L"Bottom";
			// 
			// MenuTabLayoutLeft
			// 
			this->MenuTabLayoutLeft->Name = L"MenuTabLayoutLeft";
			this->MenuTabLayoutLeft->Text = L"Left";
			// 
			// MenuTabLayoutRight
			// 
			this->MenuTabLayoutRight->Name = L"MenuTabLayoutRight";
			this->MenuTabLayoutRight->Text = L"Right";
			// 
			// ContextMenuTextEditor
			// 
			this->ContextMenuTextEditor->AutoExpandOnClick = true;
			this->ContextMenuTextEditor->Name = L"ContextMenuTextEditor";
			this->ContextMenuTextEditor->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(4) {
				this->TextEditorContextMenuCopy,
					this->TextEditorContextMenuPaste, this->TextEditorContextMenuAddVar, this->TextEditorContextMenuJumpToScript
			});
			this->ContextMenuTextEditor->Text = L"Text Editor";
			// 
			// TextEditorContextMenuCopy
			// 
			this->TextEditorContextMenuCopy->AlternateShortCutText = L"Ctrl + C";
			this->TextEditorContextMenuCopy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TextEditorContextMenuCopy.Image")));
			this->TextEditorContextMenuCopy->Name = L"TextEditorContextMenuCopy";
			this->TextEditorContextMenuCopy->Text = L"Copy";
			// 
			// TextEditorContextMenuPaste
			// 
			this->TextEditorContextMenuPaste->AlternateShortCutText = L"Ctrl + V";
			this->TextEditorContextMenuPaste->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TextEditorContextMenuPaste.Image")));
			this->TextEditorContextMenuPaste->Name = L"TextEditorContextMenuPaste";
			this->TextEditorContextMenuPaste->Text = L"Paste";
			// 
			// TextEditorContextMenuJumpToScript
			// 
			this->TextEditorContextMenuJumpToScript->AlternateShortCutText = L"Ctrl + |";
			this->TextEditorContextMenuJumpToScript->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TextEditorContextMenuJumpToScript.Image")));
			this->TextEditorContextMenuJumpToScript->Name = L"TextEditorContextMenuJumpToScript";
			this->TextEditorContextMenuJumpToScript->Text = L"Jump to Attached Script";
			// 
			// NavigationBar
			// 
			this->NavigationBar->AutoSize = true;
			this->NavigationBar->BackColor = System::Drawing::Color::White;
			// 
			// 
			// 
			this->NavigationBar->BackgroundStyle->Class = L"CrumbBarBackgroundKey";
			this->NavigationBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->NavigationBar->ContainerControlProcessDialogKey = true;
			this->NavigationBar->Dock = System::Windows::Forms::DockStyle::Top;
			this->NavigationBar->ForeColor = System::Drawing::Color::Black;
			this->NavigationBar->Location = System::Drawing::Point(0, 0);
			this->NavigationBar->Name = L"NavigationBar";
			this->NavigationBar->PathSeparator = L";";
			this->NavigationBar->Size = System::Drawing::Size(572, 22);
			this->NavigationBar->Style = DevComponents::DotNetBar::eCrumbBarStyle::Office2007;
			this->NavigationBar->TabIndex = 0;
			this->NavigationBar->TabStop = false;
			// 
			// StatusBar
			// 
			this->StatusBar->AccessibleDescription = L"DotNetBar Bar (StatusBar)";
			this->StatusBar->AccessibleName = L"DotNetBar Bar";
			this->StatusBar->AccessibleRole = System::Windows::Forms::AccessibleRole::ToolBar;
			this->StatusBar->AntiAlias = true;
			this->StatusBar->BarType = DevComponents::DotNetBar::eBarType::StatusBar;
			this->StatusBar->CanAutoHide = false;
			this->StatusBar->CanCustomize = false;
			this->StatusBar->CanDockLeft = false;
			this->StatusBar->CanDockRight = false;
			this->StatusBar->CanDockTab = false;
			this->StatusBar->CanDockTop = false;
			this->StatusBar->CanMaximizeFloating = false;
			this->StatusBar->CanMove = false;
			this->StatusBar->CanReorderTabs = false;
			this->StatusBar->CanUndock = false;
			this->StatusBar->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->StatusBar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->StatusBar->ForeColor = System::Drawing::Color::Black;
			this->StatusBar->IsMaximized = false;
			this->StatusBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(8) {
				this->StatusBarDocumentDescription,
					this->StatusBarErrorCount, this->StatusBarWarningCount, this->StatusBarNoIssuesIndicator, this->StatusBarLineNumber, this->StatusBarColumnNumber,
					this->StatusBarPreprocessorOutputFlag, this->StatusBarScriptBytecodeLength
			});
			this->StatusBar->Location = System::Drawing::Point(0, 860);
			this->StatusBar->Name = L"StatusBar";
			this->StatusBar->PaddingBottom = 3;
			this->StatusBar->PaddingLeft = 15;
			this->StatusBar->PaddingRight = 15;
			this->StatusBar->PaddingTop = 3;
			this->StatusBar->Size = System::Drawing::Size(1030, 30);
			this->StatusBar->Stretch = true;
			this->StatusBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->StatusBar->TabIndex = 13;
			this->StatusBar->TabStop = false;
			// 
			// StatusBarDocumentDescription
			// 
			this->StatusBarDocumentDescription->Name = L"StatusBarDocumentDescription";
			this->StatusBarDocumentDescription->PaddingRight = 20;
			this->StatusBarDocumentDescription->Text = L"Script Name";
			// 
			// StatusBarErrorCount
			// 
			this->StatusBarErrorCount->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->StatusBarErrorCount->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"StatusBarErrorCount.Image")));
			this->StatusBarErrorCount->ImagePaddingHorizontal = 10;
			this->StatusBarErrorCount->Name = L"StatusBarErrorCount";
			this->StatusBarErrorCount->Text = L"0";
			// 
			// StatusBarWarningCount
			// 
			this->StatusBarWarningCount->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->StatusBarWarningCount->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"StatusBarWarningCount.Image")));
			this->StatusBarWarningCount->ImagePaddingHorizontal = 10;
			this->StatusBarWarningCount->Name = L"StatusBarWarningCount";
			this->StatusBarWarningCount->Text = L"0";
			// 
			// StatusBarNoIssuesIndicator
			// 
			this->StatusBarNoIssuesIndicator->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->StatusBarNoIssuesIndicator->HotTrackingStyle = DevComponents::DotNetBar::eHotTrackingStyle::None;
			this->StatusBarNoIssuesIndicator->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"StatusBarNoIssuesIndicator.Image")));
			this->StatusBarNoIssuesIndicator->ImagePaddingHorizontal = 10;
			this->StatusBarNoIssuesIndicator->Name = L"StatusBarNoIssuesIndicator";
			this->StatusBarNoIssuesIndicator->Text = L"No Issues";
			// 
			// StatusBarLineNumber
			// 
			this->StatusBarLineNumber->ItemAlignment = DevComponents::DotNetBar::eItemAlignment::Center;
			this->StatusBarLineNumber->Name = L"StatusBarLineNumber";
			this->StatusBarLineNumber->PaddingLeft = 20;
			this->StatusBarLineNumber->PaddingRight = 5;
			this->StatusBarLineNumber->Text = L"Line 0";
			// 
			// StatusBarColumnNumber
			// 
			this->StatusBarColumnNumber->ItemAlignment = DevComponents::DotNetBar::eItemAlignment::Center;
			this->StatusBarColumnNumber->Name = L"StatusBarColumnNumber";
			this->StatusBarColumnNumber->PaddingLeft = 5;
			this->StatusBarColumnNumber->Text = L"Column 0";
			// 
			// StatusBarPreprocessorOutputFlag
			// 
			this->StatusBarPreprocessorOutputFlag->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"StatusBarPreprocessorOutputFlag.Image")));
			this->StatusBarPreprocessorOutputFlag->ItemAlignment = DevComponents::DotNetBar::eItemAlignment::Far;
			this->StatusBarPreprocessorOutputFlag->Name = L"StatusBarPreprocessorOutputFlag";
			this->StatusBarPreprocessorOutputFlag->PaddingLeft = 15;
			this->StatusBarPreprocessorOutputFlag->PaddingRight = 15;
			this->StatusBarPreprocessorOutputFlag->Text = L"Preprocessor Output <b>ON</b>";
			this->StatusBarPreprocessorOutputFlag->Visible = false;
			// 
			// StatusBarScriptBytecodeLength
			// 
			this->StatusBarScriptBytecodeLength->Diameter = 22;
			this->StatusBarScriptBytecodeLength->ItemAlignment = DevComponents::DotNetBar::eItemAlignment::Far;
			this->StatusBarScriptBytecodeLength->Maximum = 32768;
			this->StatusBarScriptBytecodeLength->Name = L"StatusBarScriptBytecodeLength";
			this->StatusBarScriptBytecodeLength->ProgressBarType = DevComponents::DotNetBar::eCircularProgressType::Donut;
			this->StatusBarScriptBytecodeLength->ProgressColor = System::Drawing::Color::MintCream;
			this->StatusBarScriptBytecodeLength->Text = L"Uncompiled Script";
			this->StatusBarScriptBytecodeLength->TextPadding->Left = 5;
			this->StatusBarScriptBytecodeLength->TextPadding->Right = 5;
			this->StatusBarScriptBytecodeLength->Visible = false;
			// 
			// SuppressibleWarningsList
			// 
			this->SuppressibleWarningsList->BackColor = System::Drawing::Color::White;
			this->SuppressibleWarningsList->CellEditUseWholeCell = false;
			this->SuppressibleWarningsList->CheckBoxes = true;
			this->SuppressibleWarningsList->Cursor = System::Windows::Forms::Cursors::Default;
			this->SuppressibleWarningsList->EmptyListMsg = L"Doesn\'t look like anything to me...";
			this->SuppressibleWarningsList->EmptyListMsgFont = (gcnew System::Drawing::Font(L"Segoe UI caps", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SuppressibleWarningsList->ForeColor = System::Drawing::Color::Black;
			this->SuppressibleWarningsList->FullRowSelect = true;
			this->SuppressibleWarningsList->HideSelection = false;
			this->SuppressibleWarningsList->Location = System::Drawing::Point(3, 3);
			this->SuppressibleWarningsList->MultiSelect = false;
			this->SuppressibleWarningsList->Name = L"SuppressibleWarningsList";
			this->SuppressibleWarningsList->ShowFilterMenuOnRightClick = false;
			this->SuppressibleWarningsList->ShowGroups = false;
			this->SuppressibleWarningsList->Size = System::Drawing::Size(350, 150);
			this->SuppressibleWarningsList->TabIndex = 2;
			this->SuppressibleWarningsList->TabStop = false;
			this->SuppressibleWarningsList->UseCompatibleStateImageBehavior = false;
			this->SuppressibleWarningsList->UseFiltering = true;
			this->SuppressibleWarningsList->View = System::Windows::Forms::View::Details;
			this->SuppressibleWarningsList->VirtualMode = true;
			// 
			// MenuSuppressedWarningsListViewWrapper
			// 
			this->MenuSuppressedWarningsListViewWrapper->AllowItemResize = true;
			this->MenuSuppressedWarningsListViewWrapper->Control = this->SuppressibleWarningsList;
			this->MenuSuppressedWarningsListViewWrapper->MenuVisibility = DevComponents::DotNetBar::eMenuVisibility::VisibleAlways;
			this->MenuSuppressedWarningsListViewWrapper->Name = L"MenuSuppressedWarningsListViewWrapper";
			this->MenuSuppressedWarningsListViewWrapper->Text = L"Container";
			// 
			// MenuSuppressedWarningsListViewContainer
			// 
			// 
			// 
			// 
			this->MenuSuppressedWarningsListViewContainer->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->MenuSuppressedWarningsListViewContainer->Name = L"MenuSuppressedWarningsListViewContainer";
			this->MenuSuppressedWarningsListViewContainer->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) { this->MenuSuppressedWarningsListViewWrapper });
			// 
			// 
			// 
			this->MenuSuppressedWarningsListViewContainer->TitleMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->MenuSuppressedWarningsListViewContainer->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// ScriptEditorWorkspace
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1030, 890);
			this->ControlBox = false;
			this->Controls->Add(this->DockSiteCenter);
			this->Controls->Add(this->DockSiteRightEx);
			this->Controls->Add(this->DockSiteLeftEx);
			this->Controls->Add(this->DockSiteTop);
			this->Controls->Add(this->DockSiteBottom);
			this->Controls->Add(this->DockSiteLeft);
			this->Controls->Add(this->DockSiteRight);
			this->Controls->Add(this->DockSiteTopEx);
			this->Controls->Add(this->DockSiteBottomEx);
			this->Controls->Add(this->ContainerMainToolbar);
			this->Controls->Add(this->StatusBar);
			this->Controls->Add(this->MainTabStrip);
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->Name = L"ScriptEditorWorkspace";
			this->RenderFormIcon = false;
			this->RenderFormText = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Load += gcnew System::EventHandler(this, &ScriptEditorWorkspace::ScriptEditorWorkspace_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MainTabStrip))->EndInit();
			this->MainTabStrip->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ContainerMainToolbar))->EndInit();
			this->DockSiteBottom->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarMessages))->EndInit();
			this->DockableBarMessages->ResumeLayout(false);
			this->PanelDockContainerMessageList->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MessagesList))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MessagesToolbar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarBookmarks))->EndInit();
			this->DockableBarBookmarks->ResumeLayout(false);
			this->PanelDockContainerBookmarks->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BookmarksList))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BookmarksToolbar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarFindReplaceResults))->EndInit();
			this->DockableBarFindReplaceResults->ResumeLayout(false);
			this->PanelDockContainerFindResults->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FindResultsList))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FindResultsToolbar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarFindInTabsResults))->EndInit();
			this->DockableBarFindInTabsResults->ResumeLayout(false);
			this->PanelDockContainerGlobalFindResults->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GlobalFindResultsList))->EndInit();
			this->DockSiteLeftEx->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarOutlineView))->EndInit();
			this->DockableBarOutlineView->ResumeLayout(false);
			this->PanelDockContainerOutline->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OutlineTreeView))->EndInit();
			this->DockSiteRightEx->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DockableBarFindReplace))->EndInit();
			this->DockableBarFindReplace->ResumeLayout(false);
			this->PanelDockContainerFindReplace->ResumeLayout(false);
			this->FindWindowLayoutControl->ResumeLayout(false);
			this->DockSiteCenter->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CenterDockBar))->EndInit();
			this->CenterDockBar->ResumeLayout(false);
			this->CenterDockBar->PerformLayout();
			this->PanelDocumentContent->ResumeLayout(false);
			this->EmptyWorkspacePanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ContextMenuProvider))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StatusBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SuppressibleWarningsList))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		void SetObjectListViewTextOverlay(BrightIdeasSoftware::ObjectListView^ ListView, Color ForeColor, Color BackColor)
		{
			auto EmptyMsgOverlay = safe_cast<BrightIdeasSoftware::TextOverlay^>(ListView->EmptyListMsgOverlay);
			EmptyMsgOverlay->TextColor = Color::White;
			EmptyMsgOverlay->BackColor = Color::FromArgb(100, 29, 32, 33);
			EmptyMsgOverlay->BorderWidth = 0.f;
			EmptyMsgOverlay->CornerRounding = 0.1f;
		}

	private: System::Void ScriptEditorWorkspace_Load(System::Object^ sender, System::EventArgs^ e) {
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ScriptEditorWorkspace::typeid));

		auto NewTabButton = gcnew DevComponents::DotNetBar::ButtonItem();
		NewTabButton->Name = L"NewTabButton";
		NewTabButton->Text = L"New Tab...";
		NewTabButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarNewScript.Image")));
		NewTabButton->Tooltip = L"New Script";
		NewTabButton->AutoExpandOnClick = true;
		NewTabButton->ImagePaddingHorizontal = 16;
		NewTabButton->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
		//NewTabButton->HotTrackingStyle = DevComponents::DotNetBar::eHotTrackingStyle::None;

		auto NewTabNewScriptButton = gcnew DevComponents::DotNetBar::ButtonItem();
		NewTabNewScriptButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarNewScript.Image")));
		NewTabNewScriptButton->Text = L"New Script";

		auto NewTabOpenScriptButton = gcnew DevComponents::DotNetBar::ButtonItem();
		NewTabOpenScriptButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarOpenScript.Image")));
		NewTabOpenScriptButton->Text = L"Existing Script";

		NewTabButton->SubItems->Add(NewTabNewScriptButton);
		NewTabButton->SubItems->Add(NewTabOpenScriptButton);

		//MainTabStrip->Tabs->Clear();
		MainTabStrip->Tabs->Insert(0, NewTabButton);

		auto MinimizeButton = gcnew DevComponents::DotNetBar::ButtonItem();
		MinimizeButton->Text = "-";
		auto MaximizeButton = gcnew DevComponents::DotNetBar::ButtonItem();
		MaximizeButton->Text = "[]";
		auto CloseButton = gcnew DevComponents::DotNetBar::ButtonItem();
		CloseButton->Text = "X";

		auto DragSpacer = gcnew DevComponents::DotNetBar::LabelItem();
		DragSpacer->Text = gcnew String(' ', 15);

		MainTabStrip->ControlBox->SubItems->Add(DragSpacer);
		MainTabStrip->ControlBox->SubItems->Add(MinimizeButton);
		MainTabStrip->ControlBox->SubItems->Add(MaximizeButton);
		MainTabStrip->ControlBox->SubItems->Add(CloseButton);

		auto ListViewOverlayForeColor = Color::White;
		auto ListViewOverlayBackColor = Color::FromArgb(150, 29, 32, 33);

		SetObjectListViewTextOverlay(MessagesList, ListViewOverlayForeColor, ListViewOverlayBackColor);
		SetObjectListViewTextOverlay(BookmarksList, ListViewOverlayForeColor, ListViewOverlayBackColor);
		SetObjectListViewTextOverlay(FindResultsList, ListViewOverlayForeColor, ListViewOverlayBackColor);
		SetObjectListViewTextOverlay(GlobalFindResultsList, ListViewOverlayForeColor, ListViewOverlayBackColor);

		FindWindowDropdownFind->Items->Add("first");
		FindWindowDropdownFind->Items->Add("2nd");
		FindWindowDropdownFind->Items->Add("3rd");
		FindWindowDropdownFind->Items->Add("last");
	}
	protected: virtual void WndProc(Message% m) override
	{
		switch(m.Msg)
		{
		case 0x84:
			MetroForm::WndProc(m);
			if ((int)m.Result == 0x1)
				m.Result = (IntPtr)0x2;
			return;
		}

		MetroForm::WndProc(m);
	}
};
}
