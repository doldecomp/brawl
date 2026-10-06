#include <types.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <revolution/OS/OSHardware.h>

typedef void (*DWCLoginCallback)(s32 error, s32 profile, void* parameter);
/* Verified layout; the rest of the login controller remains opaque. */
typedef struct DWCLoginControlView {
    void* connection;
    s32 state;
    u32 product;
    u32 gameCode;
    char* playerName;
    DWCLoginCallback callback;
    void* parameter;
    void* userData;
    u8 unknown20[0x10];
    u32 timed;
    u32 unknown34;
    s64 startTime;
    u32 temporaryLoginId[3];
    char authToken[0x100];
    char authChallenge[0x100];
    char userName[28];
} DWCLoginControlView;
#ifdef __MWERKS__
typedef char DWCLoginSizeCheck[sizeof(DWCLoginControlView) == 0x268 ? 1 : -1];
typedef char DWCLoginTimerCheck[offsetof(DWCLoginControlView, startTime) == 0x38 ? 1 : -1];
typedef char DWCLoginCallbackCheck[offsetof(DWCLoginControlView, callback) == 0x14 ? 1 : -1];
typedef char DWCLoginTemporaryCheck[offsetof(DWCLoginControlView, temporaryLoginId) == 0x40 ? 1 : -1];
typedef char DWCLoginTokenCheck[offsetof(DWCLoginControlView, authToken) == 0x4C ? 1 : -1];
typedef char DWCLoginChallengeCheck[offsetof(DWCLoginControlView, authChallenge) == 0x14C ? 1 : -1];
typedef char DWCLoginUserNameCheck[offsetof(DWCLoginControlView, userName) == 0x24C ? 1 : -1];
#endif
extern DWCLoginControlView* lbl_805A0F80;
extern const char lbl_80489A00[];
extern void DWC_Printf(u32 level, const char* format, ...);
extern u64 fn_80350C0C(const void* loginId);
extern u32 fn_80350C1C(const void* loginId);
extern BOOL DWCi_RemoteLogin(void);
extern void DWCi_RemoteLoginProcess(void);
extern BOOL DWCi_IsError(void);
extern void DWCi_SetError(s32 error, s32 code);
extern s32 fn_80367C74(void* connection);
extern u64 OSGetTime(void);

void DWCi_LoginInit(void* control, void* userData, void* connection, u32 product, u32 gameCode,
                    char* playerName, DWCLoginCallback callback, void* parameter) {
    DWC_Printf(0x20, lbl_80489A00);
    lbl_805A0F80 = control;
    memset(control, 0, 0x268);
    lbl_805A0F80->connection = connection;
    lbl_805A0F80->state = 0;
    lbl_805A0F80->product = product;
    lbl_805A0F80->gameCode = gameCode;
    lbl_805A0F80->playerName = playerName;
    lbl_805A0F80->callback = callback;
    lbl_805A0F80->parameter = parameter;
    lbl_805A0F80->userData = userData;
    DWC_Printf(0x20, lbl_80489A00 + 0xC);
    DWC_Printf(0x20, lbl_80489A00 + 0x38, fn_80350C0C((u8*)userData + 4));
    DWC_Printf(0x20, lbl_80489A00 + 0x58, fn_80350C1C((u8*)userData + 4));
    DWC_Printf(0x20, lbl_80489A00 + 0x78, fn_80350C0C((u8*)userData + 0x10));
    DWC_Printf(0x20, lbl_80489A00 + 0x98, fn_80350C1C((u8*)userData + 0x10));
    DWC_Printf(0x20, lbl_80489A00 + 0xC);
}

BOOL DWCi_LoginAsync(void) {
    if (DWCi_RemoteLogin()) {
        lbl_805A0F80->state = 1;
        lbl_805A0F80->timed = 0;
        return 1;
    }
    return 0;
}

