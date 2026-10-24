#include <revolution/DVD.h>
#include <revolution/OS.h>
#include <revolution/PAD.h>
#include <revolution/SC.h>
#include <revolution/VI.h>
#include <string.h>

static OSShutdownFunctionQueue ShutdownFunctionQueue;
static u32 bootThisDol = 0;
volatile BOOL __OSIsReturnToIdle = FALSE;

static void KillThreads(void);

void OSRegisterShutdownFunction(OSShutdownFunctionInfo* info) {
    OSShutdownFunctionInfo* it;
    OSShutdownFunctionInfo* prev;
    OSShutdownFunctionInfo* tail;

    for (it = ShutdownFunctionQueue.head; it != NULL && it->prio <= info->prio;
         it = it->next) {
        ;
    }

    if (it == NULL) {

        tail = ShutdownFunctionQueue.tail;
        if (tail == NULL) {
            ShutdownFunctionQueue.head = info;
        } else {
            ShutdownFunctionQueue.tail->next = info;
        }

        info->prev = tail;
        info->next = NULL;

        it = ShutdownFunctionQueue.head;
        ShutdownFunctionQueue.tail = info;
    } else {
        info->next = it;

        prev = it->prev;
        it->prev = info;
        info->prev = prev;

        if (prev == NULL) {
            ShutdownFunctionQueue.head = info;
        } else {
            prev->next = info;
        }
    }
}

BOOL __OSCallShutdownFunctions(u32 pass, u32 event) {
    OSShutdownFunctionInfo* iter;
    BOOL failure;
    u32 prio;

    prio = 0;
    failure = FALSE;

    for (iter = ShutdownFunctionQueue.head; iter != NULL; iter = iter->next) {
        if (failure && prio != iter->prio) {
            break;
        }

        failure |= !iter->func(pass, event);
        prio = iter->prio;
    }

    failure |= !__OSSyncSram();

    return !failure;
}

void __OSShutdownDevices(u32 event) {
    BOOL padIntr;
    BOOL osIntr;
    BOOL keepEnable;

    switch (event) {
    case 0:
    case OS_SD_EVENT_RETURN_TO_MENU:
    case OS_SD_EVENT_LAUNCH_APP:
        keepEnable = FALSE;
        break;
    case 1:
    case OS_SD_EVENT_SHUTDOWN:
    case 3:
    case OS_SD_EVENT_RESTART:
    default:
        keepEnable = TRUE;
        break;
    }

    __OSStopAudioSystem();

    if (!keepEnable) {
        padIntr = __PADDisableRecalibration(TRUE);
    }

    while (!__OSCallShutdownFunctions(FALSE, event)) {
        ;
    }

    while (!__OSSyncSram()) {
        ;
    }

    osIntr = OSDisableInterrupts();
    __OSCallShutdownFunctions(TRUE, event);
    LCDisable();

    if (!keepEnable) {
        __PADDisableRecalibration(padIntr);
    }

    KillThreads();
}

u8 __OSGetDiscState(u8 last) {
    u32 flags;

    if (__DVDGetCoverStatus() != DVD_COVER_CLOSED) {
        return 3;
    }

    if (last != 1 || (__OSGetRTCFlags(&flags) && flags != 0)) {
        return 2;
    }

    return 1;
}

void OSShutdownSystem(void) {
    SCIdleModeInfo idleMode;
    OSStateFlags stateFlags;
    OSIOSRev iosRev;

    memset(&idleMode, 0, sizeof(SCIdleModeInfo));
    SCInit();
    while (SCCheckStatus() == SC_STATUS_BUSY) {
        ;
    }
    SCGetIdleMode(&idleMode);

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();
    __DVDPrepareReset();
    __OSReadStateFlags(&stateFlags);

    stateFlags.discState = __OSGetDiscState(stateFlags.discState);
    if (idleMode.wc24 == TRUE) {
        stateFlags.BYTE_0x5 = 5;
    } else {
        stateFlags.BYTE_0x5 = 1;
    }

    __OSClearRTCFlags();
    __OSWriteStateFlags(&stateFlags);
    __OSGetIOSRev(&iosRev);

    if (idleMode.wc24 == TRUE) {
        __OSIsReturnToIdle = TRUE;

        OSDisableScheduler();
        __OSShutdownDevices(OS_SD_EVENT_RETURN_TO_MENU);
        OSEnableScheduler();
        __OSLaunchMenu();
    } else {
        OSDisableScheduler();
        __OSShutdownDevices(OS_SD_EVENT_SHUTDOWN);
        __OSShutdownToSBY();
    }
}

