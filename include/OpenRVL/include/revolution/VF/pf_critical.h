#ifndef RVL_SDK_VF_PF_CRITICAL_H
#define RVL_SDK_VF_PF_CRITICAL_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void PF_enterCritical(void* unk);
void PF_exitCritical(void* unk);

#ifdef __cplusplus
}
#endif
#endif