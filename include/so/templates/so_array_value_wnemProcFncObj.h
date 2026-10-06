#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class wnemProcFncObj {
public:
    u32 unk0;
    u32 unk4;
};
static_assert(sizeof(wnemProcFncObj) == 8, "Class is wrong size!");
