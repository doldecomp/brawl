#pragma once

#include <StaticAssert.h>
#include <types.h>

struct adventureStaticData {
    u32 unk0;
    u8 unk4;

    static const u32 AllStepNum = 0x101;
    static adventureStaticData s_adventureStaticData[AllStepNum];
public:
    static s32 getStepIndex(u32 p1);
    static u32 getAllStepNum();
};
static_assert(sizeof(adventureStaticData) == 8, "Class is the wrong size!");
