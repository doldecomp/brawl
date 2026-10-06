#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soAreaWind {
public:
    u32 unk0;
};
static_assert(sizeof(soAreaWind) == 4, "Class is wrong size!");
