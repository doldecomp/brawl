#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soShakeTerm {
public:
    u8 unk0;
    u32 unk4;
    u32 unk8;
    u8 unkc;
    u8 unkd;
    struct { u32 unk0, unk4; } unk10;
    virtual ~soShakeTerm();
};
static_assert(sizeof(soShakeTerm) == 28, "Class is wrong size!");
