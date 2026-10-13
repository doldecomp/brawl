#pragma once

#include <revolution/DVD/dvd.h>
#include <types.h>

// TODO: THPPlayer? Likely has more members
struct UnkTHPClass {
    struct UnkClass {
        u32 length;
        s8 buf[0x10];
    };
    DVDFileInfo m_fInfo;
    char unk3C[4];
    u32 unk40;
    u32 unk44;
    u32 unk48;
    float unk4C;
    u32 unk50;
    u32 unk54;
    u32 unk58;
    u32 unk5C;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    UnkClass unk6C;
    u8 unk80[0x26];
    u8 unkA6;
    u8 unkA7[0x1];
    s32 unkA8; // read error indicator
    u8 unkAC[0x8];
    u32* unkB4;
    u32 unkB8; // initial read offset
    u32 unkBC; // initial read size
    u32 unkC0;
    u8 unkC4[0x18];
    u32 unkDC;
};
// TODO: size assertion

void PrepareReady(bool p1);

extern UnkTHPClass g_thpObject;
