#ifndef RVL_SDK_FA_FOPEN_H
#define RVL_SDK_FA_FOPEN_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/FA/FA.h>

FAHandle* FAFopen(const char* filepath, const char* mode);

#ifdef __cplusplus
}
#endif
#endif