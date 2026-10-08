#pragma once
#include <ft/fighter.h>
// HYPOTHESIS: grouping follows getExtendParam and rider parameter accesses.
struct ftWarioBikeRiderParam {
    u8 unk0[8];
    float unk8;
    float unkC;
    float unk10;
    float unk14;
    int unk18;
};
// HYPOTHESIS: grouping follows SpecialHiStart/Jump reads of the same record.
struct ftWarioSpecialHiParam {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
    float unk14;
    float unk18;
};
struct ftWarioExtendParam {
    void* unk0;
    ftWarioBikeRiderParam* bikeRider;
    ftWarioSpecialHiParam* specialHi;
};
// Partial fighter declarations: module-builder storage remains unreconstructed.
// Used only for the verified inherited Fighter ABI and getExtendParam calls.
class ftWario : public Fighter {
public:
    ftWarioExtendParam* getExtendParam();
};
class ftWarioMan : public Fighter {
public:
    ftWarioExtendParam* getExtendParam();
};
