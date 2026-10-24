#include <revolution/AI.h>
#include <revolution/BASE.h>
#include <revolution/ESP.h>
#include <revolution/NAND.h>
#include <revolution/OS.h>
#include <revolution/VI.h>
#include <string.h>

#define EXPIRED_FLAG_PATH "/shared2/expired"

typedef struct OSExpireAIFade {
    s16 buffer[2][48 * 2 * 3]; // at 0x0
    s32 bufferIdx;             // at 0x480
    s16* src;                  // at 0x484
    u32 frames;                // at 0x488
    s16 left;                  // at 0x48C
    s16 right;                 // at 0x48E
    AIDMACallback gameCallback; // at 0x490
} OSExpireAIFade;

OSAlarm __OSExpireAlarm;
s64 __OSExpireTime;
OSThread* __OSExpireThread;
BOOL __OSExpireSetExpiredFlag;

static OSExpireAIFade* __OSExpireAIFade = NULL;

static void* __OSPlayTimeRebootThread(void* arg);

BOOL OSPlayTimeIsLimited(void) {
    return __OSExpireTime != 0;
}

static void __OSPlayTimeRebootCallback(OSAlarm* alarm, OSContext* ctx) {
#pragma unused(alarm)
#pragma unused(ctx)

    void* arenaHi;
    OSThread* thread;
    void* stack;
    u32 size;

    for (thread = OS_THREAD_QUEUE.head; thread != NULL;
         thread = thread->nextActive) {
        OSSuspendThread(thread);
    }

    size = ROUND_UP(sizeof(OSThread), 32) + 0x1000;
    arenaHi = OS_USABLE_MEM2_END;
    arenaHi = (u8*)arenaHi - size;

    thread = (OSThread*)arenaHi;
    arenaHi = (u8*)arenaHi + ROUND_UP(sizeof(OSThread), 32);
    stack = arenaHi;

    if (!OSCreateThread(thread, __OSPlayTimeRebootThread, NULL,
                        (u8*)stack + 0x1000, 0x1000, 0, 0)) {
        __OSHotResetForError();
    }

    OSResumeThread(thread);
}

static void __OSPlayTimeFadeLastAIDCallback(void) {
    if (__OSExpireAIFade->gameCallback != NULL) {
        __OSExpireAIFade->gameCallback();
    }

    if (__OSExpireAIFade->frames == 0) {
        __OSExpireAIFade->src = (s16*)OSPhysicalToCached(AIGetDMAStartAddr());
    }

    if (__OSExpireAIFade->frames == 1) {
        DCInvalidateRange(__OSExpireAIFade->src, 4);
        __OSExpireAIFade->left = *__OSExpireAIFade->src++;
        __OSExpireAIFade->right = *__OSExpireAIFade->src;
    }

    if (__OSExpireAIFade->frames >= 1) {
        s16* buffer =
            __OSExpireAIFade->buffer[__OSExpireAIFade->bufferIdx];
        s16* dst = buffer;
        u32 len = AIGetDMALength();
        u32 i = len;
        f32 scale = 0.995f;

        while (i != 0) {
            *dst++ = __OSExpireAIFade->left;
            *dst++ = __OSExpireAIFade->right;

            __OSExpireAIFade->left *= scale;
            __OSExpireAIFade->right *= scale;

            i -= 4;
        }

        DCFlushRange(buffer, len);
        AIInitDMA(buffer, len);

        __OSExpireAIFade->bufferIdx++;
        __OSExpireAIFade->bufferIdx &= 1;
    }

    __OSExpireAIFade->frames++;
}

BOOL __OSWriteExpiredFlag(void) {
    s32 result = NAND_RESULT_OK;
    NANDFileInfo file;
    BOOL opened = FALSE;
    u8 titleId[32] ALIGN(32);

    result = NANDPrivateCreate(EXPIRED_FLAG_PATH, NAND_PERM_RWALL, 0);
    if (result != NAND_RESULT_OK && result != NAND_RESULT_EXISTS) {
        goto exit;
    }

    result = NANDPrivateOpen(EXPIRED_FLAG_PATH, &file, NAND_ACCESS_WRITE);
    if (result != NAND_RESULT_OK) {
        goto exit;
    }

    opened = TRUE;

    result = ESP_InitLib();
    if (result != 0) {
        goto exit;
    }

    memset(titleId, 0, sizeof(titleId));
    result = ESP_GetTitleId((ESTitleId*)titleId);
    if (result != 0) {
        goto exit;
    }

    result = NANDWrite(&file, titleId, sizeof(titleId));
    if (result < 0) {
        goto exit;
    } else if (result != 32) {
        result = NAND_RESULT_INVALID;
        goto exit;
    } else {
        result = NAND_RESULT_OK;
    }

exit:
    if (opened) {
        NANDClose(&file);
    }

    return result == NAND_RESULT_OK ? TRUE : FALSE;
}

static BOOL __OSWriteExpiredFlagIfSet(void) {
    if (__OSExpireSetExpiredFlag) {
        return __OSWriteExpiredFlag();
    }

    return FALSE;
}

static void* __OSPlayTimeRebootThread(void* arg) {
#pragma unused(arg)

    BOOL enabled;
    u32 frames;
    u32 dim = 1;
    OSExpireAIFade fade ALIGN(32);

    __OSExpireAIFade = &fade;
    memset(__OSExpireAIFade, 0, sizeof(OSExpireAIFade));
    __OSExpireAIFade->gameCallback =
        AIRegisterDMACallback(__OSPlayTimeFadeLastAIDCallback);

    for (frames = 0; frames < 20; frames++) {
        dim = frames / 5 + 1;
        if (dim > 7) {
            dim = 7;
        }

        VIWaitForRetrace();
        __OSSetVIForceDimming(TRUE, dim, dim);
    }

    AIRegisterDMACallback(NULL);
    VISetBlack(TRUE);
    VIFlush();

    enabled = OSDisableInterrupts();
    __OSWriteExpiredFlagIfSet();
    OSRestoreInterrupts(enabled);

    OSReturnToMenu();
    return NULL;
}

