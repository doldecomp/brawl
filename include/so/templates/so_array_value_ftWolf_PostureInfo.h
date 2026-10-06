#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class ftWolf {
public:
class PostureInfo {
public:
    struct { u32 unk0, unk4; } unk0;
    u32 unk8;
    float unkc;
};
};
static_assert(sizeof(ftWolf::PostureInfo) == 16, "Class is wrong size!");
