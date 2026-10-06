#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soPartialAnim {
public:
    u32 unk0;
    float unk4;
    float unk8;
    float unkc;
    float unk10;
    float unk14;
    u8 unk18;
    u32 unk1c;
    u32 unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    float unk34;
    u8 unk38;
    u32 unk3c;
    u32 unk40;
    u8 unk44;
};
static_assert(sizeof(soPartialAnim) == 72, "Class is wrong size!");
