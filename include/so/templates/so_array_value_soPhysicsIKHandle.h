#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soPhysicsIKHandle {
public:
    u32 unk0;
    struct { u32 unk0, unk4; } unk4;
    u32 unkc;
    struct { u32 unk0, unk4; } unk10;
    u32 unk18;
    struct { u32 unk0, unk4; } unk1c;
    u32 unk24;
    struct { u32 unk0, unk4; } unk28;
    u32 unk30;
    float unk34;
};
static_assert(sizeof(soPhysicsIKHandle) == 56, "Class is wrong size!");
