#ifndef RVL_SDK_OS_REBOOT_H
#define RVL_SDK_OS_REBOOT_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void __OSReboot(u32 resetCode, u32 bootDol);
void OSSetSaveRegion(void* start, void* end);
void OSGetSaveRegion(void** start, void** end);

#ifdef __cplusplus
}
#endif
#endif
