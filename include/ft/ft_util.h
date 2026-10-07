#pragma once

#include <types.h>

class soModuleAccesser;

// Helpers shared by every fighter: status-ID classification and the common parameter multipliers.
// Status IDs are the common fighter action IDs (see the BrawlRE "Actions" list).
class ftUtil {
public:
    // Common statuses 0xA4-0xAE: standing, walking, dashing, jumping, falling, firing and landing while shooting an item.
    static bool isItemShootStatus(soModuleAccesser* acc, int status);

    // Common statuses 0xDF-0xE5: the hammer stand/turn/walk/jump/fall/land states.
    static bool isHammerStatus(soModuleAccesser* acc, int status);
    // HYPOTHESIS: motion IDs 0x141-0x143 are the hammer motions; the status and motion ranges are checked separately.
    static bool isHammerMotion(soModuleAccesser* acc, int motion);

    // Common statuses 0x5C-0x5E: falling asleep, sleeping and waking up.
    static bool isSleepStatus(soModuleAccesser* acc, int status);
    // Common status 0x5F: stunned by a Deku Nut.
    static bool isBindStatus(soModuleAccesser* acc, int status);
    // Common statuses 0xC7-0xC8: buried in the ground.
    static bool isBuryStatus(soModuleAccesser* acc, int status);

    // Global multipliers read from the common constants.
    static float getAttackReactionMul(soModuleAccesser* acc);
    static float getAttackPowerMul(soModuleAccesser* acc);
    static float getDamageMul(soModuleAccesser* acc);
};
