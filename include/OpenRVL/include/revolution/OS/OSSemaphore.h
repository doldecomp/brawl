#ifndef RVL_SDK_OS_SEMAPHORE_H
#define RVL_SDK_OS_SEMAPHORE_H
#include <revolution/OS/OSThread.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSSemaphore {
    volatile s32 count;  // at 0x0
    OSThreadQueue queue; // at 0x4
} OSSemaphore;

void OSInitSemaphore(OSSemaphore* sem, s32 count);
s32 OSWaitSemaphore(OSSemaphore* sem);
s32 OSTryWaitSemaphore(OSSemaphore* sem);
s32 OSSignalSemaphore(OSSemaphore* sem);
s32 OSGetSemaphoreCount(OSSemaphore* sem);

#ifdef __cplusplus
}
#endif
#endif
