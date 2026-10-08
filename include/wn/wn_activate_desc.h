#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <stddef.h>
#include <types.h>

// HYPOTHESIS: original descriptor type spelling. Physical layout follows both
// Sonic activation callers and the complete Weapon::activate consumer.
struct wnActivateDesc {
    int founderTaskId;
    int resourceId, unk8, unkC;
    int unk10, unk14, unk18, unk1C;
    Vec3f pos;
    float lr;
    int team, life;
    int unk38, unk3C, unk40, unk44, unk48;
    // The two flag bytes are also written field-wise by some activators (HYPOTHESIS: the bit grouping follows the
    // native masks used by the Robo Beam).
    union {
        u8 flags;
        struct {
            u8 flagsHigh : 1;
            u8 flagsMidHigh : 3;
            u8 flagsMidLow : 1;
            u8 flagsLow : 3;
        };
    };
    union {
        u8 unk4D;
        struct {
            u8 unk4DHigh : 2;
            u8 unk4DLow : 6;
        };
    };
    u8 unk4E[2];
};
static_assert(sizeof(wnActivateDesc) == 0x50, "Weapon activation descriptor size");
static_assert(offsetof(wnActivateDesc, pos) == 0x20, "Activation position offset");
static_assert(offsetof(wnActivateDesc, lr) == 0x2C, "Activation facing offset");
static_assert(offsetof(wnActivateDesc, team) == 0x30, "Activation team offset");
static_assert(offsetof(wnActivateDesc, flags) == 0x4C, "Activation flags offset");
static_assert(offsetof(wnActivateDesc, unk4D) == 0x4D, "Activation second flags offset");
