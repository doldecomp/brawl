#include <revolution/DVD.h>
#include <revolution/ESP.h>
#include <revolution/GX.h>
#include <revolution/IPC.h>
#include <revolution/NAND.h>
#include <revolution/OS.h>
#include <revolution/SC.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define TITLE_ID_HI(id) ((u32)(((u64)(id) >> 32) & 0xFFFFFFFF))
#define TITLE_ID_LO(id) ((u32)((u64)(id) & 0xFFFFFFFF))

#define SYSTEM_MENU_TITLE_ID 0x0000000100000002
#define DEFAULT_SYSTEM_VERSION 0x0000000100000003

#define OS_LAUNCH_PARTITION_TYPE (*(u32*)OSPhysicalToCached(0x3194))
#define OS_LAUNCH_PARTITION_OFFSET (*(u32*)OSPhysicalToCached(0x3198))
#define OS_LOCKED_FLAG (*(u8*)OSPhysicalToCached(0x3187))

typedef struct DVDGameTOC {
    u32 numGamePartitions; // at 0x0
    u32 partitionInfos;    // at 0x4
} DVDGameTOC;

typedef struct DVDPartitionInfo {
    u32 gamePartition; // at 0x0
    u32 type;          // at 0x4
} DVDPartitionInfo;

typedef struct ImgHeader {
    char date[16];  // at 0x0
    u32 entry;      // at 0x10
    u32 size;       // at 0x14
    u32 rebootSize; // at 0x18
    u32 reserved;   // at 0x1C
} ImgHeader;

typedef void (*AppInitFunc)(void (*report)(const char* msg, ...));
typedef BOOL (*AppGetNextFunc)(void** addr, u32* length, u32* offset);
typedef void* (*AppGetEntryFunc)(void);
typedef void (*AppInterfaceFunc)(AppInitFunc* init, AppGetNextFunc* getNext,
                                 AppGetEntryFunc* getEntry);

static volatile BOOL Prepared;
BOOL __OSInReboot;
static volatile u32 DVDLowIntType;
static DVDDiskID id ALIGN(32);
u32 __OSNextPartitionType = 0;

s32 __OSCurrentTGCOffset MEMORY_MAP_EXT(0x800030F4);

static BOOL PackArgs(void* addr, s32 argc, char* argv[]) {
    s32 numArgs;
    char* bootInfo2;
    char* ptr;
    char** list;
    u32 i;

    bootInfo2 = (char*)addr;
    memset(bootInfo2, 0, 0x2000);

    if (argc == 0) {
        *(u32*)&bootInfo2[8] = 0;
    } else {
        numArgs = argc;
        ptr = bootInfo2 + 0x2000;
        while (--argc >= 0) {
            ptr -= strlen(argv[argc]) + 1;
            strcpy(ptr, argv[argc]);
            argv[argc] = (char*)(ptr - bootInfo2);
        }

        list = (char**)(bootInfo2 + ((ptr - bootInfo2) & ~3));
        list -= numArgs + 1;

        for (i = 0; i < numArgs + 1; i++) {
            list[i] = argv[i];
        }

        *(s32*)(list - 1) = numArgs;
        *(u32*)&bootInfo2[8] = (u32)((char*)(list - 1) - bootInfo2);
    }

    return TRUE;
}

static BOOL Utf16ToArg(char* dstArg, u16* srcName) {
    char* srcPtr;
    char* dstPtr;
    u8 i, mask, shift;

    if (srcName != NULL) {
        srcPtr = (char*)srcName;
        dstPtr = dstArg;

        while (*srcPtr || *(srcPtr + 1)) {
            for (i = 0; i < 4; i++) {
                mask = (u8)((i & 1) ? 0xF : 0xF0);
                shift = (u8)((i & 1) ? 0 : 4);

                if (0 <= ((*srcPtr & mask) >> shift) &&
                    ((*srcPtr & mask) >> shift) < 0xA) {
                    *dstPtr = (char)(((*srcPtr & mask) >> shift) + '0');
                } else if (0xA <= ((*srcPtr & mask) >> shift) &&
                           ((*srcPtr & mask) >> shift) < 0x10) {
                    *dstPtr = (char)(((*srcPtr & mask) >> shift) + 'a' - 0xA);
                } else {
                    return FALSE;
                }

                dstPtr++;

                if (i & 1) {
                    srcPtr++;
                }
            }
        }

        *dstPtr++ = '\0';
        return TRUE;
    }

    return FALSE;
}

static BOOL PackInstallerArgs(void* addr, s32 argc, char* argv[]) {
    s32 numArgs;
    char* bootInfo2;
    char* ptr;
    char** list;
    u32 i;

    bootInfo2 = (char*)addr;
    memset(bootInfo2, 0, 0x2000);

    if (argc == 0) {
        *(u32*)&bootInfo2[8] = 0;
    } else {
        numArgs = argc;
        ptr = bootInfo2 + 0x2000;

        while (--argc >= 0) {
            if (argc < 2 || (argc % 2)) {
                char* val = argv[argc];
                ptr -= strlen(argv[argc]) + 1;
                strcpy(ptr, val);
                argv[argc] = (char*)(ptr - bootInfo2);
            } else {
                u16* val = (u16*)argv[argc];
                ptr -= wcslen((wchar_t*)val) * 4 + 1;
                Utf16ToArg(ptr, val);
                argv[argc] = (char*)(ptr - bootInfo2);
            }
        }

        list = (char**)(bootInfo2 + ((ptr - bootInfo2) & ~3));
        list -= numArgs + 1;

        for (i = 0; i < numArgs + 1; i++) {
            list[i] = argv[i];
        }

        *(s32*)(list - 1) = numArgs;
        *(u32*)&bootInfo2[8] = (u32)((char*)(list - 1) - bootInfo2);
    }

    return TRUE;
}

