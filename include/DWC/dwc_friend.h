#pragma once
#include <types.h>

typedef struct DWCFriendRecord { u32 words[3]; } DWCFriendRecord;

u8 DWC_GetFriendStatusSC(const DWCFriendRecord* friendData, u8* maxPlayers, u8* players, char* location);
u8 DWC_GetFriendStatusData(const DWCFriendRecord* friendData, void* data, s32* size);
s32 DWC_GetNumFriend(const DWCFriendRecord* friends, s32 count);
BOOL DWC_SetOwnStatusData(const void* data, u32 size);
BOOL DWC_CanChangeFriendList(void);
void DWC_DeleteBuddyFriendData(DWCFriendRecord* friendData);

typedef void (*DWCBuddyFriendCallback)(s32 index, void* parameter);
BOOL DWC_SetBuddyFriendCallback(DWCBuddyFriendCallback callback, void* parameter);