static void __OSPlayTimeAlarmExpired(OSAlarm* alarm, OSContext* ctx) {
#pragma unused(alarm)
#pragma unused(ctx)

    void* arenaHi;
    OSThread* thread;
    void* stack;
    u32 size;

    if (__OSExpireThread != NULL) {
        for (thread = OS_THREAD_QUEUE.head; thread != NULL;
             thread = thread->nextActive) {
            if (thread != __OSExpireThread) {
                OSSuspendThread(thread);
            }
        }

        OSCreateAlarm(&__OSExpireAlarm);
        OSSetAlarm(&__OSExpireAlarm, OS_SEC_TO_TICKS(240LL),
                   __OSPlayTimeRebootCallback);

        while (__OSExpireThread->suspend > 0) {
            OSResumeThread(__OSExpireThread);
        }
    } else {
        for (thread = OS_THREAD_QUEUE.head; thread != NULL;
             thread = thread->nextActive) {
            OSSuspendThread(thread);
        }

        size = ROUND_UP(sizeof(OSThread), 32) + 0x1000;
        arenaHi = OS_USABLE_MEM2_END;
        arenaHi = (u8*)arenaHi - size;

        thread = (OSThread*)arenaHi;
        arenaHi = (u8*)arenaHi + ROUND_UP(sizeof(OSThread), 32);
        stack = arenaHi;

        if (!OSCreateThread(thread, __OSPlayTimeRebootThread, NULL,
                            (u8*)stack + 0x1000, 0x1000, 0, 0)) {
            __OSHotResetForError();
        }

        OSResumeThread(thread);
    }
}

static s32 __OSPlayTimeGetConsumption(ESTicketView* ticket, ESLpEntry* entries,
                                      u32* count) {
    s32 result = ESP_GetConsumption(ticket->ticketID, NULL, count);

    if (result > 0) {
        goto exit;
    } else if (result != 0) {
        result = result;
        goto exit;
    }

    if (*count != 0) {
        result = ESP_GetConsumption(ticket->ticketID, entries, count);
        if (result != 0) {
            result = result;
            goto exit;
        }
    }

exit:
    return result;
}

s32 __OSGetPlayTime(ESTicketView* ticket, __OSPlayTimeType* type,
                    u32* playTime) {
    s32 result;
    u32 i;
    ESLpEntry entries[8] ALIGN(32);
    u32 count = 0;
    u32 other = 0;
    ESTicketView aligned ALIGN(32);

    if ((u32)ticket & 31) {
        memcpy(&aligned, ticket, sizeof(ESTicketView));
        ticket = &aligned;
    }

    result = __OSPlayTimeGetConsumption(ticket, entries, &count);
    if (result != 0) {
        goto exit;
    }

    for (i = 0; i < 8; i++) {
        if (ticket->limits[i].code == OSPLAYTIME_LIMITED) {
            *type = OSPLAYTIME_LIMITED;

            if (count == 0) {
                *playTime = ticket->limits[i].limit;
            } else if (entries[i].limit >= ticket->limits[i].limit) {
                *playTime = 0;
            } else {
                *playTime = ticket->limits[i].limit - entries[i].limit;
            }

            goto exit;
        } else if (ticket->limits[i].code != 0) {
            other = i + 1;
        }
    }

    if (!other) {
        *type = OSPLAYTIME_PERMANENT;
        *playTime = 0xFFFFFFFF;
    } else {
        other--;

        if (ticket->limits[other].code == OSPLAYTIME_LIMITED_LAUNCH) {
            *type = OSPLAYTIME_LIMITED_LAUNCH;
            *playTime = ticket->limits[other].limit;

            if (count > 0) {
                *playTime -= entries[other].limit;
            }
        } else {
            *type = OSPLAYTIME_OTHER;
        }
    }

exit:
    return result;
}

static s32 __OSGetPlayTimeCurrent(__OSPlayTimeType* type, u32* playTime) {
    s32 result;
    ESTicketView ticket ALIGN(32);

    result = ESP_DiGetTicketView(NULL, &ticket);
    if (result == -1017) {
        goto exit;
    }

    if (result != 0) {
        result = result;
        goto exit;
    }

    result = __OSGetPlayTime(&ticket, type, playTime);

exit:
    return result;
}

void __OSInitPlayTime(void) {
    s32 result;
    u32 limit;
    __OSPlayTimeType type;

    __OSExpireTime = 0;
    __OSExpireThread = NULL;
    __OSExpireSetExpiredFlag = TRUE;

    result = ESP_InitLib();
    if (result != 0) {
        result = result;
        goto exit;
    }

    result = __OSGetPlayTimeCurrent(&type, &limit);
    if (result != 0) {
        if (result != -1017) {
            result = result;
        }

        goto exit;
    }

    if (type == OSPLAYTIME_PERMANENT) {
        goto exit;
    } else if (type == OSPLAYTIME_LIMITED) {
        if (limit == 0) {
            OSPanic(__FILE__, 775, "Expired");
        }

        OSCreateAlarm(&__OSExpireAlarm);
        OSSetAlarm(&__OSExpireAlarm, OS_SEC_TO_TICKS((s64)limit + 1),
                   __OSPlayTimeAlarmExpired);
        __OSExpireTime = __OSExpireAlarm.end;
        OSReport("PlayTime: %d seconds left\n", limit);
    }

exit:
    ESP_CloseLib();
}
