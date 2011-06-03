#pragma once
#include "obse\GameTypes.h"
#include "obse\Utilities.h"

#include "TESObjectMISC.h"
#include "EffectItem.h"

//	EditorAPI: TESSigilStone class.
//	Many class definitions are directly copied from the COEF API; Credit to JRoush for his comprehensive decoding

/* 
	...
*/

namespace EditorAPI
{
	// 1A0
	class TESSigilStone : public TESObjectMISC, public TESUsesForm, public EffectItemList
	{
	public:
		// members
		//     /*00*/ TESObjectMISC
		//     /*BC*/ TESUsesForm
		//     /*C4*/ EffectItemList

		// no additional members
	};
}