#ifdef __MWERKS__
static asm void Run(register void* entryPoint) {
    // clang-format off
    fralloc

    bl ICFlashInvalidate
    sync
    isync
    mtctr entryPoint
    bctr

    frfree
    blr
    // clang-format on
}
#else
static void Run(register void* entryPoint) {}
#endif

static void Callback(s32 result, DVDCommandBlock* block) {
#pragma unused(result)
#pragma unused(block)

    Prepared = TRUE;
}

void __OSGetExecParams(OSExecParams* params) {
    if (OS_DOL_EXEC_PARAMS >= (void*)0x80000000) {
        memcpy(params, OS_DOL_EXEC_PARAMS, sizeof(OSExecParams));
    } else {
        params->valid = FALSE;
    }
}

void __OSSetExecParams(const OSExecParams* params, OSExecParams* addr) {
    memcpy(addr, params, sizeof(OSExecParams));
    OS_DOL_EXEC_PARAMS = addr;
}

static void callback(u32 intType) {
    DVDLowIntType = intType;
}

void __OSLaunchNextFirmware(void) {
    u8 i;
    s32 rc = -1;
    u32 ticketCnt = 1;
    ESTicketView* t;
    ESTicketView* t2;
    ESTitleId version = DEFAULT_SYSTEM_VERSION;
    u32 simMem2Size;
    u32 mem2ProtAddr;
    DVDGameTOC* gameToc;
    DVDPartitionInfo* partInfo;
    DVDPartitionInfo* bootGameInfo;
    ESTitleMeta* tmd;
    u32 numTmdBytes = 0;
    DVDPartitionInfo* partInfoPtr;

    gameToc = OSAllocFromMEM1ArenaLo(ROUND_UP(sizeof(DVDGameTOC), 32), 32);
    partInfo = OSAllocFromMEM1ArenaLo(
        ROUND_UP(sizeof(DVDPartitionInfo) * 256, 32), 32);
    tmd = OSAllocFromMEM1ArenaLo(ROUND_UP(sizeof(ESTitleMeta), 32), 64);
    t2 = OSAllocFromMEM1ArenaLo(ROUND_UP(sizeof(ESTicketView), 32), 32);

    if (__OSNextPartitionType == OS_LAUNCH_PARTITION_TYPE &&
        OS_LAUNCH_PARTITION_OFFSET != 0) {
        rc = ESP_InitLib();
        if (rc == 0) {
            rc = ESP_DiGetTicketView(NULL, t2);
        }
        if (rc == 0) {
            rc = ESP_DiGetTmd(NULL, &numTmdBytes);
        }
        if (rc == 0) {
            rc = ESP_DiGetTmd(tmd, &numTmdBytes);
        }
        ESP_CloseLib();

        if (OSPlayTimeIsLimited()) {
            __OSPlayTimeType type = OSPLAYTIME_PERMANENT;
            u32 remain = 0xFFFFFFFF;

            __OSGetPlayTime(t2, &type, &remain);

            if (remain == 0) {
                __OSWriteExpiredFlag();
                __OSReturnToMenuForError();
            }
        }
    }

    if (rc == 0) {
        bootGameInfo = partInfo;
        bootGameInfo->type = OS_LAUNCH_PARTITION_TYPE;
        bootGameInfo->gamePartition = OS_LAUNCH_PARTITION_OFFSET;
    } else {
        DVDLowIntType = 0;
        DVDLowClosePartition(callback);
        while (!DVDLowIntType) {
            ;
        }

        if (DVDLowIntType != 1) {
            OSReport("\nOSExec(): Failed to exec %d in %d\n", DVDLowIntType,
                     895);
            __OSReturnToMenuForError();
        }

        DVDLowIntType = 0;
        DVDLowUnencryptedRead(gameToc, ROUND_UP(sizeof(DVDGameTOC), 32),
                              0x40000 >> 2, callback);
        while (!DVDLowIntType) {
            ;
        }

        if (DVDLowIntType != 1) {
            OSReport("\nOSExec(): Failed to exec %d in %d\n", DVDLowIntType,
                     905);
            __OSReturnToMenuForError();
        }

        DVDLowIntType = 0;
        DVDLowUnencryptedRead(partInfo,
                              ROUND_UP(sizeof(DVDPartitionInfo) * 256, 32),
                              gameToc->partitionInfos, callback);
        while (!DVDLowIntType) {
            ;
        }

        if (DVDLowIntType != 1) {
            OSReport("\nOSExec(): Failed to exec %d in %d\n", DVDLowIntType,
                     917);
            __OSReturnToMenuForError();
        }

        bootGameInfo = NULL;
        partInfoPtr = partInfo;
        for (i = 0; i < gameToc->numGamePartitions; i++) {
            if (partInfoPtr->type == __OSNextPartitionType) {
                bootGameInfo = partInfoPtr;
            }

            partInfoPtr++;
        }

        if (bootGameInfo == NULL) {
            gameToc++;
            partInfoPtr = partInfo + 4;
            for (i = 0; i < gameToc->numGamePartitions; i++) {
                if (partInfoPtr->type == __OSNextPartitionType) {
                    bootGameInfo = partInfoPtr;
                }

                partInfoPtr++;
            }
        }

        if (bootGameInfo == NULL) {
            OSReport(
                "\nOSExec(): The specified game doesn't exist in the disc\n");
            __OSReturnToMenuForError();
        }

        OS_LAUNCH_PARTITION_TYPE = bootGameInfo->type;
        OS_LAUNCH_PARTITION_OFFSET = bootGameInfo->gamePartition;

        DVDLowIntType = 0;
        if (OS_LOCKED_FLAG == 0x80) {
            DVDLowOpenPartitionWithTmdAndTicketView(
                bootGameInfo->gamePartition, t2, numTmdBytes, tmd, 0, NULL,
                callback);
        } else {
            DVDLowOpenPartition(bootGameInfo->gamePartition, NULL, 0, 0,
                                (ESPTmd*)tmd, callback);
        }
        while (!DVDLowIntType) {
            ;
        }

        if (DVDLowIntType != 1) {
            OSReport("\nOSExec(): Failed to exec %d in %d\n", DVDLowIntType,
                     978);
            __OSReturnToMenuForError();
        }

        DVDLowIntType = 0;
        DVDLowClosePartition(callback);
        while (!DVDLowIntType) {
            ;
        }

        if (DVDLowIntType != 1) {
            OSReport("\nOSExec(): Failed to exec %d in %d\n", DVDLowIntType,
                     988);
            __OSReturnToMenuForError();
        }
    }

    version = tmd->head.sysVersion;

    rc = ESP_InitLib();
    if (rc != 0) {
        OSReport("\nOSExec(): Failed to exec %d in %d\n", rc, 999);
        __OSHotResetForError();
    }

    rc = ESP_GetTicketViews(version, NULL, &ticketCnt);
    if (ticketCnt != 1 || rc != 0) {
        OSReport("\nOSExec(): Failed to exec %d in %d\n", rc, 1008);
        __OSHotResetForError();
    }

    t = OSAllocFromMEM1ArenaLo(ROUND_UP(sizeof(ESTicketView) * ticketCnt, 32),
                               32);
    rc = ESP_GetTicketViews(version, t, &ticketCnt);
    if (rc != 0) {
        OSReport("\nOSExec(): Failed to exec %d in %d\n", rc, 1017);
        __OSHotResetForError();
    }

    DVDLowFinalize();

    simMem2Size = OS_SIMULATED_MEM2_SIZE;
    mem2ProtAddr = (u32)OS_ACCESSIBLE_MEM2_END;
    DCStoreRange(OSPhysicalToCached(0x3100), 0x100);

    rc = ESP_LaunchTitle(version, t);
    if (rc != 0) {
        OSReport("\nOSExec(): Failed to exec %d in %d\n", rc, 1033);
        __OSHotResetForError();
    }

    ESP_CloseLib();

    DCInvalidateRange(OSPhysicalToCached(0x3100), 0x100);

    if (simMem2Size < OS_SIMULATED_MEM2_SIZE) {
        *(u32*)&OS_ACCESSIBLE_MEM2_END =
            simMem2Size -
            (OS_SIMULATED_MEM2_SIZE - (u32)OS_ACCESSIBLE_MEM2_END);
        *(u32*)&OS_USABLE_MEM2_END =
            simMem2Size - (OS_SIMULATED_MEM2_SIZE - (u32)OS_USABLE_MEM2_END);
        *(u32*)&OS_IPC_BUFFER_START =
            simMem2Size - (OS_SIMULATED_MEM2_SIZE - (u32)OS_IPC_BUFFER_START);
        *(u32*)&OS_IPC_BUFFER_END =
            simMem2Size - (OS_SIMULATED_MEM2_SIZE - (u32)OS_IPC_BUFFER_END);
        OS_SIMULATED_MEM2_SIZE = simMem2Size;
    }

    if (mem2ProtAddr < (u32)OS_ACCESSIBLE_MEM2_END) {
        __OSInitMemoryProtection();
    }

    __OSInitIPCBuffer();
    IPCReInit();
    IPCCltReInit();

    DVDLowInit();
    DVDLowIntType = 0;
    DVDLowReadDiskID(&id, callback);
    while (!DVDLowIntType) {
        ;
    }

    if (DVDLowIntType != 1) {
        OSReport("\nOSExec(): Failed to exec %d in %d\n", DVDLowIntType, 1077);
        __OSReturnToMenuForError();
    }

    DVDLowIntType = 0;
    if (OS_LOCKED_FLAG == 0x80) {
        DVDLowOpenPartitionWithTmdAndTicketView(bootGameInfo->gamePartition,
                                                t2, numTmdBytes, tmd, 0, NULL,
                                                callback);
    } else {
        DVDLowOpenPartition(bootGameInfo->gamePartition, NULL, 0, 0,
                            (ESPTmd*)tmd, callback);
    }
    while (!DVDLowIntType) {
        ;
    }

    if (DVDLowIntType != 1) {
        OSReport("\nOSExec(): Failed to exec %d in %d\n", DVDLowIntType, 1100);
        __OSReturnToMenuForError();
    }
}