void DWCi_LoginProcess(void) {
    if (lbl_805A0F80 == NULL || DWCi_IsError()) return;
    switch (lbl_805A0F80->state) {
    case 1:
        DWCi_RemoteLoginProcess();
        break;
    case 2: case 3: case 4:
        if (lbl_805A0F80->connection != NULL && *(u32*)lbl_805A0F80->connection != 0)
            fn_80367C74(lbl_805A0F80->connection);
        if (lbl_805A0F80->timed != 0 &&
            (s64)(OSGetTime() - lbl_805A0F80->startTime) / (OS_BUS_CLOCK_SPEED / 4 / 1000) > 60000) {
            if (lbl_805A0F80 != NULL) {
                DWCi_SetError(6, -61070);
                if (lbl_805A0F80->callback != NULL)
                    lbl_805A0F80->callback(6, 0, lbl_805A0F80->parameter);
                if (lbl_805A0F80 != NULL) {
                    lbl_805A0F80->state = 0;
                    lbl_805A0F80->timed = 0;
                }
            }
            lbl_805A0F80->timed = 0;
        }
        break;
    default:
        DWC_Printf(4, lbl_80489A00 + 0xB8);
        break;
    }
}

void* DWCi_GetUserData(void) {
    if (lbl_805A0F80 != NULL) return lbl_805A0F80->userData;
    return NULL;
}

void DWCi_StopLogin(s32 error, s32 code) {
    if (lbl_805A0F80 == NULL || error == 0) return;
    DWCi_SetError(error, code);
    if (lbl_805A0F80->callback != NULL)
        lbl_805A0F80->callback(error, 0, lbl_805A0F80->parameter);
    if (lbl_805A0F80 != NULL) {
        lbl_805A0F80->state = 0;
        lbl_805A0F80->timed = 0;
    }
}

extern BOOL fn_80352AB8(void);
extern void fn_803522DC(void);
void DWCi_ShutdownLogin(void) {
    if (!fn_80352AB8()) fn_803522DC();
    lbl_805A0F80 = NULL;
}

s32 DWCi_LoginHandleGPError(s32 result) {
    s32 error;
    s32 code;
    if (result == 0) return 0;
    DWC_Printf(2, lbl_80489A00 + 0xD8, result);
    /* Other values leave these locals unset in the original. */
    switch (result) {
    case 1: error = 9; code = -1; break;
    case 2: error = 9; code = -2; break;
    case 3: error = 6; code = -10; break;
    case 4: error = 6; code = -20; break;
    }
    if (lbl_805A0F80 != NULL && error != 0) {
        DWCi_SetError(error, code - 61000);
        if (lbl_805A0F80->callback != NULL)
            lbl_805A0F80->callback(error, 0, lbl_805A0F80->parameter);
        if (lbl_805A0F80 != NULL) {
            lbl_805A0F80->state = 0;
            lbl_805A0F80->timed = 0;
        }
    }
    return result;
}

typedef struct DWCLoginUserProfileView { u8 unknown0[0x1C]; s32 profile; } DWCLoginUserProfileView;
typedef struct DWCLoginConnectEvent { s32 result; s32 profile; } DWCLoginConnectEvent;
typedef struct DWCLoginMatchTimeView {
    u8 unknown0[0x4B8];
    s64 startTime;
    s64 elapsedTime;
} DWCLoginMatchTimeView;
typedef char DWCLoginMatchTimeOffsetCheck[offsetof(DWCLoginMatchTimeView, elapsedTime) == 0x4C0 ? 1 : -1];
extern const char* fn_8034F7A4(void);
extern u64 fn_8034F684(void);
extern const char* fn_8034F79C(void);
extern s32 fn_80368058(void* connection, s32 field, const char* text);
extern DWCLoginMatchTimeView* fn_8034E158(void);
extern u32 fn_80342554(void);
extern s32 fn_80342328(s32 status);
extern s32 fn_8033AAF0(void);
extern s32 fn_8033CD90(s32 profile);
extern void DWCi_GPGetInfoCallback(void* connection, void* event, void* parameter);
extern s32 fn_80367F78(void* connection, s32 profile, s32 cache, s32 blocking,
                      void (*callback)(void*, void*, void*), void* parameter);

