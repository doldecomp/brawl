#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <mt/mt_vector.h>

// Local copy-layout declaration used only by abstract array instantiations.
// HYPOTHESIS: member grouping follows copies; field meanings remain unknown.
class soModelNodeSetUp {
public:
    u32 unk0;
    struct { u32 unk0, unk4, unk8; } unk4, unk10, unk1c;
    u32 unk28;
    struct { u32 unk0, unk4; } unk2c;
};
static_assert(sizeof(soModelNodeSetUp) == 52, "Class is wrong size!");