void __OSLaunchMenu(void) {
    u8 i;
    s32 rc;
    u32 ticketCnt = 1;
    ESTicketView* t;
    ESTitleId version = DEFAULT_SYSTEM_VERSION;

    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);

    rc = ESP_InitLib();
    if (rc != 0) {
        return;
    }

    rc = ESP_GetTicketViews(SYSTEM_MENU_TITLE_ID, NULL, &ticketCnt);
    if (ticketCnt != 1 || rc != 0) {
        return;
    }

    t = OSAllocFromMEM1ArenaLo(ROUND_UP(sizeof(ESTicketView) * ticketCnt, 32),
                               32);
    rc = ESP_GetTicketViews(SYSTEM_MENU_TITLE_ID, t, &ticketCnt);
    if (rc != 0) {
        return;
    }

    rc = ESP_LaunchTitle(SYSTEM_MENU_TITLE_ID, t);
    if (rc != 0) {
        return;
    }

    while (TRUE) {
        ;
    }
}

static BOOL __OSCheckTmdCountryCode(ESTmdView* tmd) {
    u32 code = 0;
    code = *(u32*)tmd->head.reserved;

    if (code == 3) {
        return TRUE;
    } else {
        return code == (s8)SCGetProductGameRegion() ? TRUE : FALSE;
    }

    return FALSE;
}

