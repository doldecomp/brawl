#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soAreaContactLog {
public:
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u8 unkc;
    u8 unkd;
    u8 unke;
    u8 unkf;
    struct { u32 unk0, unk4; } unk10;
};
static_assert(sizeof(soAreaContactLog) == 24, "Class is wrong size!");
