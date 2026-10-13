#ifndef RVL_SDK_DWC_ND_H
#define RVL_SDK_DWC_ND_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif


static void* DWCi_NdAlloc(size_t size, int align);
static void DWCi_NdFree(void*);


#ifdef __cplusplus
}
#endif
#endif