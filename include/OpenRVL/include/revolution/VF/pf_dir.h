#ifndef RVL_SDK_VF_PF_DIR_H
#define RVL_SDK_VF_PF_DIR_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/VF/pf_str.h>
#include <revolution/VF/pf_volume.h>

int PFDIR_p_mkdir(PF_VOLUME* vol, PF_STR* path, int unk1, int unk2);

#ifdef __cplusplus
}
#endif
#endif