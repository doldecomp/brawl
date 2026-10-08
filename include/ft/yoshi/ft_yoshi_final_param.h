#pragma once
#include <types.h>

// HYPOTHESIS: the fourth Yoshi extension parameter is the Super Dragon tuning
// record. Raw float offsets are established by FinalCommon/FinalStart loads;
// meanings remain unknown until each use has stronger external documentation.
struct ftYoshiFinalParam {
    float unk00;
    float unk04;
    float unk08;
    float unk0C;
    float unk10;
    float unk14;
    float unk18;
    float unk1C;
    float unk20;
    float unk24;
    float unk28;
    u8 _2C[0x30];
    float unk5C;
    float unk60;
};
static_assert(sizeof(ftYoshiFinalParam) == 0x64, "ftYoshiFinalParam layout mismatch");