#pragma once
#include <BGSEEUIManager.h>

class Subwindow;

namespace ConstructionSetExtender
{
	namespace UIManager
	{
		template <typename T>
		struct InitDialogMessageParamT
		{
			char						Buffer[0x400];
			T							ExtraData;
		};

		class CSEFilterableFormListManager
		{
			class FilterableWindowData
			{
				static LRESULT CALLBACK			FormListSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

				typedef std::map<HWND, UInt32>	WindowTimerMapT;
				static WindowTimerMapT			FilterTimerTable;

				typedef std::map<HWND, FilterableWindowData*>	FormListFilterDataMapT;
				static FormListFilterDataMapT	FormListDataTable;

				HWND					ParentWindow;
				HWND					FilterEditBox;
				HWND					FormListView;
				WNDPROC					FormListWndProc;
				HWND					FilterLabel;

				std::string				FilterString;
				int						TimerPeriod;
				int						TimeCounter;
				UInt8					Flags;
				bool					Enabled;

				enum
				{
					kFlags_RegEx				= 1 << 0,
					kFlags_SearchEditorID		= 1 << 1,
					kFlags_SearchName			= 1 << 2,
					kFlags_SearchDescription	= 1 << 3,
					kFlags_SearchFormID			= 1 << 4,
				};

				bool					HasRegEx(void) const { return Flags & kFlags_RegEx; }
				bool					HasEditorID(void) const { return Flags & kFlags_SearchEditorID; }
				bool					HasName(void) const { return Flags & kFlags_SearchName; }
				bool					HasDescription(void) const { return Flags & kFlags_SearchDescription; }
				bool					HasFormID(void) const { return Flags & kFlags_SearchFormID; }

				bool					FilterForm(TESForm* Form);		// returns true if the form matches the active filter
				void					HandlePopupMenu(HWND Parent, int X, int Y);

				void					CreateTimer(void) const;
				void					DestroyTimer(void) const;

				void					HookFormList(void);
				void					UnhookFormList(void);
			public:
				FilterableWindowData(HWND Parent, HWND EditBox, HWND FormList, HWND Label, int TimerPeriod);
				~FilterableWindowData();

				bool					HandleMessages(UINT uMsg, WPARAM wParam, LPARAM lParam);		// returns true on timeout
				void					SetEnabledState(bool State);

				bool					operator==(HWND FilterEditBox);
			};

			typedef std::vector<FilterableWindowData*>	FilterDataListT;

			FilterDataListT				ActiveFilters;

			FilterableWindowData*		Lookup(HWND FilterEdit);
		public:
			CSEFilterableFormListManager();
			~CSEFilterableFormListManager();

			bool						Register(HWND FilterEdit, HWND FilterLabel, HWND FormList, HWND ParentWindow, int TimePeriod = 500);
			void						Unregister(HWND FilterEdit);

			bool						HandleMessages(HWND FilterEdit, UINT uMsg, WPARAM wParam, LPARAM lParam);		// returns true to request a refresh of the form list
			void						SetEnabledState(HWND FilterEdit, bool State);

			static CSEFilterableFormListManager				Instance;
		};

		class CSEFormEnumerationManager
		{
			bool						VisibilityDeletedForms;
			bool						VisibilityUnmodifiedForms;
		public:
			CSEFormEnumerationManager();
			~CSEFormEnumerationManager();

			bool						GetVisibleDeletedForms(void) const;
			bool						GetVisibleUnmodifiedForms(void) const;

			bool						ToggleVisibilityDeletedForms(void);
			bool						ToggleVisibilityUnmodifiedForms(void);

			bool						GetShouldEnumerate(TESForm* Form);
			void						ResetVisibility(void);

			int							CompareActiveForms(TESForm* FormA, TESForm* FormB, int OriginalResult);

			static CSEFormEnumerationManager				Instance;
		};

