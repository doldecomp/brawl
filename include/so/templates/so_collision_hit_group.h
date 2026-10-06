#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout for abstract array instantiations; the SDK remains unchanged.
// HYPOTHESIS: member grouping follows copies; field meanings remain unknown.
class soCollisionHitGroup {
public:
    u32 unk0;
    s16 unk4, unk6;
    float unk8, unkc;
    u32 unk10;
    float unk14, unk18;
    u32 unk1c, unk20, unk24, unk28, unk2c;
    u8 unk30, unk31, unk32, unk33, unk34;
};
static_assert(sizeof(soCollisionHitGroup) == 56, "Class is wrong size!");
