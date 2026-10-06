#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soGroundShapeImpl {
public:
    u32 unk0;
    u32 unk4;
    struct { u32 unk0, unk4; } unk8;
    struct { u32 unk0, unk4; } unk10;
    struct { u32 unk0, unk4; } unk18;
    struct { u32 unk0, unk4; } unk20;
    struct { u32 unk0, unk4; } unk28;
    float unk30;
    u8 unk34;
    u16 unk36;
    u32 unk38;
    u32 unk3c;
    virtual ~soGroundShapeImpl();
};
static_assert(sizeof(soGroundShapeImpl) == 68, "Class is wrong size!");
