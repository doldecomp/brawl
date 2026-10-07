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

    // Speed multipliers. In adventure mode they are scaled up when this fighter is far from player 1's fighter
    // (see calcAdventureMulValue).
    static float getWalkSpeedMul(soModuleAccesser* acc);
    static float getRunSpeedMul(soModuleAccesser* acc);
    static float getJumpSpeedMul(soModuleAccesser* acc);
    // Scales how far a hit moves a fighter by its weight (heavier fighters are knocked back less).
    static float getWeightReactionMul(soModuleAccesser* acc);

    // Linear ramp from 1.0 to a maximum multiplier as the distance to the player 1 fighter grows between a near and a
    // far threshold (three common constant IDs).
    static float calcAdventureMulValue(soModuleAccesser* acc, u32 nearDistanceId, u32 farDistanceId, u32 maxMulId);

    // Motion played while holding an item: -1 when the held item has no special wait motion. Items held by a
    // grip (only King Dedede keeps one) or by a normal/pickup/plate hold use it, except the motion sensor bomb.
    static int getItemWaitMotion(soModuleAccesser* acc);
    static int getItemSquatWaitMotion(soModuleAccesser* acc);

    // False while the fighter is moving faster than the common speed limit and its "free speed" flag is off.
    static bool isEnableSpeedOperation(soModuleAccesser* acc);

    // Whether a Zako fighter is allowed to enter the status.
    static bool isValidStatusKindZako(soModuleAccesser* acc, int status);

    // Global multipliers read from the common constants.
    static float getAttackReactionMul(soModuleAccesser* acc);
    static float getAttackPowerMul(soModuleAccesser* acc);
    static float getDamageMul(soModuleAccesser* acc);
};
