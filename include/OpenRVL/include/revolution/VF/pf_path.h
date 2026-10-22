#ifndef RVL_SDK_VF_PF_PATH_H
#define RVL_SDK_VF_PF_PATH_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/VF/pf_str.h>
#include <revolution/VF/pf_volume.h>

PF_VOLUME* PFPATH_GetVolumeFromPath(PF_STR* str);

#ifdef __cplusplus
}
#endif
#endif