static BOOL __OSCheckTmdDriveSpinFlag(ESTmdView* tmd) {
    u8 flag = 0;
    flag = tmd->head.reserved[24];

    if (flag & 1) {
        return TRUE;
    } else {
        return FALSE;
    }

    return FALSE;
}

BOOL __OSCheckCompanyCode(ESTitleId titleId, BOOL diskApp) {
    NANDStatus status;
    char home[65];
    char data[65];
    u16 currentGid;
    u16 launchedGid;
    s32 rv = 0;

    rv = NANDGetHomeDir(home);
    if (rv != NAND_RESULT_OK) {
        return FALSE;
    }

    rv = NANDGetStatus(home, &status);
    if (rv != NAND_RESULT_OK) {
        return FALSE;
    }

    currentGid = status.groupId;

    if (currentGid == 2) {
        if (OSGetAppType() == OS_APP_TYPE_DVD) {
            if ((OSGetConsoleType() & OS_CONSOLE_MASK) ==
                OS_CONSOLE_MASK_EMU) {
                const DVDDiskID* diskId = DVDGetCurrentDiskID();
                currentGid = *(u16*)diskId->company;
            }
        }
    }

    if (diskApp) {
        const DVDDiskID* diskId = DVDGetCurrentDiskID();
        launchedGid = *(u16*)diskId->company;
    } else {
        sprintf(data, "/title/%08x/%08x/data", TITLE_ID_HI(titleId),
                TITLE_ID_LO(titleId));
        rv = NANDGetStatus(data, &status);
        if (rv != NAND_RESULT_OK) {
            return FALSE;
        }

        launchedGid = status.groupId;
    }

    return currentGid == launchedGid ? TRUE : FALSE;
}

static BOOL __OSCheckTmdSysVersion(ESTmdView* tmd) {
    ESTitleId systemId = DEFAULT_SYSTEM_VERSION;
    s32 rv = 0;
    u32 numTicket = 0;
    u32 numContents = 0;

    systemId = tmd->head.sysVersion;

    rv = ESP_GetTicketViews(systemId, NULL, &numTicket);
    if (rv != 0 || numTicket != 1) {
        return FALSE;
    }

    rv = ESP_ListTitleContentsOnCard(systemId, NULL, &numContents);
    if (rv != 0 || numContents == 0) {
        return FALSE;
    }

    return TRUE;
}

s32 __OSGetValidTicketIndex(ESTicketView* ticketViewList, u32 numTickets) {
    s32 rv = 0;
    s32 i = 0;
    s32 bestIdx = 0;
    BOOL permanent = FALSE;
    u32 maxBit = 0;
    u32 maxTime = 0;

    if (ticketViewList == NULL) {
        OSReport("NULL pointer detected: line %d in %s\n", 1346, __FILE__);
        return -1017;
    }

    for (i = 0; i < numTickets; i++) {
        u32 playTime;
        u16 accessMask;
        __OSPlayTimeType type;

        rv = __OSGetPlayTime(&ticketViewList[i], &type, &playTime);
        if (rv > 0) {
            rv = 0;
            continue;
        } else if (rv != 0) {
            return rv;
        }

        switch (type) {
        case OSPLAYTIME_PERMANENT: {
            u32 j;
            u32 bits = 0;

            if (!permanent) {
                bestIdx = i;
                permanent = TRUE;
            }

            accessMask = (u16)((ticketViewList[i].sysAccessMask[1] << 8) |
                               ticketViewList[i].sysAccessMask[0]);

            for (j = 0; j < 16; j++) {
                if (accessMask & (1 << j)) {
                    bits++;
                }
            }

            if (bits > maxBit) {
                bestIdx = i;
                maxBit = bits;
            }
            break;
        }
        case OSPLAYTIME_LIMITED:
            if (!permanent) {
                if (playTime > maxTime) {
                    bestIdx = i;
                    maxTime = playTime;
                }
            }
            break;
        case OSPLAYTIME_OTHER:
            break;
        default:
            break;
        }
    }

    if (!permanent && maxTime == 0) {
        return -1;
    }

    return bestIdx;
}

