#pragma once
#include <types.h>

// HYPOTHESIS: descriptive parameter names follow their observed Egg Roll uses;
// offsets and scalar types are established by the original loads.
struct ftYoshiSpecialSParam {
    int life;                       // 00
    int cancelDelay;                // 04
    int hitLifeCost;                // 08
    float startSpeed;               // 0C
    float startAirSpeed;            // 10
    float startVerticalSpeed;       // 14
    float unk18;
    float unk1C;
    float flickSpeedMultiplier;     // 20
    float gravity;                  // 24
    float gravityLimit;             // 28
    // HYPOTHESIS: raw kinetic-tuning scalars; Yoshi kinetic mode 0x64 reads
    // these floats at 0x2C, 0x30 and 0x38. Their semantic names are unknown.
    float unk2C;
    float unk30;
    float minimumGroundSpeed;       // 34
    float unk38;
    u8 _3C[8];
    float minimumAirSpeed;          // 44
    float unk48;                    // 48, read by Yoshi custom kinetic mode 0x65
    u8 _4C[4];
    float flickThreshold;           // 50
    float turnStickThreshold;       // 54
    float turnRotation;             // 58
    int dustInterval;               // 5C
    float groundCorrectThreshold;   // 60
    float wallReboundHorizontal;    // 64
    float wallReboundVertical;      // 68
    float landingBounceMultiplier;  // 6C
    float landingBounceThreshold;   // 70
    float unk74;
    float attackPowerBase;          // 78
    float attackPowerMultiplier;    // 7C
    u8 _80[4];
    float hitSpeedDeceleration;     // 84
    float endHorizontalMultiplier;  // 88
    float endVerticalMultiplier;    // 8C
    float rollRotationMultiplier;   // 90
    int attackInterval;             // 94
    float unk98;                    // 98, read by Yoshi custom kinetic mode 0x65
    float turnModelAngle;           // 9C
};
