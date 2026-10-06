#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soCollisionAttackAbsolute {
public:
    u32 unk0;
    struct { u32 unk0, unk4; } unk4;
    u32 unkc;
    float unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 unk20;
    float unk24;
    float unk28;
    float unk2c;
    u32 unk30;
    u32 unk34;
    u32 unk38;
    u32 unk3c;
    u32 unk40;
    struct { u32 unk0, unk4; } unk44;
    u32 unk4c;
    struct { u32 unk0, unk4; } unk50;
    u32 unk58;
    u16 unk5c;
    u8 unk5e;
    u8 unk5f;
    u32 unk60;
    u8 unk64;
};
static_assert(sizeof(soCollisionAttackAbsolute) == 104, "Class is wrong size!");
