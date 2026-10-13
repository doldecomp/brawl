#ifndef RVL_SDK_VF_PF_FAT_H
#define RVL_SDK_VF_PF_FAT_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/VF/pf_str.h>
#include <revolution/VF/pf_volume.h>

int PFFAT_FreeChain(void*, u32, u32, u32);

#ifdef __cplusplus
}
#endif
#endif