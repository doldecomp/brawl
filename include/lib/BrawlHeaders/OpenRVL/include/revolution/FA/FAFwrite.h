#ifndef RVL_SDK_FA_FWRITE_H
#define RVL_SDK_FA_FWRITE_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/FA/FA.h>

int FAFwrite(void* buffer, size_t size, size_t num, FAHandle* handle);

#ifdef __cplusplus
}
#endif
#endif