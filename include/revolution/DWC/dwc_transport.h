#ifndef RVL_SDK_DWC_TRANSPORT_H
#define RVL_SDK_DWC_TRANSPORT_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void DWC_SendUnreliable(u8 aid, const void* packet, u32 size);

#ifdef __cplusplus
}
#endif
#endif
