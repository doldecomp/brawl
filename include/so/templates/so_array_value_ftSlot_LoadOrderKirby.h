#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class ftSlot {
public:
class LoadOrderKirby {
public:
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkc;
};
};
static_assert(sizeof(ftSlot::LoadOrderKirby) == 16, "Class is wrong size!");
