#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <mt/mt_vector.h>

// Local copy-layout declaration used only by abstract array instantiations.
// HYPOTHESIS: member grouping follows copies; field meanings remain unknown.
class soAreaInstance {
public:
    u32 unk0, unk4, unk8;
    struct { u32 unk0, unk4; } unkc, unk14;
    u8 unk1c, unk1d;
    virtual ~soAreaInstance();

};
static_assert(sizeof(soAreaInstance) == 36, "Class is wrong size!");
