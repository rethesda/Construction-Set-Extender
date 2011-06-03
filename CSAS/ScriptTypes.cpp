#include "ScriptTypes.h"

// ugly, but seems to be the only easy way to isolate the code
#ifdef CSE
	#include "..\ExtenderInternals.h"
	#include "Array.h"
#else
// include headers that declare FormHeap_Free and FormHeap_Allocate
#endif

namespace CSAutomationScript
{
	UInt32			CSASDataElement::GlobalInstanceCount = 0;

	void CSASDataElement::Reset()
	{
		switch (Type)
		{
		case kParamType_String:
			FormHeap_Free(StringData);
			StringData = NULL;
			break;
		case kParamType_Array:
			#ifdef CSE
				Array::ReleaseArray(ArrayData);
			#else
				CSASArrayInterface_ReleaseArray(ArrayData);
			#endif

			ArrayData = NULL;
			break;
		}

		Type = kParamType_Invalid;
	}

	CSASDataElement::CSASDataElement(CSASDataElement* Data)
	{
		switch (Data->Type)
		{
		case kParamType_Invalid:
			break;
		case kParamType_String:
			SetString(Data->GetString());
			break;
		case kParamType_Array:
			SetArray(Data->GetArray());
			break;
		default:
			SetNumber(Data->GetNumber());
		}
	}

	void CSASDataElement::SetForm(TESForm* Data)
	{
		Reset();

		Type = kParamType_Reference;
		RefData = Data;
	}

	void CSASDataElement::SetNumber(double Data)
	{
		Reset();

		Type = kParamType_Numeric;
		NumericData = Data;
	}

	void CSASDataElement::SetString(const char* Data)
	{
		Reset();

		Type = kParamType_String;

		UInt32 Size = Data ? strlen(Data) : 0;
		char* Result = (char*)FormHeap_Allocate(Size + 1);
		Result[Size] = 0;
		if (Size)
		{
			strcpy_s(Result, Size + 1, Data);
		}

		StringData = Result;		
	}

	void CSASDataElement::SetArray(CSASDataElement* Elements, UInt32 Size)
	{
		Reset();

		Type = kParamType_Array;

		#ifdef CSE
			ArrayData = Array::AllocateArray(Elements, Size);
		#else
			ArrayData = ArrayInterface_AllocateNewArray(Data);
		#endif
	}

	void CSASDataElement::SetArray(Array* Data)
	{
		Reset();

		Type = kParamType_Array;

		#ifdef CSE
			ArrayData = Array::AllocateArray(ArrayData);
		#else
			CSASArrayData = ArrayInterface_CopyNewArray(Data);
		#endif
	}
}