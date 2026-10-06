#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class acCmdInterpreterStackData {
public:
    u32 unk0;
    u32 unk4;
    u8 unk8;
    u32 unkc;
    float unk10;
};
static_assert(sizeof(acCmdInterpreterStackData) == 20, "Class is wrong size!");
