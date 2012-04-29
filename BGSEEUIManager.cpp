#include "BGSEEUIManager.h"
#include "BGSEEConsole.h"
#include "BGSEditorExtenderBase_Resource.h"

namespace BGSEditorExtender
{
	INT_PTR BGSEEWindowSubclasser::SubclassData::ProcessSubclasses( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& Return )
	{
		INT_PTR Result = FALSE;

		for (SubclassProcListT::iterator Itr = Subclasses.begin(); Itr != Subclasses.end(); Itr++)
		{
			Result = (INT_PTR)(*Itr)(hWnd, uMsg, wParam, lParam, Return);
		}

		return Result;
	}

	LRESULT CALLBACK BGSEEWindowSubclasser::MainWindowSubclassProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		BGSEEWindowSubclasser* Instance = (BGSEEWindowSubclasser*)GetWindowLong(hWnd, GWL_USERDATA);
		bool CallbackReturn = false;
		LRESULT CallbackResult = FALSE;

		for (SubclassProcListT::iterator Itr = Instance->MainWindowSubclasses.begin(); Itr != Instance->MainWindowSubclasses.end(); Itr++)
		{
			CallbackResult = (*Itr)(hWnd, uMsg, wParam, lParam, CallbackReturn);
		}

		if (CallbackReturn && uMsg != WM_DESTROY)
			return CallbackResult;
		else
			return Instance->EditorMainWindowProc(hWnd, uMsg, wParam, lParam);
	}

	INT_PTR CALLBACK BGSEEWindowSubclasser::DialogSubclassProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		bool SkipCallback = false;
		INT_PTR DlgProcResult = FALSE;
		SubclassUserData* UserData = (SubclassUserData*)GetWindowLong(hWnd, DWL_USER);
		BGSEEWindowSubclasser* Instance = UserData->Instance;

		switch (uMsg)
		{
		case WM_INITDIALOG:
			{
				SetWindowLong(hWnd, DWL_USER, (LONG)lParam);
				UserData = (SubclassUserData*)lParam;
				Instance = UserData->Instance;

				DlgProcResult = UserData->Data->Original(hWnd, uMsg, wParam, UserData->InitParam);
				UserData->Data->ProcessSubclasses(hWnd, uMsg, wParam, UserData->InitParam, SkipCallback);
				return DlgProcResult;
			}

			break;
		case WM_DESTROY:
			{
				UserData->Data->ProcessSubclasses(hWnd, uMsg, wParam, lParam, SkipCallback);
				DlgProcResult = UserData->Data->Original(hWnd, uMsg, wParam, lParam);

				delete UserData;
				return DlgProcResult;
			}

			break;
		}

		bool CallbackReturn = false;
		if (SkipCallback == false)
		{
			INT_PTR CallbackResult = UserData->Data->ProcessSubclasses(hWnd, uMsg, wParam, lParam, CallbackReturn);
			if (CallbackReturn)
				return CallbackResult;
		}

		return UserData->Data->Original(hWnd, uMsg, wParam, lParam);
	}

	bool BGSEEWindowSubclasser::GetShouldSubclass( UInt32 TemplateID,
												LPARAM InitParam,
												DLGPROC OriginalProc,
												DLGPROC& OutSubclassProc,
												SubclassUserData** OutSubclassUserData )
	{
		SME_ASSERT(OutSubclassUserData);

		DialogSubclassMapT::iterator Match = DialogSubclasses.find(TemplateID);
		if (Match != DialogSubclasses.end())
		{
			OutSubclassProc = DialogSubclassProc;
			(*OutSubclassUserData) = new SubclassUserData();
			(*OutSubclassUserData)->Instance = this;
			(*OutSubclassUserData)->Data = &Match->second;
			(*OutSubclassUserData)->Data->Original = OriginalProc;
			(*OutSubclassUserData)->InitParam = InitParam;

			return true;
		}
		else
			return false;
	}

	void BGSEEWindowSubclasser::PreSubclassMainWindow( HWND MainWindow )
	{
		EditorMainWindow = MainWindow;

		SetWindowLong(EditorMainWindow, GWL_USERDATA, (LONG)this);
		EditorMainWindowProc = (WNDPROC)SetWindowLong(EditorMainWindow, GWL_WNDPROC, (LONG)MainWindowSubclassProc);

		SME_ASSERT(EditorMainWindow && EditorMainWindowProc);
	}

	BGSEEWindowSubclasser::BGSEEWindowSubclasser() :
		EditorMainWindow(NULL),
		EditorMainWindowProc(NULL),
		MainWindowSubclasses(),
		DialogSubclasses()
	{
		;//
	}

	BGSEEWindowSubclasser::~BGSEEWindowSubclasser()
	{
		MainWindowSubclasses.clear();
		DialogSubclasses.clear();
	}

	bool BGSEEWindowSubclasser::RegisterMainWindowSubclass( SubclassProc Proc )
	{
		for (SubclassProcListT::iterator Itr = MainWindowSubclasses.begin(); Itr != MainWindowSubclasses.end(); Itr++)
		{
			if ((*Itr) == Proc)
				return false;
		}

		MainWindowSubclasses.push_back(Proc);
		return true;
	}

	bool BGSEEWindowSubclasser::UnregisterMainWindowSubclass( SubclassProc Proc )
	{
		for (SubclassProcListT::iterator Itr = MainWindowSubclasses.begin(); Itr != MainWindowSubclasses.end(); Itr++)
		{
			if ((*Itr) == Proc)
			{
				MainWindowSubclasses.erase(Itr);
				return true;
			}
		}

		return false;
	}

	bool BGSEEWindowSubclasser::RegisterDialogSubclass( UInt32 TemplateID, SubclassProc Proc )
	{
		DialogSubclassMapT::iterator Match = DialogSubclasses.find(TemplateID);
		if (Match != DialogSubclasses.end())
		{
			for (SubclassProcListT::iterator Itr = Match->second.Subclasses.begin(); Itr != Match->second.Subclasses.end(); Itr++)
			{
				if ((*Itr) == Proc)
					return false;
			}

			Match->second.Subclasses.push_back(Proc);
		}
		else
		{
			DialogSubclasses.insert(std::make_pair<UInt32, SubclassData>(TemplateID, SubclassData()));
			DialogSubclasses[TemplateID].Subclasses.push_back(Proc);
		}

		return true;
	}

	bool BGSEEWindowSubclasser::UnregisterDialogSubclass( UInt32 TemplateID, SubclassProc Proc )
	{
		DialogSubclassMapT::iterator Match = DialogSubclasses.find(TemplateID);
		if (Match != DialogSubclasses.end())
		{
			for (SubclassProcListT::iterator Itr = Match->second.Subclasses.begin(); Itr != Match->second.Subclasses.end(); Itr++)
			{
				if ((*Itr) == Proc)
				{
					MainWindowSubclasses.erase(Itr);
					return true;
				}
			}
		}

		return false;
	}

	void BGSEEResourceTemplateHotSwapper::PopulateTemplateMap( void )
	{
		for (IDirectoryIterator Itr(SourceDepot().c_str(), "*.dll"); !Itr.Done(); Itr.Next())
		{
			std::string FileName = Itr.Get()->cFileName;
			std::string FullPath = SourceDepot()+ FileName;

			HINSTANCE Module = (HINSTANCE)LoadLibraryEx(FullPath.c_str(), NULL, LOAD_LIBRARY_AS_IMAGE_RESOURCE|LOAD_LIBRARY_AS_DATAFILE);
			if (Module == NULL)
			{
				BGSEECONSOLE_ERROR("BGSEEResourceTemplateHotSwapper::PopulateTemplateMap - Failed to load resource library '%s'!", FileName.c_str());
				continue;
			}

			int Index = FileName.rfind("."), TemplateID = 0;
			SME_ASSERT(Index != -1);

			TemplateID = atoi((FileName.substr(0, Index)).c_str());
			SME_ASSERT(TemplateMap.count(TemplateID) == 0);

			TemplateMap[TemplateID] = Module;
		}
	}

	void BGSEEResourceTemplateHotSwapper::ReleaseTemplateMap( void )
	{
		for (TemplateResourceInstanceMapT::iterator Itr = TemplateMap.begin(); Itr != TemplateMap.end(); Itr++)
		{
			if (FreeLibrary(Itr->second) == NULL)
				BGSEECONSOLE_ERROR("BGSEEResourceTemplateHotSwapper::ReleaseTemplateMap - Failed to release resource library for template %d", Itr->first);
		}

		TemplateMap.clear();
	}

	HINSTANCE BGSEEResourceTemplateHotSwapper::GetAlternateResourceInstance( UInt32 TemplateID )
	{
		TemplateResourceInstanceMapT::iterator Match = TemplateMap.find(TemplateID);

		if (Match != TemplateMap.end())
			return Match->second;
		else
			return NULL;
	}

	BGSEEResourceTemplateHotSwapper::BGSEEResourceTemplateHotSwapper( std::string SourcePath ) :
		SourceDepot(SourcePath),
		TemplateMap()
	{
		;//
	}

	BGSEEResourceTemplateHotSwapper::~BGSEEResourceTemplateHotSwapper()
	{
		;//
	}

	const std::string					BGSEEDialogTemplateHotSwapper::kDefaultLoc = "Dialog Templates";

	BGSEEDialogTemplateHotSwapper::BGSEEDialogTemplateHotSwapper() :
		BGSEEResourceTemplateHotSwapper(kDefaultLoc)
	{
		PopulateTemplateMap();
	}

	BGSEEDialogTemplateHotSwapper::~BGSEEDialogTemplateHotSwapper()
	{
		ReleaseTemplateMap();
	}

	BGSEEMenuTemplateHotSwapper::BGSEEMenuTemplateHotSwapper() :
		BGSEEResourceTemplateHotSwapper("")
	{
		;//
	}

	BGSEEMenuTemplateHotSwapper::~BGSEEMenuTemplateHotSwapper()
	{
		;//
	}

	bool BGSEEMenuTemplateHotSwapper::RegisterTemplateReplacer( UInt32 TemplateID, HINSTANCE Replacer )
	{
		if (TemplateMap.count(TemplateID))
			return false;
		else
			TemplateMap[TemplateID] = Replacer;

		return true;
	}

	bool BGSEEMenuTemplateHotSwapper::UnregisterTemplateReplacer( UInt32 TemplateID )
	{
		if (TemplateMap.count(TemplateID))
		{
			TemplateMap.erase(TemplateMap.find(TemplateID));
			return true;
		}
		else
			return false;
	}

	BGSEEWindowHandleCollection::HandleCollectionT::iterator BGSEEWindowHandleCollection::Find( HWND Handle )
	{
		for (HandleCollectionT::iterator Itr = HandleList.begin(); Itr != HandleList.end(); Itr++)
		{
			if (*Itr == Handle)
				return Itr;
		}

		return HandleList.end();
	}

	bool BGSEEWindowHandleCollection::Add( HWND Handle )
	{
		if (GetExists(Handle) == false)
		{
			HandleList.push_back(Handle);
			return true;
		}
		else
			return false;
	}

	bool BGSEEWindowHandleCollection::Remove( HWND Handle )
	{
		HandleCollectionT::iterator Match = Find(Handle);
		if (Match != HandleList.end())
		{
			HandleList.erase(Match);
			return true;
		}
		else
			return false;
	}

	bool BGSEEWindowHandleCollection::GetExists( HWND Handle )
	{
		return Find(Handle) != HandleList.end();
	}

	void BGSEEWindowHandleCollection::Clear( void )
	{
		HandleList.clear();
	}

	BGSEEWindowHandleCollection::BGSEEWindowHandleCollection() :
		HandleList()
	{
		;//
	}

	BGSEEWindowHandleCollection::~BGSEEWindowHandleCollection()
	{
		Clear();
	}

	BGSEEUIManager*						BGSEEUIManager::Singleton = NULL;

	SME::UIHelpers::CSnapWindow			BGSEEUIManager::WindowEdgeSnapper;

	BGSEEUIManager::IATPatchData::IATPatchData() :
		DLL(NULL),
		Import(NULL),
		Location(NULL),
		OriginalFunction(NULL),
		CallbackFunction(NULL),
		Replaced(false)
	{
		;//
	}

	void BGSEEUIManager::IATPatchData::Replace( void )
	{
		if (Replaced)
			return;

		SME::MemoryHandler::SafeWrite32((UInt32)Location, (UInt32)CallbackFunction);
		Replaced = true;
	}

	void BGSEEUIManager::IATPatchData::Reset( void )
	{
		if (Replaced == false)
			return;

		SME::MemoryHandler::SafeWrite32((UInt32)Location, (UInt32)OriginalFunction);
		Replaced = true;
	}

	HWND CALLBACK BGSEEUIManager::CallbackCreateWindowExA( DWORD dwExStyle,
														LPCSTR lpClassName,
														LPCSTR lpWindowName,
														DWORD dwStyle,
														int X, int Y,
														int nWidth, int nHeight,
														HWND hWndParent,
														HMENU hMenu,
														HINSTANCE hInstance,
														LPVOID lpParam )
	{
		SME_ASSERT(BGSEEUI->Initialized);

		bool EditorWindow = false;
		if (!_stricmp(lpClassName, BGSEEUI->EditorWindowClassName.c_str()))
		{
			EditorWindow = true;

			if (BGSEEUI->EditorMainMenuReplacement)
				hMenu = BGSEEUI->EditorMainMenuReplacement;
		}

		HWND Result = ((_CallbackCreateWindowExA)(BGSEEUI->PatchDepot[kIATPatch_CreateWindowEx].OriginalFunction))
						(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

		if (EditorWindow)
		{
			BGSEEUI->EditorWindowHandle = new HWNDGetter(Result);
			BGSEEUI->EditorResourceInstance = new HINSTANCEGetter(hInstance);
			BGSEEUI->Subclasser->PreSubclassMainWindow(Result);
			BGSEEUI->PatchDepot[kIATPatch_CreateWindowEx].Reset();
		}

		return Result;
	}

	HMENU CALLBACK BGSEEUIManager::CallbackLoadMenuA( HINSTANCE hInstance, LPCSTR lpMenuName )
	{
		SME_ASSERT(BGSEEUI->MenuHotSwapper);

		HINSTANCE Alternate = BGSEEUI->MenuHotSwapper->GetAlternateResourceInstance((UInt32)lpMenuName);
		if (Alternate)
			hInstance = Alternate;

		return ((_CallbackLoadMenuA)(BGSEEUI->PatchDepot[kIATPatch_LoadMenu].OriginalFunction))(hInstance, lpMenuName);
	}

	HWND CALLBACK BGSEEUIManager::CallbackCreateDialogParamA( HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam )
	{
		SME_ASSERT(BGSEEUI->Subclasser && BGSEEUI->DialogHotSwapper);

		DLGPROC Replacement = NULL;
		BGSEEWindowSubclasser::SubclassUserData* UserData = NULL;
		HINSTANCE Alternate = BGSEEUI->DialogHotSwapper->GetAlternateResourceInstance((UInt32)lpTemplateName);

		if (Alternate)
			hInstance = Alternate;

		if (BGSEEUI->Subclasser->GetShouldSubclass((UInt32)lpTemplateName, dwInitParam, lpDialogFunc, Replacement, &UserData))
		{
			lpDialogFunc = Replacement;
			dwInitParam = (LPARAM)UserData;
		}

		HWND Result = ((_CallbackCreateDialogParamA)(BGSEEUI->PatchDepot[kIATPatch_CreateDialogParam].OriginalFunction))
												(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);

		BGSEEUI->StyleDialogBox(Result);

		return Result;
	}

	INT_PTR CALLBACK BGSEEUIManager::CallbackDialogBoxParamA( HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam )
	{
		SME_ASSERT(BGSEEUI->Subclasser && BGSEEUI->DialogHotSwapper);

		DLGPROC Replacement = NULL;
		BGSEEWindowSubclasser::SubclassUserData* UserData = NULL;
		HINSTANCE Alternate = BGSEEUI->DialogHotSwapper->GetAlternateResourceInstance((UInt32)lpTemplateName);

		if (Alternate)
			hInstance = Alternate;

		if (BGSEEUI->Subclasser->GetShouldSubclass((UInt32)lpTemplateName, dwInitParam, lpDialogFunc, Replacement, &UserData))
		{
			lpDialogFunc = Replacement;
			dwInitParam = (LPARAM)UserData;
		}

		return ((_CallbackDialogBoxParamA)(BGSEEUI->PatchDepot[kIATPatch_DialogBoxParam].OriginalFunction))
										(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
	}

	void BGSEEUIManager::PatchIAT( UInt8 PatchType, void* Callback )
	{
		const char* DLLName = "USER32.DLL";
		const char* ImportName = NULL;

		SME_ASSERT(PatchType < kIATPatch__MAX);

		switch (PatchType)
		{
		case kIATPatch_LoadMenu:
			ImportName = "LoadMenuA";
			break;
		case kIATPatch_CreateDialogParam:
			ImportName = "CreateDialogParamA";
			break;
		case kIATPatch_DialogBoxParam:
			ImportName = "DialogBoxParamA";
			break;
		case kIATPatch_CreateWindowEx:
			ImportName = "CreateWindowExA";
			break;
		}

		IATPatchData* Patch = &PatchDepot[PatchType];
		Patch->DLL = DLLName;
		Patch->Import = ImportName;
		Patch->Location = NULL;

		HMODULE Base = GetModuleHandle(NULL);
		IMAGE_DOS_HEADER* DOSHeader = (IMAGE_DOS_HEADER*)Base;
		IMAGE_NT_HEADERS* NTHeader = (IMAGE_NT_HEADERS*)(Base + DOSHeader->e_lfanew);

		IMAGE_IMPORT_DESCRIPTOR* IAT = (IMAGE_IMPORT_DESCRIPTOR*)(Base + NTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

		for(; IAT->Characteristics && Patch->Location == NULL; ++IAT)
		{
			if(!_stricmp(DLLName, (const char*)(Base + IAT->Name)))
			{
				IMAGE_THUNK_DATA* ThunkData = (IMAGE_THUNK_DATA*)(Base + IAT->OriginalFirstThunk);
				UInt32* DLLIAT = (UInt32*)(Base + IAT->FirstThunk);

				for(; ThunkData->u1.Ordinal; ++ThunkData, ++DLLIAT)
				{
					if(!IMAGE_SNAP_BY_ORDINAL(ThunkData->u1.Ordinal))
					{
						IMAGE_IMPORT_BY_NAME* ImportInfo = (IMAGE_IMPORT_BY_NAME*)(Base + ThunkData->u1.AddressOfData);

						if(!_stricmp((char *)ImportInfo->Name, ImportName))
						{
							Patch->Location = DLLIAT;
							break;
						}
					}
				}
			}
		}

		SME_ASSERT(Patch->Location);

		Patch->OriginalFunction = *((void**)Patch->Location);
		Patch->CallbackFunction = Callback;
		Patch->Replaced = false;

		Patch->Replace();
	}

	void BGSEEUIManager::StyleDialogBox( HWND Dialog )
	{
		LONG OldStyle = GetWindowLong(Dialog, GWL_STYLE);
		LONG NewStyle = OldStyle | WS_EX_APPWINDOW;

		SetWindowLong(Dialog, GWL_STYLE, NewStyle);
		SetWindowTheme(Dialog, L"Explorer", NULL);

		SetWindowPos(Dialog, 0, 0, 0, 0, 0, SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_DRAWFRAME);
	}

	BGSEEUIManager::BGSEEUIManager() :
		OwnerThreadID(0),
		EditorWindowClassName(""),
		EditorWindowHandle(NULL),
		EditorResourceInstance(NULL),
		EditorMainMenuReplacement(NULL),
		Subclasser(NULL),
		DialogHotSwapper(NULL),
		MenuHotSwapper(NULL),
		Initialized(false)
	{
		OwnerThreadID = GetCurrentThreadId();
	}

	BGSEEUIManager::~BGSEEUIManager()
	{
		Singleton = NULL;

		for (int i = 0; i < kHandleCollection__MAX; i++)
			HandleCollections[i].Clear();

		for (int i = 0; i < kIATPatch__MAX; i++)
			PatchDepot[i].Reset();

		SAFEDELETE(Subclasser);
		SAFEDELETE(DialogHotSwapper);
		SAFEDELETE(MenuHotSwapper);
		SAFEDELETE(EditorWindowHandle);
		SAFEDELETE(EditorResourceInstance);

		Initialized = false;
	}

	BGSEEUIManager* BGSEEUIManager::GetSingleton()
	{
		if (Singleton == NULL)
			Singleton = new BGSEEUIManager();

		return Singleton;
	}

	bool BGSEEUIManager::Initialize( const char* MainWindowClassName, HMENU MainMenuHandle )
	{
		if (Initialized)
			return false;

		Initialized = true;

		EditorWindowClassName = MainWindowClassName;
		EditorMainMenuReplacement = MainMenuHandle;
		Subclasser = new BGSEEWindowSubclasser();
		DialogHotSwapper = new BGSEEDialogTemplateHotSwapper();
		MenuHotSwapper = new BGSEEMenuTemplateHotSwapper();

		return Initialized;
	}

	BGSEEWindowHandleCollection* BGSEEUIManager::GetWindowHandleCollection( UInt8 ID )
	{
		SME_ASSERT(ID < kHandleCollection__MAX);
		return &HandleCollections[ID];
	}

	HWND BGSEEUIManager::GetMainWindow( void ) const
	{
		SME_ASSERT(EditorWindowHandle);
		return EditorWindowHandle->operator()();
	}

	int BGSEEUIManager::MsgBoxI( HWND Parent, UINT Flags, const char* Format, ... )
	{
		char Buffer[0x1000] = {0};
		va_list Args;
		va_start(Args, Format);
		vsprintf_s(Buffer, sizeof(Buffer), Format, Args);
		va_end(Args);

		return MessageBox(Parent, Buffer, BGSEEMAIN->ExtenderGetShortName(), Flags|MB_ICONINFORMATION);
	}

	int BGSEEUIManager::MsgBoxI( UINT Flags, const char* Format, ... )
	{
		char Buffer[0x1000] = {0};
		va_list Args;
		va_start(Args, Format);
		vsprintf_s(Buffer, sizeof(Buffer), Format, Args);
		va_end(Args);

		return MessageBox(GetMainWindow(), Buffer, BGSEEMAIN->ExtenderGetShortName(), Flags|MB_ICONINFORMATION);
	}

	int BGSEEUIManager::MsgBoxI( const char* Format, ... )
	{
		char Buffer[0x1000] = {0};
		va_list Args;
		va_start(Args, Format);
		vsprintf_s(Buffer, sizeof(Buffer), Format, Args);
		va_end(Args);

		return MessageBox(GetMainWindow(), Buffer, BGSEEMAIN->ExtenderGetShortName(), MB_OK|MB_ICONINFORMATION);
	}

	int BGSEEUIManager::MsgBoxW( HWND Parent, UINT Flags, const char* Format, ... )
	{
		char Buffer[0x1000] = {0};
		va_list Args;
		va_start(Args, Format);
		vsprintf_s(Buffer, sizeof(Buffer), Format, Args);
		va_end(Args);

		return MessageBox(Parent, Buffer, BGSEEMAIN->ExtenderGetShortName(), Flags|MB_ICONWARNING);
	}

	int BGSEEUIManager::MsgBoxW( UINT Flags, const char* Format, ... )
	{
		char Buffer[0x1000] = {0};
		va_list Args;
		va_start(Args, Format);
		vsprintf_s(Buffer, sizeof(Buffer), Format, Args);
		va_end(Args);

		return MessageBox(GetMainWindow(), Buffer, BGSEEMAIN->ExtenderGetShortName(), Flags|MB_ICONWARNING);
	}

	int BGSEEUIManager::MsgBoxW( const char* Format, ... )
	{
		char Buffer[0x1000] = {0};
		va_list Args;
		va_start(Args, Format);
		vsprintf_s(Buffer, sizeof(Buffer), Format, Args);
		va_end(Args);

		return MessageBox(GetMainWindow(), Buffer, BGSEEMAIN->ExtenderGetShortName(), MB_OK|MB_ICONWARNING);
	}

	int BGSEEUIManager::MsgBoxE( HWND Parent, UINT Flags, const char* Format, ... )
	{
		char Buffer[0x1000] = {0};
		va_list Args;
		va_start(Args, Format);
		vsprintf_s(Buffer, sizeof(Buffer), Format, Args);
		va_end(Args);

		return MessageBox(Parent, Buffer, BGSEEMAIN->ExtenderGetShortName(), Flags|MB_ICONERROR);
	}

	int BGSEEUIManager::MsgBoxE( UINT Flags, const char* Format, ... )
	{
		char Buffer[0x1000] = {0};
		va_list Args;
		va_start(Args, Format);
		vsprintf_s(Buffer, sizeof(Buffer), Format, Args);
		va_end(Args);

		return MessageBox(GetMainWindow(), Buffer, BGSEEMAIN->ExtenderGetShortName(), Flags|MB_ICONERROR);
	}

	int BGSEEUIManager::MsgBoxE( const char* Format, ... )
	{
		char Buffer[0x1000] = {0};
		va_list Args;
		va_start(Args, Format);
		vsprintf_s(Buffer, sizeof(Buffer), Format, Args);
		va_end(Args);

		return MessageBox(GetMainWindow(), Buffer, BGSEEMAIN->ExtenderGetShortName(), MB_OK|MB_ICONERROR);
	}

	HWND BGSEEUIManager::ModelessDialog( HINSTANCE hInstance, LPSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam /*= NULL*/ )
	{
		SME_ASSERT(Initialized);
		return ((_CallbackCreateDialogParamA)(PatchDepot[kIATPatch_CreateDialogParam].OriginalFunction))
											(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
	}

	INT_PTR BGSEEUIManager::ModalDialog( HINSTANCE hInstance, LPSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam /*= NULL*/ )
	{
		SME_ASSERT(Initialized);
		return ((_CallbackDialogBoxParamA)(PatchDepot[kIATPatch_DialogBoxParam].OriginalFunction))
											(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
	}

	BGSEEWindowSubclasser* BGSEEUIManager::GetSubclasser( void )
	{
		SME_ASSERT(Subclasser);
		return Subclasser;
	}

	BGSEEDialogTemplateHotSwapper* BGSEEUIManager::GetDialogHotSwapper( void )
	{
		SME_ASSERT(DialogHotSwapper);
		return DialogHotSwapper;
	}

	BGSEEMenuTemplateHotSwapper* BGSEEUIManager::GetMenuHotSwapper( void )
	{
		SME_ASSERT(MenuHotSwapper);
		return MenuHotSwapper;
	}

	const BGSEEINIManagerSettingFactory::SettingData		BGSEEGenericModelessDialog::kDefaultINISettings[5] =
	{
		{ "Top",		"150",		"Dialog Rect Top" },
		{ "Left",		"150",		"Dialog Rect Left" },
		{ "Right",		"150",		"Dialog Rect Right" },
		{ "Bottom",		"150",		"Dialog Rect Bottom" },
		{ "Visible",	"1",		"Dialog Visibility State" }
	};

	LRESULT CALLBACK BGSEEGenericModelessDialog::DefaultDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		bool SkipCallback = false;
		bool SkipCallbackResult = false;
		bool SkipDefaultProc = false;
		LRESULT DlgProcResult = FALSE;
		DlgUserData* UserData = (DlgUserData*)GetWindowLong(hWnd, GWL_USERDATA);
		BGSEEGenericModelessDialog* Instance = UserData->Instance;

		switch (uMsg)
		{
		case WM_INITMENUPOPUP:
			if (wParam == (WPARAM)Instance->ContextMenuHandle)
			{
				if (Instance->GetTopmost())
					CheckMenuItem(Instance->ContextMenuHandle, IDC_BGSEE_GENERICMODELESSDLG_CONTEXTMENU_ALWAYSONTOP, MF_CHECKED|MF_BYPOSITION);
				else
					CheckMenuItem(Instance->ContextMenuHandle, IDC_BGSEE_GENERICMODELESSDLG_CONTEXTMENU_ALWAYSONTOP, MF_UNCHECKED|MF_BYPOSITION);

				DlgProcResult = FALSE;
				SkipCallbackResult = true;
			}

			break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDC_BGSEE_GENERICMODELESSDLG_CONTEXTMENU_HIDE:
				Instance->ToggleVisibility();
				SkipCallback = true;
				break;
			case IDC_BGSEE_GENERICMODELESSDLG_CONTEXTMENU_ALWAYSONTOP:
				Instance->ToggleTopmost();
				SkipCallback = true;
				break;
			}

			break;
		case WM_CONTEXTMENU:
			{
				RECT Rect;
				POINT Point;

				GetClientRect(hWnd, &Rect);
				Point.x = GET_X_LPARAM(lParam);
				Point.y = GET_Y_LPARAM(lParam);

				if (PtInRect((LPRECT) &Rect, Point))
				{
					ClientToScreen(hWnd, (LPPOINT)&Point);
					TrackPopupMenu(Instance->ContextMenuHandle, TPM_LEFTALIGN|TPM_LEFTBUTTON, Point.x, Point.y, 0, hWnd, NULL);
				}
			}

			break;
		case WM_SIZING:
			{
				if (Instance->LockAspectRatio)
				{
					RECT* NewBounds = (RECT*)lParam;
					tagRECT CurrentBounds;
					GetClientRect(hWnd, &CurrentBounds);

					switch (wParam)
					{
					case WMSZ_LEFT:
					case WMSZ_RIGHT:
						{
							//Adjust height and vertical position
							int TargetHeight = (int)((CurrentBounds.right - CurrentBounds.left) / Instance->AspectRatio);
							int OriginalHeight = NewBounds->bottom - NewBounds->top;
							int DiffHeight = OriginalHeight - TargetHeight;

							NewBounds->top += (DiffHeight / 2);
							NewBounds->bottom = NewBounds->top + TargetHeight;
							break;
						}
					case WMSZ_TOP:
					case WMSZ_BOTTOM:
						{
							//Adjust width and horizontal position
							int TargetWidth = (int)((CurrentBounds.bottom - CurrentBounds.top) * Instance->AspectRatio);
							int OriginalWidth = NewBounds->right - NewBounds->left;
							int DiffWidth = OriginalWidth - TargetWidth;

							NewBounds->left += (DiffWidth / 2);
							NewBounds->right = NewBounds->left + TargetWidth;
							break;
						}
					case WMSZ_RIGHT + WMSZ_BOTTOM:
						//Lower-right corner
						NewBounds->bottom = NewBounds->top + (int)((CurrentBounds.right - CurrentBounds.left) / Instance->AspectRatio);
						break;
					case WMSZ_LEFT + WMSZ_BOTTOM:
						//Lower-left corner
						NewBounds->bottom = NewBounds->top + (int)((CurrentBounds.right - CurrentBounds.left)  / Instance->AspectRatio);
						break;
					case WMSZ_LEFT + WMSZ_TOP:
						//Upper-left corner
						NewBounds->left = NewBounds->right - (int)((CurrentBounds.bottom - CurrentBounds.top) * Instance->AspectRatio);
						break;
					case WMSZ_RIGHT + WMSZ_TOP:
						//Upper-right corner
						NewBounds->right = NewBounds->left + (int)((CurrentBounds.bottom - CurrentBounds.top) * Instance->AspectRatio);
						break;
					}
				}

				break;
			}
		case WM_MOVING:
			DlgProcResult = BGSEEUIManager::WindowEdgeSnapper.OnSnapMoving(hWnd, uMsg, wParam, lParam);
			SkipDefaultProc = true;
			break;
		case WM_ENTERSIZEMOVE:
			DlgProcResult = BGSEEUIManager::WindowEdgeSnapper.OnSnapEnterSizeMove(hWnd, uMsg, wParam, lParam);
			SkipDefaultProc = true;
			break;
		case WM_INITDIALOG:
			SetWindowLong(hWnd, GWL_USERDATA, (LONG)lParam);
			UserData = (DlgUserData*)lParam;
			Instance = UserData->Instance;
			break;
		case WM_DESTROY:
			Instance->CallbackDlgProc(hWnd, uMsg, wParam, lParam, SkipCallback);
			SkipCallback = true;
			delete UserData;
			break;
		}

		bool CallbackReturn = false;
		if (SkipCallback == false)
		{
			LRESULT CallbackResult = Instance->CallbackDlgProc(hWnd, uMsg, wParam, lParam, CallbackReturn);
			if (SkipDefaultProc == false && SkipCallbackResult == false && CallbackReturn)
				return CallbackResult;
		}

		if (SkipDefaultProc)
			return DlgProcResult;
		else
			return FALSE;
	}

	void BGSEEGenericModelessDialog::INILoadUIState( BGSEEINIManagerGetterFunctor* Getter, const char* Section )
	{
		int Top = atoi(Getter->operator()(kDefaultINISettings[kDefaultINISetting_Top].Key, Section)),
			Left = atoi(Getter->operator()(kDefaultINISettings[kDefaultINISetting_Left].Key, Section)),
			Right = atoi(Getter->operator()(kDefaultINISettings[kDefaultINISetting_Right].Key, Section)),
			Bottom = atoi(Getter->operator()(kDefaultINISettings[kDefaultINISetting_Bottom].Key, Section));

		SetWindowPos(DialogHandle, HWND_NOTOPMOST, Left, Top, Right, Bottom, NULL);
		SetVisibility(atoi(Getter->operator()(kDefaultINISettings[kDefaultINISetting_Visible].Key, Section)));
	}

	void BGSEEGenericModelessDialog::INISaveUIState( BGSEEINIManagerSetterFunctor* Setter, const char* Section )
	{
		tagRECT WindowRect;
		char Buffer[20] = {0};
		GetWindowRect(DialogHandle, &WindowRect);

		_itoa_s(WindowRect.top, Buffer, sizeof(Buffer), 10);
		Setter->operator()(kDefaultINISettings[kDefaultINISetting_Top].Key, Section, Buffer);
		_itoa_s(WindowRect.left, Buffer, sizeof(Buffer), 10);
		Setter->operator()(kDefaultINISettings[kDefaultINISetting_Left].Key, Section, Buffer);
		_itoa_s(WindowRect.right - WindowRect.left, Buffer, sizeof(Buffer), 10);
		Setter->operator()(kDefaultINISettings[kDefaultINISetting_Right].Key, Section, Buffer);
		_itoa_s(WindowRect.bottom - WindowRect.top, Buffer, sizeof(Buffer), 10);
		Setter->operator()(kDefaultINISettings[kDefaultINISetting_Bottom].Key, Section, Buffer);

		Setter->operator()(kDefaultINISettings[kDefaultINISetting_Visible].Key, Section, ((Visible)?"1":"0"));
	}

	bool BGSEEGenericModelessDialog::SetVisibility( bool State )
	{
		if (State)
			ShowWindow(DialogHandle, SW_SHOWNA);
		else
			ShowWindow(DialogHandle, SW_SHOWNA);

		Visible = State;
		return Visible;
	}

	bool BGSEEGenericModelessDialog::SetTopmost( bool State )
	{
		if (State)
			SetWindowPos(DialogHandle, HWND_TOPMOST, 0, 1, 1, 1, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
		else
			SetWindowPos(DialogHandle, HWND_NOTOPMOST, 0, 1, 1, 1, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);

		Topmost = State;
		return Topmost;
	}

	BGSEEGenericModelessDialog::BGSEEGenericModelessDialog( HWND Parent,
															HINSTANCE Resource,
															UInt32 DialogTemplate, UInt32 ContextMenuTemplate,
															MessageCallback CallbackProc,
															float AspectRatio /*= 0.0f*/ )
	{
		SME_ASSERT(Parent && Resource && DialogTemplate && ContextMenuTemplate && CallbackProc);

		DialogHandle = NULL;
		ContextMenuHandle = NULL;
		ParentHandle = Parent;
		ResourceInstance = Resource;
		DialogTemplateID = DialogTemplate;
		DialogContextMenuID = ContextMenuTemplate;
		CallbackDlgProc = CallbackProc;
		Visible = false;
		Topmost = false;
		this->AspectRatio = AspectRatio;

		if (AspectRatio == 0.0f)
			LockAspectRatio = false;
		else
			LockAspectRatio = true;
	}

	BGSEEGenericModelessDialog::BGSEEGenericModelessDialog()
	{
		DialogHandle = NULL;
		ContextMenuHandle = NULL;
		ParentHandle = NULL;
		ResourceInstance = NULL;
		DialogTemplateID = NULL;
		DialogContextMenuID = NULL;
		CallbackDlgProc = NULL;
		Visible = false;
		Topmost = false;
		AspectRatio = 0.0f;
		LockAspectRatio = false;
	}

	BGSEEGenericModelessDialog::~BGSEEGenericModelessDialog()
	{
		if (DialogHandle == NULL || ContextMenuHandle == NULL)
			return;

		BGSEEUI->GetWindowHandleCollection(BGSEEUIManager::kHandleCollection_MainWindowChildren)->Remove(DialogHandle);

		DestroyMenu(ContextMenuHandle);
		DestroyWindow(DialogHandle);
	}

	void BGSEEGenericModelessDialog::Create( LPARAM InitParam, bool Hide )
	{
		if (DialogHandle || ContextMenuHandle || CallbackDlgProc == NULL)
			return;

		DlgUserData* UserData = new DlgUserData();
		UserData->Instance = const_cast<BGSEEGenericModelessDialog*>(this);
		UserData->UserData = InitParam;
		DialogHandle = BGSEEUI->ModelessDialog(ResourceInstance, MAKEINTRESOURCE(DialogTemplateID), ParentHandle, (DLGPROC)DefaultDlgProc, (LPARAM)UserData);
		ContextMenuHandle = LoadMenu(ResourceInstance, (LPSTR)DialogContextMenuID);
		SME_ASSERT(DialogHandle && ContextMenuHandle);

		BGSEEUI->GetWindowHandleCollection(BGSEEUIManager::kHandleCollection_MainWindowChildren)->Add(DialogHandle);
		SetVisibility((!Hide));
	}

	bool BGSEEGenericModelessDialog::ToggleVisibility( void )
	{
		return SetVisibility((Visible == false));
	}

	bool BGSEEGenericModelessDialog::ToggleTopmost( void )
	{
		return SetTopmost((Topmost == false));
	}

	bool BGSEEGenericModelessDialog::GetVisible( void ) const
	{
		return Visible;
	}

	bool BGSEEGenericModelessDialog::GetTopmost( void ) const
	{
		return Topmost;
	}

	bool BGSEEGenericModelessDialog::GetInitialized( void ) const
	{
		return (DialogHandle != NULL);
	}
}