#pragma once

class TESForm;
class Script;
class TESGlobal;

#ifdef CSE
struct CommandInfo;
struct PluginInfo;
#else
typedef int HWND;
#endif

namespace ComponentDLLInterface
{
	void DumpInstanceCounters(void);

	class IDisposableData
	{
	public:
		virtual ~IDisposableData() = 0
		{
			;//
		}
	};
	struct FormData : public IDisposableData
	{
		const char*										EditorID;
		UInt32											FormID;
		UInt8											TypeID;
		UInt32											Flags;
		TESForm*										ParentForm;

		virtual bool									IsValid() { return (EditorID) ? true : false; }
		void											FillFormData(TESForm* Form);

		FormData();
		FormData(TESForm* Parent);
		virtual ~FormData();

		bool											IsActive() { return ((Flags >> 1) & 1); }
	};

	struct FormListData : public IDisposableData
	{
		FormData*										FormListHead;
		UInt32											FormCount;

		FormListData();
		virtual ~FormListData();
	};

	struct ScriptData : public FormData
	{
		enum
		{
			kScriptType_Object		= 0x0,
			kScriptType_Quest		= 0x1,
			kScriptType_Magic		= 0x100
		};

		const char*										Text;
		UInt16											Type;
		bool											ModifiedFlag;
		void*											ByteCode;
		UInt32											Length;
		const char*										ParentID;
		bool											UDF;
		bool											Compiled;

		void											FillScriptData(Script* Form);

		ScriptData();
		ScriptData(Script* Parent);
		virtual ~ScriptData();
	};

	struct ScriptListData : public IDisposableData
	{
		ScriptData*										ScriptListHead;
		UInt32											ScriptCount;

		ScriptListData();
		virtual ~ScriptListData();
	};

	struct QuestData : public FormData
	{
		const char*										FullName;
		const char*										ScriptName;

		QuestData();
		virtual ~QuestData();
	};

	struct VariableData : public FormData
	{
		enum
		{
			kType_Int = 0,
			kType_Float,
			kType_String
		};

		UInt8											Type;

		void											FillVariableData(const char* VariableName);
		void											FillVariableData(TESGlobal* Global);

		VariableData();
		virtual ~VariableData();
	};

	typedef VariableData GlobalData;
	typedef VariableData GMSTData;

	struct IntelliSenseUpdateData : public IDisposableData
	{
		ScriptData*										ScriptListHead;
		UInt32											ScriptCount;

		QuestData*										QuestListHead;
		UInt32											QuestCount;

		GlobalData*										GlobalListHead;
		UInt32											GlobalCount;

		GMSTData*										GMSTListHead;
		UInt32											GMSTCount;

		FormData*										EditorIDListHead;
		UInt32											EditorIDCount;

		IntelliSenseUpdateData();
		virtual ~IntelliSenseUpdateData();
	};

	struct ScriptVarListData : public IDisposableData
	{
		struct ScriptVarInfo
		{
			const char*									Name;
			UInt8										Type;	// 2 = ref var
			UInt32										Index;
		};

		ScriptVarInfo*									ScriptVarListHead;
		UInt32											ScriptVarListCount;

		ScriptVarListData();
		virtual ~ScriptVarListData();
	};

	struct ScriptErrorListData : public IDisposableData
	{
		struct ErrorData
		{
			UInt32										Line;
			const char*									Message;
		};

		ErrorData*										ErrorListHead;
		UInt32											Count;

		ScriptErrorListData();
		virtual ~ScriptErrorListData();
	};

	struct ScriptCompileData : public IDisposableData
	{
		ScriptData										Script;			// callee updates the member after a successful compile op

		bool											CompileResult;
		ScriptErrorListData								CompileErrorData;

		ScriptCompileData();
		virtual ~ScriptCompileData();
	};

	struct ScriptVarRenameData : public IDisposableData
	{
		struct ScriptVarInfo
		{
			const char*									OldName;
			const char*									NewName;
		};

		const char*										ParentScriptID;
		ScriptVarInfo*									ScriptVarListHead;
		UInt32											ScriptVarListCount;

		ScriptVarRenameData();
		virtual ~ScriptVarRenameData();
	};

	struct ObScriptCommandInfo
	{
		struct ParamInfo
		{
			const char*		typeStr;
			UInt32			typeID;
			UInt32			isOptional;

