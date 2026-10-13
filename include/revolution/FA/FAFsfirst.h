#ifndef RVL_SDK_FA_FSFIRST_H
#define RVL_SDK_FA_FSFIRST_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/FA/FA.h>

int FAFsfirst(const char* pattern, int filter, FAEntryInfo* ret);

#ifdef __cplusplus
}
#endif
#endif