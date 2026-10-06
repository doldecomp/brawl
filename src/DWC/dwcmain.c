#include <types.h>
#include <stddef.h>
#include <string.h>

typedef void (*DWCMainCallback)(void);
typedef struct DWCMainMatchView {
    u8 unknown00[0x10];
    void* qr2;
    u8 unknown14;
    u8 phase;
    u8 unknown16[0x16];
    u8 unknown2C;
    u8 unknown2D[0xCB];
    void* serverBrowser;
    u8 unknownFC[0x464];
} DWCMainMatchView;
typedef struct DWCMainControlView {
    void* socket;
    DWCMainCallback gt2Callbacks[4];
    s32 sendBufferSize;
    s32 receiveBufferSize;
    void* connection;
    void* userData;
    s32 phase;
    s32 previousPhase;
    u8 unknown2C;
    u8 unknown2D;
    char playerName[0x36];
    u32 unknown64;
    void* gameName;
    char* secretKey;
    u32 unknown70[10];
    u8 login[0x268];
    u8 friendControl[0x60];
    DWCMainMatchView match;
    u8 transport[0x918];
    u8 unknown11D8;
    u8 unknown11D9[7];
} DWCMainControlView;
#ifdef __MWERKS__
typedef char DWCMainSizeCheck[sizeof(DWCMainControlView) == 0x11E0 ? 1 : -1];
typedef char DWCMainLoginCheck[offsetof(DWCMainControlView, login) == 0x98 ? 1 : -1];
typedef char DWCMainFriendCheck[offsetof(DWCMainControlView, friendControl) == 0x300 ? 1 : -1];
typedef char DWCMainMatchCheck[offsetof(DWCMainControlView, match) == 0x360 ? 1 : -1];
typedef char DWCMainTransportCheck[offsetof(DWCMainControlView, transport) == 0x8C0 ? 1 : -1];
typedef char DWCMainQR2Check[offsetof(DWCMainMatchView, qr2) == 0x10 ? 1 : -1];
typedef char DWCMainBrowserCheck[offsetof(DWCMainMatchView, serverBrowser) == 0xF8 ? 1 : -1];
#endif
extern DWCMainControlView* lbl_805A0F88;
extern const char lbl_80489E48[];
extern u8 lbl_80533730[0x80];
extern u8 lbl_805337B0[0x100];
extern u8 lbl_80535BE0[];
extern char lbl_80535CE0[0x100];
extern void DWC_Printf(u32 level, const char* format, ...);
extern void* DWC_Alloc(int kind, u32 size);
extern void DWC_ClearError(void);
extern void fn_80340A48(void);
extern void fn_8033BA3C(void);
extern void fn_8033BA40(void);
extern void fn_8033C018(void);
extern void fn_8033B134(s32 error, s32 profile, void* parameter);
extern void DWCi_LoginInit(void* control, void* userData, void* connection, u32 product,
                           u32 gameCode, char* playerName,
                           void (*callback)(s32, s32, void*), void* parameter);
extern void DWCi_FriendInit(void* control, void* connection, void* playerName,
                            void* friends, s32 count);
extern void fn_8033CBEC(void* control, void* connection, void* mainControl,
                      DWCMainCallback* callbacks, void* gameName, void* secretKey,
                      void* friends, s32 count);
extern void fn_8034E59C(void* transport);
extern void fn_8034F028(void* destination, const void* source, u32 size);

