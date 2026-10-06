#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <mt/mt_vector.h>

// Local copy-layout declaration used only by abstract array instantiations.
// HYPOTHESIS: member grouping follows copies; field meanings remain unknown.
class soCameraSubject {
public:
    u8 unk0;
    u32 unk4, unk8, unkc, unk10;
    struct { u32 unk0, unk4; } unk14, unk1c;
    u32 unk24;
    struct { u32 unk0, unk4; } unk28;
    u32 unk30;
    float unk34;
    u32 unk38;
    u8 unk3c;
    virtual ~soCameraSubject();

};
static_assert(sizeof(soCameraSubject) == 68, "Class is wrong size!");
