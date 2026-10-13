#ifndef RVL_SDK_DWC_INIT_H
#define RVL_SDK_DWC_INIT_H

#include <revolution/dwc/dwc_memfunc.h>
#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

s32 DWC_Init(int, const char*, u32 gamecode, DWCAlloc alloc, DWCFree free);
void DWC_Shutdown(void);

#ifdef __cplusplus
}
#endif
#endif
