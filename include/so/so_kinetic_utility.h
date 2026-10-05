#pragma once

#include <mt/mt_vector.h>
#include <types.h>

class soModuleAccesser;

// Declared from scratch from the asm (parameter meanings are HYPOTHESES).
class soKineticUtility {
public:
    static float brakeSpeedSub(float speed, float accel, float target, float brake);
    static Vec2f brakeSpeed(Vec2f* speed, Vec2f* accel, Vec2f* target, Vec2f* brake);
    static Vec2f limitSpeed(Vec2f* speed, Vec2f* limit);
    static Vec2f projectionNormalFollow(Vec2f* vec, Vec2f* normal);
    static Vec2f projectionGroundSpeed(Vec2f* speed, soModuleAccesser* moduleAccesser);
    // HYPOTHESIS: resets the energy with the given index and enables it.
    static void resetEnableEnergy(int energyIndex, soModuleAccesser* moduleAccesser, int resetMode, Vec2f* speed, Vec3f* rotation);
};
