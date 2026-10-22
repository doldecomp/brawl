#ifndef RVL_SDK_FA_OPENDIR_H
#define RVL_SDK_FA_OPENDIR_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/FA/FA.h>

FAHandle* FAOpendir(const char* path);

#ifdef __cplusplus
}
#endif
#endif