#include <revolution/OS.h>

static void* SaveEnd;
static void* SaveStart;

void __OSReboot(u32 resetCode, u32 bootDol) {
    const char* argv;

    OSDisableInterrupts();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);

    argv = NULL;
    __OSNextPartitionType = OS_BOOT_PARTITION_TYPE;
    __OSBootDol(bootDol, resetCode | 0x80000000, &argv);
}

void OSSetSaveRegion(void* start, void* end) {
    SaveStart = start;
    SaveEnd = end;
}

void OSGetSaveRegion(void** start, void** end) {
    *start = SaveStart;
    *end = SaveEnd;
}
