#pragma once

struct FormData
{
	const char*										EditorID;
	UInt32											FormID;
	UInt8											TypeID;
	UInt32											Flags;

	bool											IsValid() { return (EditorID) ? true : false; }
};

struct ScriptData : FormData
{
	const char*										Text;
	UInt16											Type;
	bool											ModifiedFlag;
	void*											ByteCode;
	UInt32											Length;
	const char*										ParentID;
};

struct ScriptVarIndexData
{
	struct ScriptVarInfo
	{
		const char*									Name;
		UInt8										Type;
		UInt32										Index;
	};

	ScriptVarInfo*									Data;
	UInt32											Count;
};

struct CommandInfoCLI
{
	const char*										longName;		
	const char*										shortName;	
	UInt32											opcode;			
	const char* 									helpText;		
	UInt16											needsParent;	
	UInt16											numParams;		
	void*											params;			

	void*											HandlerA;		
	void*											HandlerB;		
	void*											HandlerC;		

	UInt32											flags;
};

struct CommandTableData
{
#ifdef CSE_INTERFACE
	const CommandInfo*								CommandTableStart;
	const CommandInfo*								CommandTableEnd;
	UInt32											(* GetCommandReturnType)(const CommandInfo* cmd);
	const PluginInfo*								(* GetParentPlugin)(const CommandInfo* cmd);
#elif CSE_USER
	struct PluginInfo
	{
		UInt32			infoVersion;
		const char *	name;
		UInt32			version;
	};

	const CommandInfoCLI*							CommandTableStart;
	const CommandInfoCLI*							CommandTableEnd;
	UInt32											(* GetCommandReturnType)(const CommandInfoCLI* cmd);
	const PluginInfo*								(* GetParentPlugin)(const CommandInfoCLI* cmd);
#endif

	void											DumpData();
};

struct UseListCellItemData : public FormData
{
	const char*										WorldEditorID;
	const char*										RefEditorID;
	int												XCoord;
	int												YCoord;
	UInt32											UseCount;
};