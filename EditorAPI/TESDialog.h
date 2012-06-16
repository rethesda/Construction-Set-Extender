#pragma once

#include "TESTopicInfo.h"

//	EditorAPI: TESDialog and related classes.
//	A number of class definitions are directly derived from the COEF API; Credit to JRoush for his comprehensive decoding

/*
    TESDialog is a 'container' classes for dealing with CS interface dialogs.
    The static methods and data here may actually belong in a number of other classes, but they are grouped together
    in the exectuable images, and apparently had their own file in the BS repository ("TESDialog.cpp").
    At the moment, these classes are defined for convenience, to group code related to the CS interface in one place.

    TESDialogs store a BaseExtraDataList for DialogExtra*** objects in their window 'user param' (e.g. GetWindowLong(-0x15))

    There seems to be a strong distinction between dialogs that edit forms and those that edit simpler component objects or
    provide services like import/export or text searching.  Some members are only for dialogs that edit forms, and some are
    only for dialogs that edit forms accessible in the Objects Window.
*/

class	TESForm;
class	TESQuest;
class	TESRace;
class	Script;
class	TESObjectREFR;
class	BSExtraData;

// FormEditParam - for form-editing dialogs.
// passed as initParam to CreateDialogParam() (i.e. lParam on WM_INITDIALOG message) for form-editing dialogs
// 0C
class FormEditParam
{
public:
	/*00*/ UInt8		typeID;
	/*01*/ UInt8		pad01[3];
	/*04*/ TESForm*		form;
	/*08*/ UInt32		unk08;				// never initialized or accessed

	FormEditParam(const char* EditorID);
	FormEditParam(UInt32 FormID);
	FormEditParam(TESForm* Form);
};
STATIC_ASSERT(sizeof(FormEditParam) == 0xC);

// 20
class Subwindow
{
public:
	typedef tList<HWND>		ControlListT;

	/*00*/ ControlListT     controls;		// items are actually HWNDs; declared as such due to tList's definition
    /*08*/ HWND             hDialog;		// handle of parent dialog window
    /*0C*/ HINSTANCE        hInstance;		// module instance of dialog template
	/*10*/ POINT            position;		// position of subwindow within parent dialog
	/*18*/ HWND             hContainer;		// handle of container control (e.g. Tab Control)
    /*1C*/ HWND             hSubwindow;		// handle of subwindow, if created

	// methods
	bool					Build(UInt32 TemplateID);
	void					TearDown(void);

	static Subwindow*		CreateInstance(void);
	void					DeleteInstance(void);
};
STATIC_ASSERT(sizeof(Subwindow) == 0x20);

// 2C
class ResponseEditorData
{
public:
	struct VoiceRecorderData
	{
		/*00*/ HWND			recorderDlg;
	};

	typedef tList<TESRace>			VoicedRaceListT;

	/*00*/ const char*				editorTitle;
	/*04*/ UInt32					maxResponseLength;
	/*08*/ DialogResponse*			selectedResponse;
	/*0C*/ DialogResponse*			responseLocalCopy;
	/*10*/ VoiceRecorderData*		recorderData;
	/*14*/ TESTopic*				parentTopic;
	/*18*/ TESTopicInfo*			infoLocalCopy;
	/*1C*/ TESTopicInfo*			selectedInfo;
	/*20*/ TESQuest*				selectedQuest;
	/*24*/ VoicedRaceListT			voicedRaces;
};
STATIC_ASSERT(sizeof(ResponseEditorData) == 0x2C);

// 12C
class ScriptEditorData
{
public:
	/*00*/ RECT						editorBounds;
	/*10*/ Script*					currentScript;
	/*14*/ UInt8					newScript;					// set to 1 when a new script is created, used to remove the new script when it's discarded
	/*15*/ UInt8					pad15[3];
	/*18*/ HMENU					editorMenu;
	/*1C*/ HWND						editorStatusBar;
	/*20*/ HWND						editorToolBar;
	/*24*/ HWND						scriptableFormList;			// handle to the TESScriptableForm combo box, passed as the lParam during init
	/*28*/ char						findTextQuery[0x104];
};
STATIC_ASSERT(sizeof(ScriptEditorData) == 0x12C);