			enum
			{
				kParamType_String = 0x00,
				kParamType_Integer = 0x01,
				kParamType_Float = 0x02,
				kParamType_InventoryObject = 0x03,	// GetItemCount				TESForm *, must pass IsInventoryObjectType check
				kParamType_ObjectRef = 0x04,	// Activate					TESObjectREFR *
				kParamType_ActorValue = 0x05,	// ModActorValue			not in switch
				kParamType_Actor = 0x06,	// ToggleAI					TESObjectREFR *, must pass IsActor
				kParamType_SpellItem = 0x07,	// AddSpell					TESForm *, must be either SpellItem or book
				kParamType_Axis = 0x08,	// Rotate					not in switch (X Y Z, passed as char)
				kParamType_Cell = 0x09,	// GetInCell				TESObjectCELL *, must pass sub_4C0780
				kParamType_AnimationGroup = 0x0A,	// PlayGroup				not in switch
				kParamType_MagicItem = 0x0B,	// Cast						MagicItem *
				kParamType_Sound = 0x0C,	// Sound					TESForm *, kFormType_Sound
				kParamType_Topic = 0x0D,	// Say						TESForm *, kFormType_Dialog
				kParamType_Quest = 0x0E,	// ShowQuestVars			TESForm *, kFormType_Quest
				kParamType_Race = 0x0F,	// GetIsRace				TESForm *, kFormType_Race
				kParamType_Class = 0x10,	// GetIsClass				TESForm *, kFormType_Class
				kParamType_Faction = 0x11,	// Faction					TESForm *, kFormType_Faction
				kParamType_Sex = 0x12,	// GetIsSex					not in switch
				kParamType_Global = 0x13,	// GetGlobalValue			TESForm *, kFormType_Global
				kParamType_Furniture = 0x14,	// IsCurrentFurnitureObj	TESForm *, kFormType_Furniture
				kParamType_TESObject = 0x15,	// PlaceAtMe				TESObject *
				kParamType_VariableName = 0x16,	// GetQuestVariable			not in switch
				kParamType_QuestStage = 0x17,	// SetStage					handled like integer
				kParamType_MapMarker = 0x18,	// ShowMap					TESObjectREFR *, base form must be dword_AF36F8
				kParamType_ActorBase = 0x19,	// SetEssential				TESActorBase *
				kParamType_Container = 0x1A,	// RemoveMe					TESObjectREFR *, must pass TESObjectREFR_GetContainer
				kParamType_WorldSpace = 0x1B,	// CenterOnWorld			TESWorldSpace *
				kParamType_CrimeType = 0x1C,	// GetCrimeKnown			not in switch
				kParamType_AIPackage = 0x1D,	// GetIsCurrentPackage		TESPackage *
				kParamType_CombatStyle = 0x1E,	// SetCombatStyle			TESCombatStyle *
				kParamType_MagicEffect = 0x1F,	// HasMagicEffect			EffectSetting *
				kParamType_Birthsign = 0x20,	// GetIsPlayerBirthsign		TESForm *, kFormType_BirthSign
				kParamType_FormType = 0x21,	// GetIsUsedItemType		FormType (not all types supported)
				kParamType_WeatherID = 0x22,	// GetIsCurrentWeather		TESForm *, kFormType_Weather
				kParamType_NPC = 0x23,	// Say						TESForm *, kFormType_NPC
				kParamType_Owner = 0x24,	// IsOwner					TESForm *, kFormType_NPC or kFormType_Faction
				kParamType_EffectShader = 0x25,	// haven't seen used		TESForm *, kFormType_EffectShader

				// custom OBSE types
				kParamType_StringVar = 0x01,
				kParamType_Array = 0x26,	// only usable with compiler override; StandardCompile() will report unrecognized param type
			};

			// OBSE-specific
			enum
			{
				kTokenType_Number = 0,
				kTokenType_Boolean,
				kTokenType_String,
				kTokenType_Form,
				kTokenType_Ref,
				kTokenType_Global,
				kTokenType_Array,
				kTokenType_ArrayElement,
				kTokenType_Slice,
				kTokenType_Command,
				kTokenType_Variable,
				kTokenType_NumericVar,
				kTokenType_RefVar,
				kTokenType_StringVar,
				kTokenType_ArrayVar,
				kTokenType_Ambiguous,
				kTokenType_Operator,
				kTokenType_ForEachContext,

				// numeric literals can optionally be encoded as one of the following
				// all are converted to _Number on evaluation
				kTokenType_Byte,
				kTokenType_Short,		// 2 bytes
				kTokenType_Int,			// 4 bytes

