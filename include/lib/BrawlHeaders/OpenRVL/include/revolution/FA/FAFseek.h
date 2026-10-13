#ifndef RVL_SDK_FA_FSEEK_H
#define RVL_SDK_FA_FSEEK_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/FA/FA.h>

int FAFseek(FAHandle* handle, int offset, int mode);

#ifdef __cplusplus
}
#endif
#endif