void DWCi_GPConnectCallback(void* connection, void* argument, void* parameter) {
    DWCLoginConnectEvent* event = argument;
    char identity[31];
    const char* gameName;
    const char* consoleName;
    u64 consoleId;
    u64 now;
    s64 start;
    DWCLoginMatchTimeView* match;
    DWC_Printf(0x20, lbl_80489A00 + 0xEC, event->result);
    lbl_805A0F80->timed = 0;
    gameName = fn_8034F7A4();
    consoleId = fn_8034F684();
    consoleName = fn_8034F79C();
    snprintf(identity, 31, lbl_80489A00 + 0x11C, consoleName, consoleId, gameName);
    if (DWCi_LoginHandleGPError(fn_80368058(connection, 0x704, identity)) != 0) return;
    if (event->result != 0) {
        DWCi_LoginHandleGPError(event->result);
        return;
    }
    if (lbl_805A0F80->state == 2) {
        if (((DWCLoginUserProfileView*)lbl_805A0F80->userData)->profile == event->profile) {
            DWC_Printf(0x20, lbl_80489A00 + 0x12C);
            lbl_805A0F80->state = 5;
            now = OSGetTime();
            start = fn_8034E158()->startTime;
            match = fn_8034E158();
            match->elapsedTime = (s64)(now - (u64)start);
            DWC_Printf(0x200000, lbl_80489A00 + 0x148,
                       (s32)(fn_8034E158()->elapsedTime / (OS_BUS_CLOCK_SPEED / 4 / 1000)));
            DWC_Printf(0x200000, lbl_80489A00 + 0x164, fn_80342554());
            if (DWCi_LoginHandleGPError(fn_80342328(1)) == 0) {
                lbl_805A0F80->callback(0, event->profile, lbl_805A0F80->parameter);
                if (fn_8033AAF0() == 0) fn_8033CD90(event->profile);
            }
        } else {
            DWC_Printf(0x20, lbl_80489A00 + 0x184);
            if (lbl_805A0F80 != NULL) {
                DWCi_SetError(6, -60000);
                if (lbl_805A0F80->callback != NULL)
                    lbl_805A0F80->callback(6, 0, lbl_805A0F80->parameter);
                if (lbl_805A0F80 != NULL) {
                    lbl_805A0F80->state = 0;
                    lbl_805A0F80->timed = 0;
                }
            }
        }
    } else if (lbl_805A0F80->state == 3) {
        DWCi_LoginHandleGPError(fn_80367F78(connection, event->profile, 0, 0, DWCi_GPGetInfoCallback, NULL));
    }
}

extern BOOL fn_80351284(const void* userData);
extern BOOL fn_8035126C(const void* loginId);
extern BOOL fn_8035121C(const void* loginId);
extern void fn_80351154(void* loginId);
extern void fn_80350C44(void* loginId, u32 playerId);
extern void fn_80350D74(const void* loginId, u32 gameCode, char* userName);
extern void* DWC_Alloc(int kind, u32 size);
extern void DWC_Free(int kind, void* allocation, int size);
extern BOOL fn_803520B8(const void* playerName, const char* authName, u64 userId,
                      void* (*alloc)(int, u32), void (*free)(int, void*, int));

