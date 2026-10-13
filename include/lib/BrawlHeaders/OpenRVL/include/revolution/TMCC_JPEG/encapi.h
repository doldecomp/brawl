#ifndef RVL_SDK_TMCC_JPEG_ENCAPI_H
#define RVL_SDK_TMCC_JPEG_ENCAPI_H

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

void TMCCJPEGEncGetQFactor(void* p1, u32 p2, u16 p3, u16 p4, s32 p5, u32 p6, u32* p7, s32* p8);
void TMCCJPEGEncEncode(void* p1, s32 p2, s32 p3, u16 p4, s32 p5, s32 p6, s32 p7, u32 p8, void* p9);

#ifdef __cplusplus
}
#endif

#endif
