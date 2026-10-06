#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soOtherAnim {
public:
    struct { u32 unk0, unk4; } unk0;
    struct { u32 unk0, unk4; } unk8;
    u32 unk10;
    float unk14;
    float unk18;
    float unk1c;
    float unk20;
    u8 unk24;
    u32 unk28;
};
static_assert(sizeof(soOtherAnim) == 44, "Class is wrong size!");
