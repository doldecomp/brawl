#ifndef RVL_SDK_VF_PF_CACHE_H
#define RVL_SDK_VF_PF_CACHE_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/VF/pf_volume.h>

int PFCACHE_FlushFATCache(PF_VOLUME* vol);
int PFCACHE_FlushDataCacheSpecific(PF_VOLUME* vol, int unk);

#ifdef __cplusplus
}
#endif
#endif