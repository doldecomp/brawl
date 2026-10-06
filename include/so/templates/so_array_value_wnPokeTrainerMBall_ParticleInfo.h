#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class wnPokeTrainerMBall {
public:
class ParticleInfo {
public:
    struct { u32 unk0, unk4; } unk0;
    u32 unk8;
    struct { u32 unk0, unk4; } unkc;
    u32 unk14;
    struct { u32 unk0, unk4; } unk18;
    u32 unk20;
    float unk24;
    u32 unk28;
    u32 unk2c;
    u32 unk30;
    u32 unk34;
    u32 unk38;
    float unk3c;
};
};
static_assert(sizeof(wnPokeTrainerMBall::ParticleInfo) == 64, "Class is wrong size!");
