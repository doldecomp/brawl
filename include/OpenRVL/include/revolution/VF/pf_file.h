#ifndef RVL_SDK_VF_PF_FILE_H
#define RVL_SDK_VF_PF_FILE_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/VF/pf_str.h>
#include <revolution/VF/pf_volume.h>

int PFFILE_p_remove(PF_VOLUME* vol, PF_STR* str);

#ifdef __cplusplus
}
#endif
#endif