BOOL DWCi_RemoteLogin(void) {
    u64 userId;
    DWC_Printf(0x20, lbl_80489A00 + 0x1A4);
    if (fn_80351284(lbl_805A0F80->userData)) {
        DWC_Printf(0x20, lbl_80489A00 + 0x1B8);
        fn_80350D74((u8*)lbl_805A0F80->userData + 0x10,
                   *(u32*)((u8*)lbl_805A0F80->userData + 0x24), lbl_805A0F80->userName);
        userId = fn_80350C0C((u8*)lbl_805A0F80->userData + 0x10);
    } else {
        DWC_Printf(0x20, lbl_80489A00 + 0x1E8);
        if (!fn_8035126C(lbl_805A0F80->temporaryLoginId)) {
            DWC_Printf(0x20, lbl_80489A00 + 0x218);
            if (fn_8035121C((u8*)lbl_805A0F80->userData + 4)) {
                u32* pseudo = (u32*)((u8*)lbl_805A0F80->userData + 4);
                DWC_Printf(0x20, lbl_80489A00 + 0x254);
                lbl_805A0F80->temporaryLoginId[0] = pseudo[0];
                lbl_805A0F80->temporaryLoginId[1] = pseudo[1];
                lbl_805A0F80->temporaryLoginId[2] = pseudo[2];
            } else {
                DWC_Printf(0x20, lbl_80489A00 + 0x280);
                fn_80351154(lbl_805A0F80->temporaryLoginId);
            }
        } else {
            DWC_Printf(0x20, lbl_80489A00 + 0x2AC);
            fn_80350C44(lbl_805A0F80->temporaryLoginId,
                       (u32)((OSGetTime() * 0x5D588B656C078965ULL + 0x269EC3) >> 32));
        }
        fn_80350D74(lbl_805A0F80->temporaryLoginId, lbl_805A0F80->gameCode, lbl_805A0F80->userName);
        userId = 0;
    }
    return fn_803520B8(lbl_805A0F80->playerName, lbl_805A0F80->userName + 9, userId, DWC_Alloc, DWC_Free);
}

extern void fn_80352418(void);
extern BOOL fn_80352AF4(void);
extern s32 fn_80352B0C(void);
extern void fn_80352B18(char* token, char* challenge);
extern u64 fn_80352B64(void);
extern void fn_80350C24(void* loginId, u64 userId);
extern s32 fn_80367D20(void* connection, const char* token, const char* challenge,
                     s32 firewall, s32 blocking,
                     void (*callback)(void*, void*, void*), void* parameter);

void DWCi_RemoteLoginProcess(void) {
    s32 result;
    fn_80352418();
    if (!fn_80352AB8()) return;
    if (fn_80352AF4()) {
        DWC_Printf(0x20, lbl_80489A00 + 0x2F0);
        fn_80352B18(lbl_805A0F80->authToken, lbl_805A0F80->authChallenge);
        if (fn_80351284(lbl_805A0F80->userData)) {
            DWC_Printf(0x20, lbl_80489A00 + 0x300);
            lbl_805A0F80->startTime = OSGetTime();
            lbl_805A0F80->timed = 1;
            result = fn_80367D20(lbl_805A0F80->connection, lbl_805A0F80->authToken,
                                lbl_805A0F80->authChallenge, 1, 0, DWCi_GPConnectCallback, NULL);
            if (DWCi_LoginHandleGPError(result) == 0) lbl_805A0F80->state = 2;
        } else {
            fn_80350C24(lbl_805A0F80->temporaryLoginId, fn_80352B64());
            DWC_Printf(0x20, lbl_80489A00 + 0x300);
            lbl_805A0F80->startTime = OSGetTime();
            lbl_805A0F80->timed = 1;
            result = fn_80367D20(lbl_805A0F80->connection, lbl_805A0F80->authToken,
                                lbl_805A0F80->authChallenge, 1, 0, DWCi_GPConnectCallback, NULL);
            if (DWCi_LoginHandleGPError(result) == 0) lbl_805A0F80->state = 3;
        }
    } else {
        result = fn_80352B0C();
        DWC_Printf(0x20, lbl_80489A00 + 0x328, result);
        if (result <= -29000) {
            if (lbl_805A0F80 != NULL) {
                DWCi_SetError(9, result);
                if (lbl_805A0F80->callback != NULL)
                    lbl_805A0F80->callback(9, 0, lbl_805A0F80->parameter);
                if (lbl_805A0F80 != NULL) {
                    lbl_805A0F80->state = 0;
                    lbl_805A0F80->timed = 0;
                }
            }
        } else {
            if (lbl_805A0F80 != NULL) {
                DWCi_SetError(2, result);
                if (lbl_805A0F80->callback != NULL)
                    lbl_805A0F80->callback(2, 0, lbl_805A0F80->parameter);
                if (lbl_805A0F80 != NULL) {
                    lbl_805A0F80->state = 0;
                    lbl_805A0F80->timed = 0;
                }
            }
        }
    }
}

