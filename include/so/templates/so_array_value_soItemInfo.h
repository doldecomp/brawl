#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soItemInfo {
public:
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkc;
    u8 unk10;
};
static_assert(sizeof(soItemInfo) == 20, "Class is wrong size!");