// 14
class ObjectWindowTreeEntryInfo
{
public:
	typedef tList<TESForm> FormListT;

	// members
	/*00*/ UInt8         formType;           // form type for this tree entry
	/*01*/ UInt8         pad01[3];
	/*04*/ UInt32        columnCount;        // number of columns in listview
	/*08*/ UInt32        selectedIndex;      // index of currently selected item in listview (??)
	/*0C*/ FormListT     formList;

	static const UInt32		kTreeEntryCount = 0x24; // size of static tree entry arrays
};
STATIC_ASSERT(sizeof(ObjectWindowTreeEntryInfo) == 0x14);

// only required methods exposed in the API
class TESDialog
{
public:
	enum
	{
		// CS Main Dialogs
		kDialogTemplate_SplashScreen				= 235,
		kDialogTemplate_About						= 100,
		kDialogTemplate_Temp						= 102,
		kDialogTemplate_ObjectWindow				= 122,
		kDialogTemplate_CellView					= 175,
		kDialogTemplate_CellEdit					= 125,
		kDialogTemplate_Data						= 162,
		kDialogTemplate_Preferences					= 169,
		kDialogTemplate_RenderWindow				= 176,
		kDialogTemplate_PreviewWindow				= 315,		// accessible through View > Preview Window
		kDialogTemplate_ScriptEdit					= 188,
		kDialogTemplate_SearchReplace				= 198,
		kDialogTemplate_LandscapeEdit				= 203,
		kDialogTemplate_FindText					= 233,
		kDialogTemplate_RegionEditor				= 250,
		kDialogTemplate_HeightMapEditor				= 295,
		kDialogTemplate_IdleAnimations				= 302,
		kDialogTemplate_AIPackages					= 303,
		kDialogTemplate_AdjustExteriorCells			= 306,
		kDialogTemplate_OpenWindows					= 307,
		kDialogTemplate_DistantLODExport			= 317,
		kDialogTemplate_FilteredDialog				= 3235,
		kDialogTemplate_CreateLocalMaps				= 3249,
		kDialogTemplate_TextureUse					= 316,

		// TESBoundObject/FormEdit Dialogs
		kDialogTemplate_Weapon						= 135,
		kDialogTemplate_Armor						= 136,
		kDialogTemplate_Clothing					= 137,
		kDialogTemplate_MiscItem					= 138,
		kDialogTemplate_Static						= 140,
		kDialogTemplate_Reference					= 141,
		kDialogTemplate_Apparatus					= 143,
		kDialogTemplate_Book						= 144,
		kDialogTemplate_Container					= 145,
		kDialogTemplate_Activator					= 147,
		kDialogTemplate_AIForm						= 154,
		kDialogTemplate_Light						= 156,
		kDialogTemplate_Potion						= 165,
		kDialogTemplate_Enchantment					= 166,
		kDialogTemplate_LeveledCreature				= 168,
		kDialogTemplate_Sound						= 190,
		kDialogTemplate_Door						= 196,
		kDialogTemplate_LeveledItem					= 217,
		kDialogTemplate_LandTexture					= 230,
		kDialogTemplate_SoulGem						= 261,
		kDialogTemplate_Ammo						= 262,
		kDialogTemplate_Spell						= 279,
		kDialogTemplate_Flora						= 280,
		kDialogTemplate_Tree						= 287,
		kDialogTemplate_CombatStyle					= 305,
		kDialogTemplate_Water						= 314,
		kDialogTemplate_NPC							= 3202,
		kDialogTemplate_Creature					= 3206,
		kDialogTemplate_Grass						= 3237,
		kDialogTemplate_Furniture					= 3239,
		kDialogTemplate_LoadingScreen				= 3246,
		kDialogTemplate_Ingredient					= 3247,
		kDialogTemplate_LeveledSpell				= 3250,
		kDialogTemplate_AnimObject					= 3251,
		kDialogTemplate_Subspace					= 3252,
		kDialogTemplate_EffectShader				= 3253,
		kDialogTemplate_SigilStone					= 3255,

