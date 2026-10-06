#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class wnPokeTrainerMBall {
public:
class BallInfo {
public:
    struct { u32 unk0, unk4; } unk0;
    u32 unk8;
    struct { u32 unk0, unk4; } unkc;
    u32 unk14;
    struct { u32 unk0, unk4; } unk18;
    u32 unk20;
    struct { u32 unk0, unk4; } unk24;
    u32 unk2c;
    u32 unk30;
    u32 unk34;
    float unk38;
};
};
static_assert(sizeof(wnPokeTrainerMBall::BallInfo) == 60, "Class is wrong size!");
