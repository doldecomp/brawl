#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soDisposeInstanceTerm {
public:
    u32 unk0;
    u32 unk4;
    u8 unk8;
    u8 unk9;
};
static_assert(sizeof(soDisposeInstanceTerm) == 12, "Class is wrong size!");