		// TESFormIDListView Dialogs
		kDialogTemplate_Faction						= 157,
		kDialogTemplate_Race						= 159,
		kDialogTemplate_Class						= 160,
		kDialogTemplate_Skill						= 161,
		kDialogTemplate_EffectSetting				= 163,
		kDialogTemplate_GameSetting					= 170,
		kDialogTemplate_Globals						= 192,
		kDialogTemplate_Birthsign					= 223,
		kDialogTemplate_Climate						= 285,
		kDialogTemplate_Worldspace					= 286,
		kDialogTemplate_Hair						= 289,
		kDialogTemplate_Quest						= 3225,
		kDialogTemplate_Eyes						= 3228,

		// Misc Dialogs
		kDialogTemplate_StringEdit					= 174,
		kDialogTemplate_SelectForm					= 189,
		kDialogTemplate_SoundPick					= 195,
		kDialogTemplate_UseReport					= 220,
		kDialogTemplate_DialogNameConflicts			= 227,
		kDialogTemplate_Package						= 243,
		kDialogTemplate_FileInUse					= 244,
		kDialogTemplate_RegionSystemTester			= 247,			// could be deprecated
		kDialogTemplate_EffectItem					= 267,
		kDialogTemplate_TESFileDetails				= 180,
		kDialogTemplate_SelectWorldspace			= 291,
		kDialogTemplate_FunctionParams				= 300,
		kDialogTemplate_ConfirmFormUserChanges		= 301,
		kDialogTemplate_ClimateChanceWarning		= 310,
		kDialogTemplate_Progress					= 3166,
		kDialogTemplate_ChooseReference				= 3224,
		kDialogTemplate_SelectTopic					= 3226,
		kDialogTemplate_ResponseEditor				= 3231,
		kDialogTemplate_SelectAudioFormat			= 107,
		kDialogTemplate_SelectAudioCaptureDevice	= 134,
		kDialogTemplate_SelectQuests				= 3234,
		kDialogTemplate_SelectQuestsEx				= 3236,
		kDialogTemplate_SoundRecording				= 3241,

