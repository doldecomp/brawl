#ifndef RVL_SDK_VF_PF_ENTRY_ITERATOR_H
#define RVL_SDK_VF_PF_ENTRY_ITERATOR_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/VF/pf_str.h>
#include <revolution/VF/pf_volume.h>
#include <revolution/VF/pf.h>

int PFENT_ITER_GetEntryOfPath(PF_ENT_ITER* iter, PF_DIR_ENT* entry, PF_VOLUME* vol, PF_STR* str, int unk);

#ifdef __cplusplus
}
#endif
#endif