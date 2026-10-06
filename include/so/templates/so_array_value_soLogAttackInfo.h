#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soLogAttackInfo {
public:
    u32 unk0;
    u32 unk4;
    u32 unk8;
};
static_assert(sizeof(soLogAttackInfo) == 12, "Class is wrong size!");