void DWC_InitFriendsMatch(u32 unused0, void* userData, u32 product, u32 unused3,
                          const char* secretKey, s32 sendBufferSize, s32 receiveBufferSize,
                          void* friends, s32 count) {
    u32 length;
    (void)unused0;
    (void)unused3;
    DWC_Printf(4, lbl_80489E48);
    lbl_805A0F88 = DWC_Alloc(4, 0x11E0);
    memset(lbl_805A0F88, 0, 0x11E0);
    DWC_ClearError();
    lbl_805A0F88->socket = NULL;
    lbl_805A0F88->gt2Callbacks[0] = fn_80340A48;
    lbl_805A0F88->gt2Callbacks[1] = fn_8033BA3C;
    lbl_805A0F88->gt2Callbacks[2] = fn_8033BA40;
    lbl_805A0F88->gt2Callbacks[3] = fn_8033C018;
    lbl_805A0F88->sendBufferSize = sendBufferSize != 0 ? sendBufferSize : 0x2000;
    lbl_805A0F88->receiveBufferSize = receiveBufferSize != 0 ? receiveBufferSize : 0x2000;
    lbl_805A0F88->connection = NULL;
    lbl_805A0F88->userData = userData;
    lbl_805A0F88->phase = 0;
    lbl_805A0F88->previousPhase = 0;
    lbl_805A0F88->unknown2C = 0;
    lbl_805A0F88->unknown2D = 0;
    lbl_805A0F88->unknown11D8 = 0;
    lbl_805A0F88->unknown64 = 0;
    lbl_805A0F88->gameName = lbl_80535BE0;
    lbl_805A0F88->secretKey = lbl_80535CE0;
    lbl_805A0F88->unknown70[0] = 0;
    lbl_805A0F88->unknown70[1] = 0;
    lbl_805A0F88->unknown70[2] = 0;
    lbl_805A0F88->unknown70[3] = 0;
    lbl_805A0F88->unknown70[4] = 0;
    lbl_805A0F88->unknown70[5] = 0;
    lbl_805A0F88->unknown70[6] = 0;
    lbl_805A0F88->unknown70[7] = 0;
    lbl_805A0F88->unknown70[8] = 0;
    lbl_805A0F88->unknown70[9] = 0;
    memset(lbl_80533730, 0, 0x80);
    memset(lbl_805337B0, 0, 0x100);
    DWCi_LoginInit(lbl_805A0F88->login, userData, &lbl_805A0F88->connection, product,
                   *(u32*)((u8*)userData + 0x24), lbl_805A0F88->playerName, fn_8033B134, NULL);
    DWCi_FriendInit(lbl_805A0F88->friendControl, &lbl_805A0F88->connection,
                    lbl_805A0F88->playerName, friends, count);
    fn_8033CBEC(&lbl_805A0F88->match, &lbl_805A0F88->connection, lbl_805A0F88,
                lbl_805A0F88->gt2Callbacks, lbl_80535BE0, lbl_80535CE0, friends, count);
    fn_8034E59C(lbl_805A0F88->transport);
    length = strlen(secretKey);
    if (length < 0x100) length = strlen(secretKey);
    else length = 0xFF;
    fn_8034F028(lbl_80535CE0, secretKey, length);
    lbl_80535CE0[length] = 0;
}

extern const char lbl_80489E70[];
extern void fn_803791BC(void* qr2);
extern void fn_803895D0(void* browser);
extern void fn_8033C0D4(void);
extern void fn_80383470(void);
extern s32 fn_80367CB0(void* connection, s32 event, void (*callback)(void*, void*, void*), void* parameter);
extern s32 fn_80367C74(void* connection);
extern void fn_80367C54(void* connection);
extern void DWCi_ShutdownLogin(void);
extern void DWCi_ShutdownFriend(void);
extern void fn_803424AC(void);
extern void fn_8034EB74(void);
extern void fn_80374880(void* socket);
extern void DWC_Free(int kind, void* allocation, int size);

void DWC_ShutdownFriendsMatch(void) {
    DWC_Printf(4, lbl_80489E70, lbl_805A0F88);
    if (lbl_805A0F88 == NULL) return;
    if (lbl_805A0F88->match.qr2 != NULL) {
        fn_803791BC(lbl_805A0F88->match.qr2);
        lbl_805A0F88->match.qr2 = NULL;
    }
    lbl_805A0F88->match.unknown2C = 0;
    if (lbl_805A0F88->match.serverBrowser != NULL) {
        fn_803895D0(lbl_805A0F88->match.serverBrowser);
        lbl_805A0F88->match.serverBrowser = NULL;
    }
    fn_8033C0D4();
    fn_80383470();
    if (lbl_805A0F88->connection != NULL) {
        fn_80367CB0(&lbl_805A0F88->connection, 0, NULL, NULL);
        fn_80367CB0(&lbl_805A0F88->connection, 3, NULL, NULL);
        fn_80367CB0(&lbl_805A0F88->connection, 1, NULL, NULL);
        fn_80367CB0(&lbl_805A0F88->connection, 2, NULL, NULL);
        fn_80367C74(&lbl_805A0F88->connection);
        fn_80367C54(&lbl_805A0F88->connection);
        lbl_805A0F88->connection = NULL;
    }
    DWCi_ShutdownLogin();
    DWCi_ShutdownFriend();
    fn_803424AC();
    fn_8034EB74();
    if (lbl_805A0F88->socket != NULL) {
        fn_80374880(lbl_805A0F88->socket);
        lbl_805A0F88->socket = NULL;
    }
    DWC_Free(4, lbl_805A0F88, 0);
    lbl_805A0F88 = NULL;
}

