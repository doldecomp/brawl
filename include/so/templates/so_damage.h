#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout for abstract array instantiations; the SDK remains unchanged.
// HYPOTHESIS: member grouping follows copies; field meanings remain unknown.
class soDamage {
public:
    float unk0, unk4, unk8, unkc;
    struct { u32 unk0, unk4, unk8; } unk10;
    u32 unk1c;
    struct { u32 unk0, unk4, unk8; } unk20;
    u16 unk2c, unk2e;
    u8 unk30, unk31, unk32, unk33, unk34, unk35, unk36, unk37, unk38, unk39, unk3a;
    u32 unk3c;
    struct { u32 unk0, unk4, unk8; } unk40;
    float unk4c;
    u32 unk50, unk54, unk58, unk5c;
    float unk60, unk64, unk68;
    u32 unk6c, unk70, unk74, unk78;
    float unk7c;
    struct { u32 unk0, unk4, unk8; } unk80;
    struct { u32 unk0, unk4; } unk8c;
    float unk94;
    u32 unk98;
    u8 unk9c;
};
static_assert(sizeof(soDamage) == 160, "Class is wrong size!");
