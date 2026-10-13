#ifndef RVL_SDK_VF_PF_ENTRY_H
#define RVL_SDK_VF_PF_ENTRY_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/VF/pf_str.h>
#include <revolution/VF/pf_volume.h>
#include <revolution/VF/pf.h>

int PFENT_RemoveEntry(PF_DIR_ENT* entry, PF_ENT_ITER* iter);
int PFENT_getcurrentDateTimeForEnt(u16* date, u16* time);

#ifdef __cplusplus
}
#endif
#endif