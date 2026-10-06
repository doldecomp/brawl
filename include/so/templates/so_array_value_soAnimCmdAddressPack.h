#pragma once
#include <StaticAssert.h>
#include <types.h>
// Local copy layout for abstract array instantiations; SDK unchanged.
// HYPOTHESIS: the copied words have unknown meanings.
class soAnimCmdAddressPack {
public:
    u32 unk0, unk4, unk8;
    void operator=(const soAnimCmdAddressPack& other) {
        if (this != &other) {
            // MATCH-ONLY: read all words before writing the destination.
            u32 a, b, c;
            c = other.unk8;
            b = other.unk4;
            a = other.unk0;
            unk0 = a;
            unk4 = b;
            unk8 = c;
        }
    }
};
static_assert(sizeof(soAnimCmdAddressPack) == 12, "Class is wrong size!");