void OSRestart(u32 resetCode) {
    u8 type = OSGetAppType();

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();

    if (type == OS_APP_TYPE_CHANNEL) {
        OSDisableScheduler();
        __OSShutdownDevices(OS_SD_EVENT_RESTART);
        OSEnableScheduler();
        __OSRelaunchTitle();
    } else if (type == OS_APP_TYPE_DVD) {
        OSDisableScheduler();
        __OSShutdownDevices(OS_SD_EVENT_RESTART);
        OSEnableScheduler();
        __OSReboot(resetCode, bootThisDol);
    }

    OSDisableScheduler();
    __OSShutdownDevices(1);
    __OSHotResetForError();
}

static void KillThreads(void) {
    OSThread* iter;
    OSThread* next;

    for (iter = OS_THREAD_QUEUE.head; iter != NULL; iter = next) {
        next = iter->nextActive;

        switch (iter->state) {
        case OS_THREAD_STATE_SLEEPING:
        case OS_THREAD_STATE_READY:
            OSCancelThread(iter);
            break;
        }
    }
}

void __OSReturnToMenu(u8 menuMode) {
    OSStateFlags stateFlags;

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();
    __DVDPrepareReset();

    __OSReadStateFlags(&stateFlags);
    stateFlags.discState = __OSGetDiscState(stateFlags.discState);
    stateFlags.BYTE_0x5 = 3;
    stateFlags.BYTE_0x7 = menuMode;
    __OSClearRTCFlags();
    __OSWriteStateFlags(&stateFlags);

    OSDisableScheduler();
    __OSShutdownDevices(OS_SD_EVENT_RETURN_TO_MENU);
    OSEnableScheduler();

    __OSLaunchMenu();
    OSDisableScheduler();
    __VISetRGBModeImm();
    __OSHotResetForError();
}

void OSReturnToMenu(void) {
    __OSReturnToMenu(0);

    // clang-format off
#line 834
    OSError("OSReturnToMenu(): Falied to boot system menu.\n");
    // clang-format on
}

void OSReturnToDataManager(void) {
    __OSReturnToMenu(1);

    // clang-format off
#line 846
    OSError("OSReturnToDataManager(): Falied to boot system menu.\n");
    // clang-format on
}

void OSReturnToSetting(u8 setting) {
    const char* url;

    switch (setting) {
    case OS_SETTING_CALENDAR:
        url = "Calendar/Calendar_index.html";
        break;
    case OS_SETTING_DISPLAY:
        url = "Display/Display_index.html";
        break;
    case OS_SETTING_SOUND:
        url = "Sound/Sound_index.html";
        break;
    case OS_SETTING_PARENTAL:
        url = "Parental_Control/Parental_Control_index.html";
        break;
    case OS_SETTING_INTERNET:
        url = "Internet/Internet_index.html";
        break;
    case OS_SETTING_WC24:
        url = "WiiConnect24/Wiiconnect24_index.html";
        break;
    case OS_SETTING_UPDATE:
        url = "Update/Update_index.html";
        break;
    default:
        OSReport("OSReturnToSetting(): You can't specify %d.  \n", setting);

        // clang-format off
#line 910
        OSError("");
        // clang-format on
    }

    __OSReturnToMenul(1, url, NULL);
}

void __OSReturnToMenuForError(void) {
    OSStateFlags stateFlags;

    __OSReadStateFlags(&stateFlags);
    stateFlags.discState = 2;
    stateFlags.BYTE_0x5 = 3;
    __OSClearRTCFlags();
    __OSWriteStateFlags(&stateFlags);

    __OSLaunchMenu();
    OSDisableScheduler();
    __VISetRGBModeImm();
    __OSHotResetForError();

    // clang-format off
#line 949
    OSError("__OSReturnToMenu(): Falied to boot system menu.\n");
    // clang-format on
}

void __OSHotResetForError(void) {
    if (__OSInNandBoot || __OSInReboot) {
        __OSInitSTM();
    }

    __OSHotReset();

    // clang-format off
#line 973
    OSError("__OSHotReset(): Falied to reset system.\n");
    // clang-format on
}

u32 OSGetResetCode(void) {
    if (__OSRebootParams.valid) {
        return __OSRebootParams.restartCode | 0x80000000;
    }

    return PI_HW_REGS[PI_RESET] >> 3;
}

void OSResetSystem(u32 arg0, u32 arg1, u32 arg2) {
#pragma unused(arg0)
#pragma unused(arg1)
#pragma unused(arg2)

    // clang-format off
#line 1124
    OSError("OSResetSystem() is obsoleted. It doesn't work any longer.\n");
    // clang-format on
}

u32 OSSetBootDol(u32 offset) {
#pragma unused(offset)

    // clang-format off
#line 1140
    OSError("OSSetBootDol() is obsoleted. It doesn't work any longer.\n");
    // clang-format on
    return 0;
}