				kTokenType_Pair,
				kTokenType_AssignableString,

				kTokenType_Invalid,
				kTokenType_Max = kTokenType_Invalid,

				// sigil value, returned when an empty expression is parsed
				kTokenType_Empty = kTokenType_Max + 1,
			};

			enum
			{
				kOBSEParamType_Number = (1 << kTokenType_Number) | (1 << kTokenType_Ambiguous),
				kOBSEParamType_Boolean = (1 << kTokenType_Boolean) | (1 << kTokenType_Ambiguous),
				kOBSEParamType_String = (1 << kTokenType_String) | (1 << kTokenType_Ambiguous),
				kOBSEParamType_Form = (1 << kTokenType_Form) | (1 << kTokenType_Ambiguous),
				kOBSEParamType_Array = (1 << kTokenType_Array) | (1 << kTokenType_Ambiguous),
				kOBSEParamType_ArrayElement = 1 << (kTokenType_ArrayElement) | (1 << kTokenType_Ambiguous),
				kOBSEParamType_Slice = 1 << kTokenType_Slice,
				kOBSEParamType_Command = 1 << kTokenType_Command,
				kOBSEParamType_Variable = 1 << kTokenType_Variable,
				kOBSEParamType_NumericVar = 1 << kTokenType_NumericVar,
				kOBSEParamType_RefVar = 1 << kTokenType_RefVar,
				kOBSEParamType_StringVar = 1 << kTokenType_StringVar,
				kOBSEParamType_ArrayVar = 1 << kTokenType_ArrayVar,
				kOBSEParamType_ForEachContext = 1 << kTokenType_ForEachContext,

				kOBSEParamType_Collection = kOBSEParamType_Array | kOBSEParamType_String,
				kOBSEParamType_ArrayVarOrElement = kOBSEParamType_ArrayVar | kOBSEParamType_ArrayElement,
				kOBSEParamType_ArrayIndex = kOBSEParamType_String | kOBSEParamType_Number,
				kOBSEParamType_BasicType = kOBSEParamType_Array | kOBSEParamType_String | kOBSEParamType_Number | kOBSEParamType_Form,
				kOBSEParamType_NoTypeCheck = 0,

				kOBSEParamType_FormOrNumber = kOBSEParamType_Form | kOBSEParamType_Number,
				kOBSEParamType_StringOrNumber = kOBSEParamType_String | kOBSEParamType_Number,
				kOBSEParamType_Pair = 1 << kTokenType_Pair,
			};

			const char* TypeIDString()
			{
				switch (typeID)
				{
				case kOBSEParamType_Number: return "Number";
				case kOBSEParamType_Boolean: return "Boolean";
				case kOBSEParamType_String: return "String";
				case kOBSEParamType_Form: return "Form";
				case kOBSEParamType_Array: return "Array";
				case kOBSEParamType_ArrayElement: return "Array Element";
				case kOBSEParamType_Slice: return "Slice";
				case kOBSEParamType_Command: return "Command";
				case kOBSEParamType_Variable: return "Variable";
				case kOBSEParamType_NumericVar: return "Numeric Variable";
				case kOBSEParamType_RefVar: return "Reference Variable";
				case kOBSEParamType_StringVar: return "String Variable";
				case kOBSEParamType_ArrayVar: return "Array Variable";
				case kOBSEParamType_ForEachContext: return "ForEach Context";
				case kOBSEParamType_Collection: return "Collection";
				case kOBSEParamType_ArrayVarOrElement: return "Array Variable or Element";
				case kOBSEParamType_BasicType: return "Basic Type";
				case kOBSEParamType_FormOrNumber: return "Form or Number";
				case kOBSEParamType_StringOrNumber: return "String or Number";
				case kOBSEParamType_Pair: return "Pair";

				case kParamType_String: return "String";
				case kParamType_Integer: return "Integer";
				case kParamType_Float: return "Float";
				case kParamType_Array: return "Array";
				case kParamType_InventoryObject: return "Inventory Object";
				case kParamType_ObjectRef: return "Object Reference";
				case kParamType_ActorValue: return "Actor Value";
				case kParamType_Actor: return "Actor";
				case kParamType_SpellItem: return "SpellItem";
				case kParamType_Axis: return "Axis";
				case kParamType_Cell: return "Cell";
				case kParamType_AnimationGroup: return "Animation Group";
				case kParamType_MagicItem: return "Magic Item";
				case kParamType_Sound: return "Sound";
				case kParamType_Topic: return "Topic";
				case kParamType_Quest: return "Quest";
				case kParamType_Race: return "Race";
				case kParamType_Class: return "Class";
				case kParamType_Faction: return "Faction";
				case kParamType_Sex: return "Sex";
				case kParamType_Global: return "Global";
				case kParamType_Furniture: return "Furniture";
				case kParamType_TESObject: return "Object";
				case kParamType_VariableName: return "Variable Name";
				case kParamType_QuestStage: return "Quest Stage";
				case kParamType_MapMarker: return "Map Marker";
				case kParamType_ActorBase: return "Actor";
				case kParamType_Container: return "Container";
				case kParamType_WorldSpace: return "WorldSpace";
				case kParamType_CrimeType: return "Crime Type";
				case kParamType_AIPackage: return "AI Package";
				case kParamType_CombatStyle: return "Combat Style";
				case kParamType_MagicEffect: return "Magic Effect";
				case kParamType_FormType: return "Form Type";
				case kParamType_WeatherID: return "Weather Type";
				case kParamType_NPC: return "NPC";
				case kParamType_Owner: return "Owner";
				case kParamType_EffectShader: return "Effect Shader";
				case kParamType_Birthsign: return "Birthsign";
				default: return "<unknown>";
				}
			}
		};