extern BOOL DWCi_IsError(void);
extern void DWCi_LoginProcess(void);
extern void DWCi_FriendProcess(void);
extern void fn_8033DD60(BOOL active);
extern void fn_8034E790(void);
extern s32 fn_8035E1A8(void);
extern void DWCi_StopLogin(s32 error, s32 code);
extern s32 fn_80367C28(void* connection, u32 product, u32 nameSpace, u32 partner);
extern s32 fn_8033AEEC(s32 result);
extern BOOL DWCi_LoginAsync(void);
extern const char lbl_80489EAC[];
extern void fn_8033B45C(void*, void*, void*);
extern void fn_8033B8CC(void*, void*, void*);
extern void DWCi_GPRecvBuddyAuthCallback(void*, void*, void*);
extern void DWCi_GPRecvBuddyRequestCallback(void*, void*, void*);
extern void DWCi_GPRecvBuddyStatusCallback(void*, void*, void*);

void DWC_ProcessFriendsMatch(void) {
    s32 result;
    if (lbl_805A0F88 == NULL || lbl_805A0F88->phase == 0 || DWCi_IsError()) return;
    switch (lbl_805A0F88->phase) {
    case 1:
        result = fn_8035E1A8();
        switch (result) {
        case 1:
            DWC_Printf(0x10, lbl_80489EAC);
            result = fn_80367C28(&lbl_805A0F88->connection, *(u32*)(lbl_805A0F88->login + 8), 0x10, 0xB);
            if (fn_8033AEEC(result) != 0) return;
            result = fn_80367CB0(&lbl_805A0F88->connection, 0, fn_8033B45C, NULL);
            if (fn_8033AEEC(result) != 0) return;
            result = fn_80367CB0(&lbl_805A0F88->connection, 3, fn_8033B8CC, NULL);
            if (fn_8033AEEC(result) != 0) return;
            result = fn_80367CB0(&lbl_805A0F88->connection, 7, DWCi_GPRecvBuddyAuthCallback, NULL);
            if (fn_8033AEEC(result) != 0) return;
            result = fn_80367CB0(&lbl_805A0F88->connection, 1, DWCi_GPRecvBuddyRequestCallback, NULL);
            if (fn_8033AEEC(result) != 0) return;
            result = fn_80367CB0(&lbl_805A0F88->connection, 2, DWCi_GPRecvBuddyStatusCallback, NULL);
            if (fn_8033AEEC(result) != 0) return;
            lbl_805A0F88->previousPhase = lbl_805A0F88->phase;
            lbl_805A0F88->phase = 2;
            if (!DWCi_LoginAsync()) DWCi_StopLogin(2, -20100);
            break;
        case 2:
            DWCi_StopLogin(3, -20110);
            return;
        case 3:
            DWCi_StopLogin(4, -20101);
            return;
        }
        break;
    case 2:
        DWCi_LoginProcess();
        break;
    case 3:
    case 4:
        DWCi_FriendProcess();
        fn_8033DD60(0);
        break;
    case 5:
        fn_8033DD60(1);
        DWCi_FriendProcess();
        break;
    case 6:
        fn_8034E790();
        DWCi_FriendProcess();
        if (lbl_805A0F88->match.phase == 2 || lbl_805A0F88->match.phase == 3) fn_8033DD60(1);
        else if (lbl_805A0F88->socket != NULL) fn_8033DD60(0);
        break;
    }
    if (lbl_805A0F88->match.unknown2C == 1) {
        if (lbl_805A0F88->match.qr2 != NULL) {
            fn_803791BC(lbl_805A0F88->match.qr2);
            lbl_805A0F88->match.qr2 = NULL;
        }
        lbl_805A0F88->match.unknown2C = 0;
    }
}
