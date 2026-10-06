#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soEffectContinual {
public:
    u32 unk0;
    u32 unk4;
    float unk8;
    float unkc;
    struct { u32 unk0, unk4; } unk10;
    u32 unk18;
    struct { u32 unk0, unk4; } unk1c;
    u32 unk24;
    u8 unk28;
    u8 unk29;
    u8 unk2a;
};
static_assert(sizeof(soEffectContinual) == 44, "Class is wrong size!");
