#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soControllerClatter {
public:
    float unk0;
    float unk4;
    float unk8;
    u8 unkc;
    u8 unkd;
    u8 unke;
    u8 unkf;
    u8 unk10;
};
static_assert(sizeof(soControllerClatter) == 20, "Class is wrong size!");