void __OSRelaunchTitle(void) {
    s32 rc = 0;
    u32 ticketCnt = 1;
    ESTicketView* tik = NULL;
    ESTitleId titleId ALIGN(32);

    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);

    rc = ESP_InitLib();
    if (rc != 0) {
        __OSReturnToMenuForError();
    }

    rc = ESP_GetTitleId(&titleId);
    if (rc != 0) {
        __OSReturnToMenuForError();
    }

    tik = OSAllocFromMEM1ArenaLo(ROUND_UP(sizeof(ESTicketView), 32), 32);
    if (tik == (void*)NULL) {
        __OSReturnToMenuForError();
    }

    memset(tik, 0, ROUND_UP(sizeof(ESTicketView), 32));

    rc = ESP_DiGetTicketView(NULL, tik);
    if (rc == -1017) {
        ESTicketView* tmp = NULL;

        rc = ESP_GetTicketViews(titleId, NULL, &ticketCnt);
        if (rc != 0) {
            __OSReturnToMenuForError();
        }

        tmp = OSAllocFromMEM1ArenaLo(
            ROUND_UP(ticketCnt * sizeof(ESTicketView), 32), 32);
        if (tmp == (void*)NULL) {
            __OSReturnToMenuForError();
        }

        rc = ESP_GetTicketViews(titleId, tmp, &ticketCnt);
        if (rc != 0) {
            __OSReturnToMenuForError();
        }

        memcpy(tik, tmp, sizeof(ESTicketView));
    } else if (rc != 0) {
        __OSReturnToMenuForError();
    } else if (OSPlayTimeIsLimited()) {
        __OSPlayTimeType type = OSPLAYTIME_PERMANENT;
        u32 remain = 0xFFFFFFFF;

        __OSGetPlayTime(tik, &type, &remain);
        if (remain == 0) {
            __OSWriteExpiredFlag();
            __OSReturnToMenuForError();
        }
    }

    rc = ESP_LaunchTitle(titleId, tik);
    if (rc != 0) {
        __OSReturnToMenuForError();
    }

    while (TRUE) {
        ;
    }
}

void __OSLaunchTitle(ESTitleId titleId) {
    s32 rc;
    ESTicketView* tik;
    ESTicketView* list;
    u32 ticketCnt = 1;

    rc = ESP_InitLib();
    if (rc != 0) {
        return;
    }

    tik = OSAllocFromMEM1ArenaLo(ROUND_UP(sizeof(ESTicketView), 32), 32);
    if (tik == NULL) {
        return;
    }

    memset(tik, 0, ROUND_UP(sizeof(ESTicketView), 32));

    rc = ESP_GetTicketViews(titleId, NULL, &ticketCnt);
    if (rc != 0) {
        return;
    }

    list = OSAllocFromMEM1ArenaLo(
        ROUND_UP(sizeof(ESTicketView) * ticketCnt, 32), 32);
    if (list == NULL) {
        return;
    }

    rc = ESP_GetTicketViews(titleId, list, &ticketCnt);
    if (rc != 0) {
        return;
    }

    rc = __OSGetValidTicketIndex(list, ticketCnt);
    if (rc < 0) {
        return;
    }

    memcpy(tik, &list[rc], sizeof(ESTicketView));

    rc = ESP_LaunchTitle(titleId, tik);
    if (rc != 0) {
        return;
    }

    while (TRUE) {
        ;
    }
}

