#pragma once

#include <StaticAssert.h>
#include <types.h>

// TODO: ntFriendInfoSave?
class UnkFriendInfo {
    struct UnkClass1 {
        u8 unk0;
        u8 unk1;
        u8 unk2[0x2];
    };

    // TODO: First 8 bytes likely hold the 16-digit Wii Number
    struct UnkClass2 {
        u8 unk0;
        u8 unk1;
        u8 unk2;
        u8 unk3;
        u8 unk4;
        u8 unk5;
        u8 unk6;
        u8 unk7;
        u8 unk8[0x81];
    };
public:
    static const u32 FriendRosterLimit = 64;

    u8 unk0[0x350];
    UnkClass1 unk350[FriendRosterLimit];
    u8 unk450[0x163];
    UnkClass2 unk5B3[FriendRosterLimit];
};
// TODO size assertion

class ntFriendInfo {

public:
    UnkFriendInfo* getFriendInfo();
    static ntFriendInfo* getInstance();
};
// TODO size assertion

class NtOffline {
public:
    NtOffline();
    virtual ~NtOffline();
    u32 getFriendIndexHaveWiiID(u64 id);

    u32 unk4;
};
// TODO size assertion
