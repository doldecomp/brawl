#ifndef RVL_SDK_CRC_H
#define RVL_SDK_CRC_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

u16 NETCalcCRC16(const char* src, u32 size);

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_CRC_H