typedef struct DWCLoginInfoEvent {
    s32 result;
    s32 profile;
    u8 unknown08[0x86];
    char lastName[0x100];
} DWCLoginInfoEvent;
typedef char DWCLoginLastNameCheck[offsetof(DWCLoginInfoEvent, lastName) == 0x8E ? 1 : -1];
extern void fn_80351480(void* userData, const void* loginId, s32 profile);
extern void fn_80367E4C(void* connection);
extern s32 fn_80368990(void* connection, char* ticket);

void DWCi_GPGetInfoCallback(void* connection, void* eventPointer, void* parameter) {
    DWCLoginInfoEvent* event = eventPointer;
    char temporaryName[24];
    char pseudoName[24];
    char newName[28];
    s32 result;
    (void)parameter;
    if (event->result != 0) {
        DWC_Printf(0x20, lbl_80489A00 + 0x428, event->result);
        return;
    }
    if (lbl_805A0F80->state == 3) {
        if (event->lastName[0] == 0) {
            DWC_Printf(0x20, lbl_80489A00 + 0x340);
            fn_80350D74((u8*)lbl_805A0F80->userData + 4, lbl_805A0F80->gameCode, newName);
            result = fn_80368058(connection, 0x705, newName);
            if (DWCi_LoginHandleGPError(result) != 0) return;
            lbl_805A0F80->state = 4;
            result = fn_80367F78(connection, event->profile, 0, 0, DWCi_GPGetInfoCallback, NULL);
            if (DWCi_LoginHandleGPError(result) != 0) return;
            DWC_Printf(0x20, lbl_80489A00 + 0x374);
        } else {
            DWC_Printf(0x20, lbl_80489A00 + 0x38C);
            fn_80367E4C(connection);
            DWCi_RemoteLogin();
            lbl_805A0F80->state = 1;
        }
    } else if (lbl_805A0F80->state == 4) {
        fn_80350D74((u8*)lbl_805A0F80->userData + 4, lbl_805A0F80->gameCode, pseudoName);
        if (strcmp(event->lastName, pseudoName) == 0) {
            fn_80350D74(lbl_805A0F80->temporaryLoginId, lbl_805A0F80->gameCode, temporaryName);
            DWC_Printf(0x20, lbl_80489A00 + 0x3C0, temporaryName, pseudoName, event->profile);
            fn_80351480(lbl_805A0F80->userData, lbl_805A0F80->temporaryLoginId, event->profile);
            fn_80367E4C(connection);
            DWC_Printf(0x20, lbl_80489A00 + 0x300);
            lbl_805A0F80->startTime = OSGetTime();
            lbl_805A0F80->timed = 1;
            result = fn_80367D20(lbl_805A0F80->connection, lbl_805A0F80->authToken,
                                lbl_805A0F80->authChallenge, 1, 0, DWCi_GPConnectCallback, NULL);
            if (DWCi_LoginHandleGPError(result) == 0) lbl_805A0F80->state = 2;
        } else {
            DWC_Printf(0x20, lbl_80489A00 + 0x3E8, event->lastName, event->profile);
            result = fn_80367F78(connection, event->profile, 0, 0, DWCi_GPGetInfoCallback, NULL);
            if (DWCi_LoginHandleGPError(result) != 0) return;
        }
    }
}

BOOL DWCi_CheckLogin(void) {
    if (lbl_805A0F80 != NULL && lbl_805A0F80->state == 5) return 1;
    return 0;
}

BOOL DWCi_GetLoginTicket(char* ticket) {
    if (DWCi_CheckLogin()) return fn_80368990(lbl_805A0F80->connection, ticket) == 0;
    return 0;
}
