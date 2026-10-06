#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout for abstract array instantiations; the SDK remains unchanged.
// HYPOTHESIS: field grouping follows copies; meanings remain unknown.
class soCollisionGroup {
public:
    struct { u32 unk0, unk4; } unk0;
    u32 unk8;
    struct { u32 unk0, unk4, unk8; } unkc;
    u32 unk18;
    struct { u32 unk0, unk4, unk8; } unk1c, unk28;
    u32 unk34, unk38, unk3c;
    struct { u32 unk0, unk4, unk8; } unk40;
    float unk4c, unk50, unk54;
    struct { u32 unk0, unk4; } unk58, unk60, unk68;
    s16 unk70;
    u8 unk72, unk73, unk74;
};
static_assert(sizeof(soCollisionGroup) == 120, "Class is wrong size!");
