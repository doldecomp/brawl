#pragma once

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void DWC_ClearError(void);
s32 DWC_GetLastErrorEx(s32 *p1, s32 *p2);

#ifdef __cplusplus
}
#endif