		// Subwindows
		kDialogTemplate_DialogData					= 151,
		kDialogTemplate_AIPackageLocationData		= 240,
		kDialogTemplate_AIPackageTargetData			= 241,
		kDialogTemplate_AIPackageTimeData			= 242,
		kDialogTemplate_RegionEditorWeatherData		= 251,
		kDialogTemplate_RegionEditorObjectsData		= 252,
		kDialogTemplate_RegionEditorGeneral			= 253,
		kDialogTemplate_Reference3DData				= 254,
		kDialogTemplate_RegionEditorMapData			= 256,
		kDialogTemplate_ReferenceLockData			= 257,
		kDialogTemplate_ReferenceTeleportData		= 258,
		kDialogTemplate_ReferenceOwnershipData		= 259,
		kDialogTemplate_ReferenceExtraData			= 260,
		kDialogTemplate_IdleConditionData			= 263,
		kDialogTemplate_RaceBodyData				= 264,
		kDialogTemplate_RaceGeneral					= 265,
		kDialogTemplate_RaceTextData				= 266,
		kDialogTemplate_CellLightingData			= 283,
		kDialogTemplate_CellGeneral					= 284,
		kDialogTemplate_NPCStatsData				= 288,
		kDialogTemplate_RegionEditorObjectsExtraData
													= 309,
		kDialogTemplate_WeatherGeneral				= 311,
		kDialogTemplate_WeatherPecipitationData		= 312,
		kDialogTemplate_WeatherSoundData			= 313,
		kDialogTemplate_HeightMapEditorBrushData	= 3167,			// doubtful
		kDialogTemplate_HeightMapEditorToolBar		= 3169,
		kDialogTemplate_HeightMapEditorOverview		= 3180,
		kDialogTemplate_HeightMapEditorPreview		= 3193,
		kDialogTemplate_HeightMapEditorColorData	= 3201,
		kDialogTemplate_ActorFactionData			= 3203,
		kDialogTemplate_ActorInventoryData			= 3204,
		kDialogTemplate_ActorBlank					= 3205,
		kDialogTemplate_CreatureStatsData			= 3208,
		kDialogTemplate_FactionInterfactionData		= 3209,
		kDialogTemplate_PreferencesRenderWindow		= 3210,
		kDialogTemplate_PreferencesMovement			= 3211,
		kDialogTemplate_PreferencesMisc				= 3212,
		kDialogTemplate_RegionEditorLandscapeData	= 3214,
		kDialogTemplate_ActorAnimationData			= 3215,
		kDialogTemplate_NPCFaceData					= 3216,
		kDialogTemplate_ActorBlankEx				= 3219,			// spell list ?
		kDialogTemplate_RegionEditorGrassData		= 3220,
		kDialogTemplate_PreferencesShader			= 3221,
		kDialogTemplate_PreferencesLOD				= 3222,
		kDialogTemplate_ReferenceMapMarkerData		= 3223,
		kDialogTemplate_QuestGeneral				= 3227,
		kDialogTemplate_RaceFaceData				= 3229,
		kDialogTemplate_PreferencesPreviewMovement	= 3230,
		kDialogTemplate_ConditionData				= 3232,
		kDialogTemplate_RegionEditorSoundData		= 3233,
		kDialogTemplate_QuestStageData				= 3240,
		kDialogTemplate_CreatureSoundData			= 3242,
		kDialogTemplate_CellInteriorData			= 3244,
		kDialogTemplate_QuestTargetData				= 3245,
		kDialogTemplate_ReferenceSelectRefData		= 3248,
		kDialogTemplate_CreatureBloodData			= 3254,
		kDialogTemplate_NPCFaceAdvancedData			= 3256,
		kDialogTemplate_WeatherHDRData				= 3257,
		kDialogTemplate_ReferenceLeveledCreatureData
													= 3259,

		// Deprecated
		kDialogTemplate_SelectModel					= 110,
		kDialogTemplate_IngredientEx				= 139,
		kDialogTemplate_AnimGroup					= 155,
		kDialogTemplate_BodyPart					= 153,
		kDialogTemplate_FactionRankDisposition		= 158,
		kDialogTemplate_FindObject					= 205,
		kDialogTemplate_PathGrid					= 208,
		kDialogTemplate_JournalPreview				= 222,
		kDialogTemplate_ExtDoorTeleport				= 224,			// haven't seen it around
		kDialogTemplate_SoundGen					= 228,
		kDialogTemplate_IntDoorTeleport				= 229,			// same here
		kDialogTemplate_IntNorthMarker				= 231,
		kDialogTemplate_VersionControl				= 238,
		kDialogTemplate_VersionControlCheckInProbs	= 255,
		kDialogTemplate_MemoryUsage					= 304,
		kDialogTemplate_CreatureSoundEx				= 3243,
		kDialogTemplate_NPCFaceAdvancedDataEx		= 3217,

		// Unknown
		kDialogTemplate_Dialog						= 308,			// looks like a base formIDListView template of sorts
		kDialogTemplate_Progress3238				= 3238,			// could be version control/convert ESM for xBox tool related
		kDialogTemplate_Preview3258					= 3258,
		kDialogTemplate_Preview181					= 181,
	};

	// methods
	static UInt32							WritePositionToINI(HWND Handle, const char* WindowClassName);
	static bool								GetPositionFromINI(const char* WindowClassName, LPRECT OutRect);

	static LRESULT							WriteToStatusBar(int PanelIndex, const char* Message);

