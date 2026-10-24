#include <revolution/OS.h>

void OSInitSemaphore(OSSemaphore* sem, s32 count) {
    BOOL enabled = OSDisableInterrupts();
    OSInitThreadQueue(&sem->queue);
    sem->count = count;
    OSRestoreInterrupts(enabled);
}

s32 OSWaitSemaphore(OSSemaphore* sem) {
    BOOL enabled = OSDisableInterrupts();
    s32 count;

    while ((count = sem->count) <= 0) {
        OSSleepThread(&sem->queue);
    }

    sem->count--;
    OSRestoreInterrupts(enabled);
    return count;
}

s32 OSTryWaitSemaphore(OSSemaphore* sem) {
    BOOL enabled = OSDisableInterrupts();
    s32 count = sem->count;

    if (count > 0) {
        sem->count--;
    }

    OSRestoreInterrupts(enabled);
    return count;
}

s32 OSSignalSemaphore(OSSemaphore* sem) {
    BOOL enabled = OSDisableInterrupts();
    s32 count = sem->count++;

    OSWakeupThread(&sem->queue);

    OSRestoreInterrupts(enabled);
    return count;
}

s32 OSGetSemaphoreCount(OSSemaphore* sem) {
    return sem->count;
}
