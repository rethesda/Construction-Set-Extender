#pragma once

#include "Common\Includes.h"
#include "Common\HandshakeStructs.h"

extern "C"{

__declspec(dllexport) void OpenUseInfoBox(void);

__declspec(dllexport) void SetFormListItemData(FormData* Data);
__declspec(dllexport) void SetUseListObjectItemData(FormData* Data);
__declspec(dllexport) void SetUseListCellItemData(UseListCellItemData* Data);

}