	static void								InitializeCSWindows();
	static void								DeinitializeCSWindows();
	static void		 						SetMainWindowTitleModified(bool State);
	static void								AutoSave();				// should probably be in TES/TESDataHandler

	static UInt32							GetDialogTemplateForFormType(UInt8 FormTypeID);
	static TESObjectREFR*					ShowSelectReferenceDialog(HWND Parent, TESObjectREFR* DefaultSelection);
	static BSExtraData*						GetDialogExtraByType(HWND Dialog, UInt16 Type);
	static TESForm*							GetDialogExtraParam(HWND Dialog);
	static TESForm*							GetDialogExtraLocalCopy(HWND Dialog);
	static bool								GetIsWindowDragDropRecipient(UInt16 FormType, HWND hWnd);

	static bool								GetIsFormEditDialogCompatible(TESForm* Form);

	static bool								SelectTESFileCommonDialog(HWND Parent, const char* SaveDir, bool SaveAsESM, char* FileNameOut, size_t OutSize);
	static HWND								ShowFormEditDialog(TESForm* Form);
	static void								ShowScriptEditorDialog(TESForm* InitScript);
	static HWND								ShowUseReportDialog(TESForm* Form);
	static void								ResetRenderWindow();
	static void								RedrawRenderWindow();
	static void								ResetFormListControls();

	static float							GetDlgItemFloat(HWND Dialog, int ID);
	static void								SetDlgItemFloat(HWND Dialog, int ID, float Value, int DecimalPlaces);
	static void								ClampDlgEditField(HWND EditControl, float Min, float Max, bool NoDecimals = false, UInt32 DecimalPlaces = 2);

	static void								ShowDialogPopupMenu(HMENU Menu, POINT* Coords, HWND Parent, LPARAM Data = NULL);
	static void								UpdatePreviewWindows(bool RefreshRenderWindow = true);
};

class TESComboBox
{
public:
	// methods
	static void								AddItem(HWND hWnd, const char* Text, void* Data, bool ResizeDroppedWidth = true);
	static void*							GetSelectedItemData(HWND hWnd);

	static void								PopulateWithForms(HWND hWnd, UInt8 FormType, bool ClearItems, bool AddDefaultItem);
};

class TESListView
{
public:
	// methods
	static void								SetSelectedItem(HWND hWnd, int Index);
	static void*							GetSelectedItemData(HWND hWnd);
	static void*							GetItemData(HWND hWnd, int Index);
};

class TESPreviewWindow
{
public:
	// methods
	static void								Initialize(TESBoundObject* Object);
};

extern const HINSTANCE*			g_TESCS_Instance;

extern const DLGPROC			g_ScriptEditor_DlgProc;
extern const DLGPROC			g_FormUseReport_DlgProc;
extern const DLGPROC			g_TESDialogFormEdit_DlgProc;
extern const DLGPROC			g_TESDialogFormIDListView_DlgProc;

extern HWND*					g_HWND_RenderWindow;
extern HWND*					g_HWND_ObjectWindow;
extern HWND*					g_HWND_CellView;
extern HWND*					g_HWND_CSParent;
extern HWND*					g_HWND_AIPackagesDlg;
extern HWND*					g_HWND_ObjectWindow_FormList;
extern HWND*					g_HWND_ObjectWindow_Tree;
extern HWND*					g_HWND_MainToolbar;
extern HWND*					g_HWND_QuestWindow;
extern HWND*					g_HWND_LandscapeEdit;
extern HWND*					g_HWND_CellView_ObjectList;
extern HWND*					g_HWND_CellView_CellList;
extern HWND*					g_HWND_PreviewWindow;

extern HMENU*					g_HMENU_MainMenu;

extern char**					g_TESActivePluginName;
extern UInt8*					g_TESCSAllowAutoSaveFlag;
extern UInt8*					g_TESCSExittingCSFlag;
extern UInt8*					g_Flag_ObjectWindow_MenuState;
extern UInt8*					g_Flag_CellView_MenuState;
extern ResponseEditorData**		g_ResponseEditorData;