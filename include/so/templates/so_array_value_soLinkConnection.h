#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soLinkConnection {
public:
    u32 unk0;
    u32 unk4;
    struct { u32 unk0, unk4; } unk8;
    struct { u32 unk0, unk4; } unk10;
    u32 unk18;
    struct { u32 unk0, unk4; } unk1c;
    struct { u32 unk0, unk4; } unk24;
    u32 unk2c;
    u32 unk30;
};
static_assert(sizeof(soLinkConnection) == 52, "Class is wrong size!");