		const char*										longName;
		const char*										shortName;
		UInt32											opcode;
		const char* 									helpText;
		UInt16											needsParent;
		UInt16											numParams;
		ParamInfo*										params;

		void*											HandlerA;
		void*											HandlerB;
		void*											HandlerC;

		UInt32											flags;
	};

	struct CommandTableData
	{
#ifdef CSE
		const CommandInfo*								CommandTableStart;
		const CommandInfo*								CommandTableEnd;
		UInt32											(* GetCommandReturnType)(const CommandInfo* cmd);
		const PluginInfo*								(* GetParentPlugin)(const CommandInfo* cmd);
		UInt32											(* GetRequiredOBSEVersion)(const CommandInfo* cmd);
#else
		struct PluginInfo
		{
			UInt32			infoVersion;
			const char *	name;
			UInt32			version;
		};

		const ObScriptCommandInfo*						CommandTableStart;
		const ObScriptCommandInfo*						CommandTableEnd;
		UInt32											(* GetCommandReturnType)(const ObScriptCommandInfo* cmd);
		const PluginInfo*								(* GetParentPlugin)(const ObScriptCommandInfo* cmd);
		UInt32											(* GetRequiredOBSEVersion)(const ObScriptCommandInfo* cmd);
#endif
	};

	typedef FormListData UseInfoListFormData;
	typedef FormListData UseInfoListCrossRefData;

	struct UseInfoListCellItemData : public FormData
	{
		const char*										WorldEditorID;
		const char*										RefEditorID;			// first ref in cell
		UInt32											RefFormID;
		bool											ParentCellInterior;
		int												XCoord;
		int												YCoord;
		UInt32											UseCount;

		UseInfoListCellItemData();
		virtual ~UseInfoListCellItemData();
	};

	struct UseInfoListCellItemListData : public IDisposableData
	{
		UseInfoListCellItemData*						UseInfoListCellItemListHead;
		UInt32											UseInfoListCellItemListCount;

		UseInfoListCellItemListData();
		virtual ~UseInfoListCellItemListData();
	};

	struct CellObjectData : public FormData
	{
		bool											Selected;

		bool											IsValid() { return (FormID) ? true : false; }

		CellObjectData();
		virtual ~CellObjectData();
	};

	typedef FormListData BatchRefOwnerFormData;

	struct BatchRefData : public IDisposableData
	{
		CellObjectData*									CellObjectListHead;
		UInt32											ObjectCount;

		enum
		{
			kListID_NPC = 0,
			kListID_Global,
			kListID_Faction
		};

		struct _3DData
		{
			float										RotX, RotY, RotZ;
			float										PosX, PosY, PosZ;
			float										Scale;

			enum
			{
				kFlag_UsePosX = 1 << 0,
				kFlag_UsePosY = 1 << 1,
				kFlag_UsePosZ = 1 << 2,

				kFlag_UseRotX = 1 << 3,
				kFlag_UseRotY = 1 << 4,
				kFlag_UseRotZ = 1 << 5,

				kFlag_UseScale = 1 << 6,
			};
			UInt32										Flags;