static void LaunchCommon(ESTitleId titleId, u32 launchCode,
                         char* const argv[], BOOL launchCheck) {
    OSStateFlags state;
    OSNandbootInfo* info;
    u8* bi2;
    s32 argvlen;
    char titleIdString[20];
    char** argvToPass;
    s32 i;
    ESTitleId title ALIGN(32);
    ESTmdView* tmd = NULL;
    u32 tmdSize = 0;
    s32 rv = 0;

    rv = ESP_InitLib();
    if (rv != 0) {
        __OSReturnToMenuForError();
    }

    rv = ESP_GetTmdView(titleId, NULL, &tmdSize);
    if (rv != 0) {
        __OSReturnToMenuForError();
    }

    tmd = OSAllocFromMEM1ArenaLo(ROUND_UP(tmdSize, 32), 64);
    if (tmd == (void*)NULL) {
        __OSReturnToMenuForError();
    }

    rv = ESP_GetTmdView(titleId, tmd, &tmdSize);
    if (rv != 0) {
        __OSReturnToMenuForError();
    }

    if (!__OSCheckTmdSysVersion(tmd)) {
        OSReport("OSLaunchTitle(): Firmware is not installed\n");
        __OSReturnToMenuForError();
    }

    if (launchCheck) {
        if (!__OSCheckCompanyCode(titleId, FALSE)) {
            OSReport("OSLaunchTitle(): Company code is not correct\n");
            __OSReturnToMenuForError();
        }

        if (!__OSCheckTmdCountryCode(tmd)) {
            OSReport("OSLaunchTitle(): Country code is not correct\n");
            __OSReturnToMenuForError();
        }
    }

    if (!__OSCheckTmdDriveSpinFlag(tmd)) {
        if (__DVDGetCoverStatus() == DVD_COVER_CLOSED) {
            __DVDResetWithNoSpinup();
        }
    }

    if (argv != NULL || launchCode != 0) {
        bi2 = OSAllocFromMEM1ArenaLo(0x2000, 64);
        info = (OSNandbootInfo*)(bi2 + (0x2000 - sizeof(OSNandbootInfo)));

        sprintf(titleIdString, "%016llx", titleId);

        argvlen = 0;
        if (argv != NULL) {
            while (argv[argvlen] != NULL) {
                argvlen++;
            }
        }

        argvlen += 1;
        argvToPass = OSAllocFromMEM1ArenaLo((argvlen + 1) * sizeof(char*), 1);
        argvToPass[0] = titleIdString;

        for (i = 1; i < argvlen; i++) {
            argvToPass[i] = argv[i - 1];
        }

        PackArgs(bi2, argvlen, argvToPass);

        if (__OSInIPL) {
            title = SYSTEM_MENU_TITLE_ID;
        } else {
            rv = ESP_InitLib();
            if (rv != 0) {
                OSReport("\nOSExec(): Failed to exec %d in %d\n", rv, 1719);
                __OSHotResetForError();
            }

            rv = ESP_GetTitleId(&title);
            if (rv != 0) {
                OSReport("\nOSExec(): Failed to exec %d in %d\n", rv, 1727);
                __OSHotResetForError();
            }
        }

        info->LastTitleId = title;
        info->ArgOffset = *(u32*)&bi2[8];
        info->LastAppType = OSGetAppType();
        if (titleId == SYSTEM_MENU_TITLE_ID) {
            info->ReturnType = 4;
        } else {
            info->ReturnType = 2;
        }
        info->ArgValue = launchCode;

        __OSCreateNandbootInfo();
        __OSWriteNandbootInfo(info);

        __OSReadStateFlags(&state);
        state.BYTE_0x5 = 3;
        if (titleId == SYSTEM_MENU_TITLE_ID) {
            state.discState = __OSGetDiscState(state.discState);
            state.BYTE_0x7 = 2;
        }
        __OSWriteStateFlags(&state);
    }

    OSDisableScheduler();
    __OSShutdownDevices(OS_SD_EVENT_LAUNCH_APP);
    OSEnableScheduler();
    __OSLaunchTitle(titleId);
    __OSLaunchMenu();
}

void __OSLaunchTitlevForSystem(ESTitleId titleId, char* const argv[]) {
#pragma unused(titleId)
#pragma unused(argv)

    OSReport("__OSLaunchTitlevForSystem(): only system can call this "
             "function\n");
}

void __OSLaunchTitlelForSystem(ESTitleId titleId, const char* arg0, ...) {
#pragma unused(titleId)
#pragma unused(arg0)

    OSReport("__OSLaunchTitlelForSystem(): only system can call this "
             "function\n");
}

void __OSReturnToMenul(u8 type, const char* arg0, ...) {
    va_list list;
    char* ptr;
    s32 i;
    char** argv;

    __OSUnRegisterStateEvent();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);

    argv = OSAllocFromMEM1ArenaLo(sizeof(char*), 0x1000);

    va_start(list, arg0);
    i = 0;
    ptr = (char*)arg0;
    while ((argv[i++] = ptr) != NULL) {
        ptr = va_arg(list, char*);
    }
    va_end(list);

    LaunchCommon(SYSTEM_MENU_TITLE_ID, type, argv, FALSE);
    __OSReturnToMenuForError();
}

void OSLaunchDisk(void) {
    OSReport("OSLaunchDisk(): You can't call this API from DVD application.  "
             "\n");
    OSError("");
    OSReport("OSLaunchDisk(): You must call DVDPrepareDisk before launching "
             "disc.\n");
    OSReport("OSLaunchDisk(): Specified id is different from one specified to "
             "DVDPrepareDisk.\n");
}

void OSLaunchDiskl(void) {
    OSReport("0000000000000000");
}

static inline void ReadDisc(void* addr, s32 length, u32 offset) {
    DVDCommandBlock block;
    GXColor bg = {0, 0, 0, 0};
    GXColor fg = {255, 255, 255, 0};

    DVDReadAbsAsyncPrio(&block, addr, length, offset, NULL, 0);

    while (DVDGetCommandBlockStatus(&block) != DVD_STATE_IDLE) {
        if (DVDGetCommandBlockStatus(&block) > DVD_STATE_WAITING ||
            DVDGetCommandBlockStatus(&block) < DVD_STATE_IDLE) {
            __OSReturnToMenuForError();
        }
    }
}

static u32 GetApploaderPosition(void) {
    static u32 apploaderPosition = 0;

    if (apploaderPosition != 0) {
        return apploaderPosition;
    }

    if (__OSCurrentTGCOffset != 0) {
        u32* tgcHeader;
        s32 apploaderOffsetInTGC;

        tgcHeader = OSAllocFromMEM1ArenaLo(64, 32);
        ReadDisc(tgcHeader, 64, (u32)(__OSCurrentTGCOffset >> 2));
        apploaderOffsetInTGC = *(s32*)((u8*)tgcHeader + 56);
        apploaderPosition =
            (u32)((__OSCurrentTGCOffset + apploaderOffsetInTGC) >> 2);
    } else {
        apploaderPosition = 0x2440 >> 2;
    }

    return apploaderPosition;
}

