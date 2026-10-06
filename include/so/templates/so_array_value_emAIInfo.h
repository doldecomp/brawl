#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class emAIInfo {
public:
    u32 unk0;
    u32 unk4;
};
static_assert(sizeof(emAIInfo) == 8, "Class is wrong size!");
