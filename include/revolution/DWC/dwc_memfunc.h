#ifndef RVL_SDK_DWC_MEMFUNC_H
#define RVL_SDK_DWC_MEMFUNC_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*DWCAlloc)(int, size_t size, int align);
typedef void (*DWCFree)(int, void*, int);

void DWCi_SetMemFunc(DWCAlloc alloc, DWCFree free);

#ifdef __cplusplus
}
#endif
#endif