static ImgHeader* LoadApploader(void) {
    ImgHeader* header;

    header = OSAllocFromMEM1ArenaLo(sizeof(ImgHeader), 32);
    ReadDisc(header, sizeof(ImgHeader), GetApploaderPosition());
    ReadDisc((void*)0x81200000, (s32)ROUND_UP(header->size, 32),
             GetApploaderPosition() + (sizeof(ImgHeader) >> 2));
    ICInvalidateRange((void*)0x81200000, ROUND_UP(header->size, 32));

    return header;
}

static BOOL IsNewApploader(ImgHeader* header) {
    if (strncmp(header->date, "2004/02/01", 10) > 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static void* LoadDol(const OSExecParams* params, AppInterfaceFunc getInterface) {
    AppInitFunc appInit;
    AppGetNextFunc appGetNext;
    AppGetEntryFunc appGetEntry;
    void* addr;
    u32 length;
    u32 offset;
    OSExecParams* paramsWork;

    getInterface(&appInit, &appGetNext, &appGetEntry);
    paramsWork = OSAllocFromMEM1ArenaLo(sizeof(OSExecParams), 1);
    __OSSetExecParams(params, paramsWork);
    appInit(OSReport);
    OSSetArenaLo(paramsWork);

    while (appGetNext(&addr, &length, &offset)) {
        ReadDisc(addr, (s32)length, offset >> __DVDLayoutFormat);
    }

    return appGetEntry();
}

static void StartDol(const OSExecParams* params, void* entry) {
    OSExecParams* paramsWork;

    paramsWork = OSAllocFromMEM1ArenaLo(sizeof(OSExecParams), 1);
    __OSSetExecParams(params, paramsWork);
    PI_HW_REGS[PI_RESET] = 0x00000004 | 0x00000001 | 2;
    OSDisableInterrupts();
    Run(entry);
}

void __OSBootDolSimple(u32 doloffset, u32 restartCode, void* regionStart,
                       void* regionEnd, BOOL argsUseDefault, s32 argc,
                       char* argv[]) {
    OSExecParams* params;
    void* dolEntry;
    ImgHeader* header;
    DVDDiskID* diskId;

    OSDisableInterrupts();

    if (__OSInReboot) {
        __OSNextPartitionType = OS_LAUNCH_PARTITION_TYPE;
    }

    params = OSAllocFromMEM1ArenaLo(sizeof(OSExecParams), 1);
    params->valid = TRUE;
    params->restartCode = restartCode;
    params->regionStart = regionStart;
    params->regionEnd = regionEnd;
    params->argsUseDefault = argsUseDefault;

    if (!argsUseDefault) {
        params->argsAddr = OSAllocFromMEM1ArenaLo(0x2000, 1);

        if (__OSNextPartitionType == 2 && !__OSInReboot) {
            PackInstallerArgs(params->argsAddr, argc, argv);
        } else {
            PackArgs(params->argsAddr, argc, argv);
        }
    }

    DVDInit();
    DVDSetAutoInvalidation(TRUE);
    DVDResume();

    Prepared = FALSE;
    __DVDPrepareResetAsync(Callback);

    __OSMaskInterrupts(~0xF);
    __OSUnmaskInterrupts(OS_INTR_MASK(OS_INTR_PI_ACR));
    OSEnableInterrupts();

    while (Prepared != TRUE) {
        ;
    }

    __OSLaunchNextFirmware();

    if (restartCode == 0xA0000000 && !__OSInReboot) {
        ESTitleId titleId ALIGN(32);
        s32 rc;
        char* ptr;

        rc = ESP_InitLib();
        if (rc != 0) {
            return;
        }

        rc = ESP_GetTitleId(&titleId);
        if (rc != 0) {
            return;
        }

        rc = ESP_CloseLib();
        if (rc != 0) {
            return;
        }

        ptr = (char*)params->argsAddr + (u32)argv[1];
        snprintf(ptr, 16 + 1, "%016llx", titleId);
    }

    header = LoadApploader();

    if (IsNewApploader(header)) {
        if (doloffset == 0xFFFFFFFF) {
            doloffset = GetApploaderPosition() +
                        ((sizeof(ImgHeader) + header->size) >> 2);
        }

        params->bootDol = doloffset;
        dolEntry = LoadDol(params, (AppInterfaceFunc)header->entry);

        diskId = (DVDDiskID*)OSPhysicalToCached(0x0000);
        *(u32*)OSPhysicalToCached(OS_PHYS_CURRENT_APP_NAME) =
            *(u32*)diskId->game;
        *(u8*)OSPhysicalToCached(OS_PHYS_CURRENT_APP_TYPE) = OS_APP_TYPE_DVD;

        StartDol(params, dolEntry);
    } else {
        *(void**)0x812FDFF0 = regionStart;
        *(void**)0x812FDFEC = regionEnd;
        *(u8*)OSPhysicalToCached(0x30E2) = 1;

        ReadDisc((void*)0x81330000, (s32)ROUND_UP(header->rebootSize, 32),
                 GetApploaderPosition() +
                     ((sizeof(ImgHeader) + header->size) >> 2));
        ICInvalidateRange((void*)0x81330000,
                          ROUND_UP(header->rebootSize, 32));
        OSDisableInterrupts();
        ICFlashInvalidate();
        Run((void*)0x81330000);
    }
}

void __OSBootDol(u32 doloffset, u32 restartCode, const char** argv) {
    char doloffInString[20];
    s32 argvlen;
    char** argvToPass;
    s32 i;
    void* saveStart;
    void* saveEnd;

    OSGetSaveRegion(&saveStart, &saveEnd);
    sprintf(doloffInString, "%d", doloffset);

    argvlen = 0;
    if (argv != NULL) {
        while (argv[argvlen] != NULL) {
            argvlen++;
        }
    }

    argvlen += 1;
    argvToPass = OSAllocFromMEM1ArenaLo((argvlen + 1) * sizeof(char*), 1);
    argvToPass[0] = doloffInString;

    for (i = 1; i < argvlen; i++) {
        argvToPass[i] = (char*)argv[i - 1];
    }

    __OSBootDolSimple(0xFFFFFFFF, restartCode, saveStart, saveEnd, FALSE,
                      argvlen, argvToPass);
}

void __OSLaunchPartition(ESTitleId titleId, u32 launchCode,
                         char* const argv[]) {
    ESTitleId title;
    NANDStatus status;
    char path[32];
    NANDFileSystemStatus fsStatus;
    u8 appType;
    s32 argc;
    char** argvToPass;
    s32 i;
    OSNandbootInfo* info;
    s32 rv;

    appType = OSGetAppType();
    if (appType == OS_APP_TYPE_CHANNEL) {
        OSReport("OSLaunchPartition(): You can't call this API from NAND "
                 "application.  \n");

        // clang-format off
#line 2841
        OSError("");
        // clang-format on
    }

    if (titleId != 0 && (u32)(titleId >> 32) != 0x00010000 &&
        (u32)(titleId >> 32) != 0x00010004) {
        OSReport("OSLaunchPartition(): Specified title ID is not DISC "
                 "application.  \n");

        // clang-format off
#line 2850
        OSError("");
        // clang-format on
    }

    OS_NAND_TITLE_LAUNCH_CODE = launchCode;
    OS_NAND_TITLE_RETURN_CODE = 0;
    *(u8*)OSPhysicalToCached(0x3186) = appType;

    if (titleId != 0) {
        sprintf(path, "/title/%08x/%08x", (u32)(titleId >> 32), (u32)titleId);

        rv = NANDGetStatus(path, &status);
        switch (rv) {
        case NAND_RESULT_OK:
            break;
        case NAND_RESULT_NOEXISTS:
            if (NANDSecretGetFileSystemStatus(&fsStatus) != NAND_RESULT_OK) {
                OSReport("\nOSLaunchPartition(): Failed to get free i-nodes "
                         "number\n");
                __OSHotResetForError();
            }

            if (0x17FF - fsStatus.occupiedInodes < 5) {
                OSReport("\nOSLaunchPartition(): There are not enough "
                         "i-nodes to launch next partition\n");
                __OSHotResetForError();
            }
            break;
        default:
            OSReport("\nOSLaunchPartition(): Failed to get nand status\n");
            __OSHotResetForError();
            break;
        }
    }

    sprintf(path, "0000000000000000");

    argc = 0;
    if (argv != NULL) {
        while (argv[argc] != NULL) {
            argc++;
        }
    }

    argc += 1;
    argvToPass = OSAllocFromMEM1ArenaLo((argc + 1) * sizeof(char*), 1);
    argvToPass[0] = path;

    for (i = 1; i < argc; i++) {
        argvToPass[i] = argv[i - 1];
    }

    argvToPass[argc] = NULL;

    info = OSAllocFromMEM1ArenaLo(sizeof(OSNandbootInfo), 64);
    memset(info, 0, sizeof(OSNandbootInfo));

    rv = ESP_InitLib();
    if (rv != 0) {
        OSReport("\nOSExec(): Failed to exec %d in %d\n", rv, 2925);
        __OSHotResetForError();
    }

    rv = ESP_GetTitleId(&title);
    if (rv != 0) {
        OSReport("\nOSExec(): Failed to exec %d in %d\n", rv, 2933);
        __OSHotResetForError();
    }

    rv = ESP_CloseLib();
    if (rv != 0) {
        OSReport("\nOSExec(): Failed to exec %d in %d\n", rv, 2941);
        __OSHotResetForError();
    }

    info->LastTitleId = title;
    info->LastAppType = appType;
    __OSCreateNandbootInfo();
    __OSWriteNandbootInfo(info);

    __OSNextPartitionType = (u32)titleId;
    __OSBootDol(0, 0xA0000000, (const char**)argvToPass);

    OSDisableScheduler();
    __OSShutdownDevices(1);
    __OSHotResetForError();
}

void OSLaunchPartitionl(ESTitleId titleId, u32 launchCode, const char* arg0,
                        ...) {
    va_list list;
    char* ptr;
    s32 i;
    char** argv;

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();

    OSDisableScheduler();
    __OSShutdownDevices(OS_SD_EVENT_LAUNCH_APP);
    OSEnableScheduler();

    OSDisableInterrupts();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);

    argv = OSAllocFromMEM1ArenaLo(sizeof(char*), 0x1000);

    va_start(list, arg0);
    i = 0;
    ptr = (char*)arg0;
    while ((argv[i++] = ptr) != NULL) {
        ptr = va_arg(list, char*);
    }
    va_end(list);

    __OSLaunchPartition(titleId, launchCode, argv);
}