		class CSECellViewExtraData : public BGSEditorExtender::BGSEEWindowExtraData
		{
		public:
			RECT	RefFilterEditBox;		// init bounds of the new controls
			RECT	RefFilterLabel;
			RECT	XLabel;
			RECT	YLabel;
			RECT	XEdit;
			RECT	YEdit;
			RECT	GoBtn;
			RECT	CellFilterEditBox;
			RECT	CellFilterLabel;

			CSECellViewExtraData();
			virtual ~CSECellViewExtraData();

			enum { kTypeID = 'XCVD' };

			enum
			{
				kExtraRefListColumn_Persistent = 5,
				kExtraRefListColumn_Disabled,
				kExtraRefListColumn_VWD,
				kExtraRefListColumn_EnableParent,
				kExtraRefListColumn_Count
			};

			static int CALLBACK CustomFormListComparator(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
		};

		class CSEDialogExtraFittingsData : public BGSEditorExtender::BGSEEWindowExtraData
		{
		public:
			POINT		LastCursorPos;
			HWND		LastCursorPosWindow;
			bool		QuickViewTriggered;

			HWND		AssetControlToolTip;
			TOOLINFO	AssetControlToolData;
			HWND		LastTrackedTool;
			bool		TrackingToolTip;

			CSEDialogExtraFittingsData();
			virtual ~CSEDialogExtraFittingsData();

			enum { kTypeID = 'XDEF' };
		};

		class CSEMainWindowMiscData : public BGSEditorExtender::BGSEEWindowExtraData
		{
		public:
			Subwindow*			ToolbarExtras;

			CSEMainWindowMiscData();
			virtual ~CSEMainWindowMiscData();

			enum { kTypeID = 'XMWM' };
		};

		class CSEMainWindowToolbarData : public BGSEditorExtender::BGSEEWindowExtraData
		{
		public:
			bool				SettingTODSlider;

			CSEMainWindowToolbarData();
			virtual ~CSEMainWindowToolbarData();

			enum { kTypeID = 'XMTD' };
		};

		class CSERenderWindowMiscData : public BGSEditorExtender::BGSEEWindowExtraData
		{
		public:
			bool				TunnelingKeyMessage;

			CSERenderWindowMiscData();
			virtual ~CSERenderWindowMiscData();

			enum { kTypeID = 'XRWM' };
		};

		class CSETESFormEditData : public BGSEditorExtender::BGSEEWindowExtraData
		{
		public:
			TESForm*						Buffer;		// stores a temp copy of the form being edited

			CSETESFormEditData();
			virtual ~CSETESFormEditData();

			enum { kTypeID = 'XFED' };

			void							FillBuffer(TESForm* Parent);
			bool							HasChanges(TESForm* Parent);
		};

		class CSEFaceGenWindowData : public BGSEditorExtender::BGSEEWindowExtraData
		{
		public:
			bool				TunnelingTabSelectMessage;
			bool				AllowPreviewUpdates;
			std::string			VoicePlaybackFilePath;

			CSEFaceGenWindowData();
			virtual ~CSEFaceGenWindowData();

			enum { kTypeID = 'XFGD' };
		};

		struct CSEFaceGenVoicePreviewData
		{
			char				VoicePath[MAX_PATH];
			char				LipPath[MAX_PATH];
			UInt32				DelayTime;
		};

		LRESULT CALLBACK		FindTextDlgSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		DataDlgSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);

		LRESULT CALLBACK		MainWindowMenuInitSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		MainWindowMenuSelectSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		MainWindowMiscSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		MainWindowToolbarSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);

