#pragma once
#include <StaticAssert.h>
#include <types.h>
// Local copy layout for abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field meanings remain unknown; the copied layout is verified.
class soMotionChangeParam {
public:
    u32 unk0;
    float unk4, unk8;
    u8 unkc, unkd, unke, unkf;
    void operator=(const soMotionChangeParam& other) {
        if (this != &other) {
            unk0 = other.unk0;
            unk4 = other.unk4;
            unk8 = other.unk8;
            unkc = other.unkc;
            unkd = other.unkd;
            unke = other.unke;
            unkf = other.unkf;
        }
    }
};
static_assert(sizeof(soMotionChangeParam) == 16, "Class is wrong size!");