			bool UsePosX() { return (Flags & kFlag_UsePosX) ? true : false; }
			bool UsePosY() { return (Flags & kFlag_UsePosY) ? true : false; }
			bool UsePosZ() { return (Flags & kFlag_UsePosZ) ? true : false; }
			bool PosChanged() { return UsePosX() || UsePosY() || UsePosZ(); }

			bool UseRotX() { return (Flags & kFlag_UseRotX) ? true : false; }
			bool UseRotY() { return (Flags & kFlag_UseRotY) ? true : false; }
			bool UseRotZ() { return (Flags & kFlag_UseRotZ) ? true : false; }
			bool RotChanged() { return UseRotX() || UseRotY() || UseRotZ(); }

			bool UseScale() { return (Flags & kFlag_UseScale) ? true : false; }

			_3DData()
			{
				RotX = RotY = RotZ = 0;
				PosX = PosY = PosZ = 0;
				Scale = 0;
			}
		};
		struct _Flags
		{
			bool										Persistent;
			bool										VWD;
			bool										Disabled;

			enum
			{
				kFlag_UsePersistent = 1 << 0,
				kFlag_UseVWD = 1 << 1,
				kFlag_UseDisabled = 1 << 2
			};
			UInt32										Flags;

			bool UsePersistent() { return (Flags & kFlag_UsePersistent) ? true : false; }
			bool UseVWD() { return (Flags & kFlag_UseVWD) ? true : false; }
			bool UseDisabled() { return (Flags & kFlag_UseDisabled) ? true : false; }

			_Flags()
			{
				Persistent = VWD = Disabled = false;
			}
		};

		struct _Extra
		{
			float										Health;
			float 										TimeLeft;
			int											Count;
			int											Charge;

			enum Soul
			{
				kSoul_None = 0,
				kSoul_Petty,
				kSoul_Lesser,
				kSoul_Common,
				kSoul_Greater,
				kSoul_Grand,
			};
			UInt8										SoulLevel;

			enum
			{
				kFlag_UseHealth = 1 << 0,
				kFlag_UseTimeLeft = 1 << 1,
				kFlag_UseCount = 1 << 2,
				kFlag_UseCharge = 1 << 3,
				kFlag_UseSoulLevel= 1 << 4
			};
			UInt32										Flags;

			bool UseHealth() { return (Flags & kFlag_UseHealth) ? true : false; }
			bool UseTimeLeft() { return (Flags & kFlag_UseTimeLeft) ? true : false; }
			bool UseCount() { return (Flags & kFlag_UseCount) ? true : false; }
			bool UseCharge() { return (Flags & kFlag_UseCharge) ? true : false; }
			bool UseSoulLevel() { return (Flags & kFlag_UseSoulLevel) ? true : false; }

			_Extra()
			{
				Health = TimeLeft = 0;
				Count = Charge = 0;
				SoulLevel = 0;
				Flags = 0;
			}
		};

		struct _EnableParent
		{
			void*										Parent;				// TESObjectREFR*
			bool										OppositeState;

			enum
			{
				kFlag_UseEnableParent = 1 << 0
			};
			UInt32										Flags;

			bool UseEnableParent() { return (Flags & kFlag_UseEnableParent) ? true : false; }

			_EnableParent()
			{
				Parent = 0;
				OppositeState = false;
			}
		};

		struct _Ownership
		{
			void*										Owner;				// TESNPC* or TESFaction*;
			void*										Global;				// TESGlobal*
			int											Rank;

			enum
			{
				kFlag_UseOwnership = 1 << 0,
				kFlag_UseNPCOwner = 1 << 1
			};
			UInt32										Flags;

			bool UseOwnership() { return (Flags & kFlag_UseOwnership) ? true : false; }
			bool UseNPCOwner() { return (Flags & kFlag_UseNPCOwner) ? true : false; }

			_Ownership()
			{
				Owner = Global = 0;
				Rank = 0;
				Flags = 0;
			}
		};

		_3DData											World3DData;
		_Flags											Flags;
		_Extra											Extra;
		_EnableParent									EnableParent;
		_Ownership										Ownership;

		BatchRefData();
		virtual ~BatchRefData();
	};

	struct TagBrowserInstantiationData : public IDisposableData
	{
#ifdef CSE
		POINT											InsertionPoint;
#else
		Point											InsertionPoint;
#endif

		FormData*										FormListHead;
		UInt32											FormCount;

		TagBrowserInstantiationData();
		virtual ~TagBrowserInstantiationData();
	};
}