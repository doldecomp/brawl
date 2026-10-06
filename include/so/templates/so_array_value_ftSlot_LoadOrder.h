#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class ftSlot {
public:
class LoadOrder {
public:
    u8 unk0;
    u32 unk4;
};
};
static_assert(sizeof(ftSlot::LoadOrder) == 8, "Class is wrong size!");
