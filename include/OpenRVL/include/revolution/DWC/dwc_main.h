#pragma once

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

s32 DWC_GetState(void);
s32 DWC_InitFriendsMatch(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, s32 p8, s32 p9);
s32 DWC_LoginAsync(s32 p1, s32 p2, void (*p3)(s32, s32, void *), void *p4);
void DWC_ProcessFriendsMatch(void);
void DWC_ShutdownFriendsMatch(void);

#ifdef __cplusplus
}
#endif