		LRESULT CALLBACK		RenderWindowMenuInitSelectSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		RenderWindowMiscSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		ObjectWindowSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		CellViewWindowSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);

		LRESULT CALLBACK		ResponseDlgSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		LandscapeTextureUseDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		FilteredDialogQuestDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		AboutDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		RaceDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);

		LRESULT CALLBACK		CommonDialogExtraFittingsSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		SelectTopicsQuestsSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		TESFormIDListViewDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		LandscapeEditDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		AIPackagesDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		AIFormDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		FaceGenDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		TESFormEditDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		MagicItemFormDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		LeveledItemFormDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);
		LRESULT CALLBACK		TESObjectCELLDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);

		LRESULT CALLBACK		WindowPosDlgSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return, BGSEditorExtender::BGSEEWindowExtraDataCollection* ExtraData);

		BOOL CALLBACK			AssetSelectorDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL CALLBACK			TextEditDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL CALLBACK			TESFileSaveDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL CALLBACK			TESComboBoxDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL CALLBACK			CopyPathDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK		CreateGlobalScriptDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL CALLBACK			BindScriptDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL CALLBACK			EditResultScriptDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void					Initialize(void);
	}
}

// custom window messages
// result = Vector3*
#define WM_RENDERWINDOW_GETCAMERASTATICPIVOT	(WM_USER + 2005)
#define WM_RENDERWINDOW_UPDATEFOV				(WM_USER + 2010)
// wParam = CSEFaceGenVoicePreviewData*
#define WM_FACEGENPREVIEW_PLAYVOICE				(WM_USER + 2020)
// wParam = std::string* Out
#define WM_WINDOWPOS_GETCLASSNAME				(WM_USER + 2021)

// custom control IDs, as baked into the dialog templates
#define IDC_CSE_DATA_SETSTARTUPPLUGIN           9906
#define IDC_CSE_DATA_LOADSTARTUPPLUGIN          9907
#define IDC_CSE_DATA_SELECTLOADORDER		    9908
#define IDC_CSE_DATA_SELECTNONE					9909

#define IDC_CSE_RACE_COPYHAIR                   9915
#define IDC_CSE_RACE_COPYEYES                   9916

#define IDC_CSEFILTERABLEFORMLIST_FILTERLBL		9926
#define IDC_CSEFILTERABLEFORMLIST_FILTEREDIT	9927

#define IDC_CSE_QUEST_EDITRESULTSCRIPT			9928

#define IDC_CSE_CELLVIEW_XLBL					9929
#define IDC_CSE_CELLVIEW_YLBL					9930
#define IDC_CSE_CELLVIEW_XEDIT					9931
#define IDC_CSE_CELLVIEW_YEDIT					9932
#define IDC_CSE_CELLVIEW_GOBTN					9933

#define IDC_CSE_RESPONSEWINDOW_FACEGENPREVIEW	9934
// also used in the NPC edit dialog
#define IDC_CSE_RESPONSEWINDOW_VOICEDELAY		9935

// the IDC_CSEFILTERABLEFORMLIST_XXX IDs are used for the ref list filter
#define IDC_CSE_CELLVIEW_CELLFILTEREDIT			9936
#define IDC_CSE_CELLVIEW_CELLFILTERLBL			9937

// custom popup menu item IDs
#define IDC_CSE_POPUP_SETFORMID                 9907
#define IDC_CSE_POPUP_MARKUNMODIFIED            9908
#define IDC_CSE_POPUP_JUMPTOUSEINFOLIST         9909
#define IDC_CSE_POPUP_UNDELETE                  9910
#define IDC_CSE_POPUP_EDITBASEFORM              9913
#define IDC_CSE_POPUP_TOGGLEVISIBILITY          9917
#define IDC_CSE_POPUP_TOGGLECHILDRENVISIBILITY  9918
#define IDC_CSE_POPUP_ADDTOTAG                  9919
#define IDC_CSE_POPUP_SHOWOVERRIDES             9925
#define IDC_CSE_POPUP_PREVIEW		            9926
#define IDC_CSE_POPUP_EXPORTFACETEXTURES		9927
#define IDC_CSE_POPUP_GLOBALCOPY				9928
#define IDC_CSE_POPUP_REPLACEBASEFORM			9929
#define IDC_CSE_POPUP_GLOBALPASTE				9930
