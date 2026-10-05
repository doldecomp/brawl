#include <ft/fighter.h>
#include <ft/ft_kinetic_energy.h>
#include <ft/ft_status_uniq_process_glide.h>
#include <nw4r/math/math_arithmetic.h>
#include <so/so_kinetic_utility.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

// MATCH-ONLY: the RTTI of ftKineticEnergyStop lives in another TU; calling the runtime directly avoids
// emitting a duplicate weak copy of the whole RTTI chain here.
extern "C" {
extern char __RTTI__19ftKineticEnergyStop[];
extern char __RTTI__15soKineticEnergy[];
void* __dynamic_cast(void* ptr, long vtblOffset, const void* target, const void* source, int isRef);
}

// Clears and disables the kinetic energy with the given index (sora_melee helper).
void ftKineticEnergyDisableAndClear(int index, soModuleAccesser* moduleAccesser);

// HYPOTHESIS: ftUtil is a class/namespace of fighter helpers. Returns the mask of touched surfaces of the
// fighter (bit 0 = ?, bit 1/2 = side walls?, bit 3 = ?) and writes position/normal of the touch per surface.
class ftUtil {
public:
    static u32 getAirGroundTouchInfo(soModuleAccesser* moduleAccesser, Vec2f* pos, Vec2f* normal);
};

// HYPOTHESIS: reset type used by the fighters to restart an energy from a given speed without its own state.
static const int ENERGY_RESET_GLIDE = 0x16;

// Work variables of the glide status (ids taken from the asm; names from the Ultimate port of the glide).
enum {
    Glide_Float_Angle = 0x21000004,      // current glide angle in degrees, positive = nose up
    Glide_Float_Power = 0x21000005,      // glide power (speed along the glide direction)
    Glide_Float_Gravity = 0x21000006,    // downward pull accumulated while gliding
    Glide_Float_AngleSpeed = 0x21000007, // how fast the angle is changing (stick steering)
    Glide_Flag_Stall = 0x22000010,       // HYPOTHESIS: out of power, the fighter falls with air physics
    Glide_Flag_RapidFall = 0x22000012,   // set while diving with the extra speed gain disabled
    Glide_Flag_Touch = 0x22000013,       // set by execFixPos while touching a wall/ceiling/floor surface
};

// HYPOTHESIS: the original uses its own inline length helper (float FLT_MIN compare and inline fabs)
// instead of Vec2f::length from the shared header (same helper as in ftStatusUniqProcessDamageFly).
static inline float calcLength(float lengthSq) {
    float length;
    if ((float)__fabs(lengthSq) <= 1.17549435e-38f) {
        length = 0.0f;
    } else {
        length = rsqrtf(lengthSq) * lengthSq;
    }
    return length;
}

static inline float calcLength(const Vec2f& v) {
    return calcLength(v.m_x * v.m_x + v.m_y * v.m_y);
}

// HYPOTHESIS: inline clamp helper (fsel based).
static inline float clampf(float value, float lo, float hi) {
    value = nw4r::math::FSelect(value - lo, value, lo);
    return nw4r::math::FSelect(value - hi, hi, value);
}

ftStatusUniqProcessGlide g_ftStatusUniqProcessGlide;

// HYPOTHESIS: glide start. Seeds the glide power / gravity work variables, restarts the STOP energy with the
// glide speed along the facing direction, clears the other fighter energies and starts the glide motions.
void ftStatusUniqProcessGlide::initStatus(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getStatusModule().getStatusKind() == Fighter::Status::Glide) {
        ftGlideParam* param = (ftGlideParam*)soValueAccesser::getConstantIndefinite(moduleAccesser, 0xa80b, 0);
        float lr = moduleAccesser->getPostureModule().getLr();
        soKineticEnergy::AttributeFlag flag(1);
        Vec2f sumSpeed;
        Vec2f::copy(sumSpeed, moduleAccesser->getKineticModule().getSumSpeed(flag));
        moduleAccesser->getWorkManageModule().setFloat(param->m_baseSpeed, Glide_Float_Power);
        moduleAccesser->getWorkManageModule().setFloat(-sumSpeed.m_y, Glide_Float_Gravity);
        Vec3f rotation(0.0f, 0.0f, 0.0f);
        soKineticUtility::resetEnableEnergy(3, moduleAccesser, ENERGY_RESET_GLIDE,
                                            &Vec2f(param->m_baseSpeed * lr, 0.0f), &rotation);
        ftKineticEnergyDisableAndClear(2, moduleAccesser);
        ftKineticEnergyDisableAndClear(0, moduleAccesser);
        ftKineticEnergyDisableAndClear(1, moduleAccesser);
        soMotionChangeParam motion;
        motion.m_kind = Fighter::Motion::Glide_Direction;
        motion.m_frame = 90.0f;
        motion.m_rate = 0.0f;
        motion._12 = 0;
        motion._13 = 0;
        motion._14 = 0;
        motion._15 = 0;
        moduleAccesser->getMotionModule().changeMotionRequest(&motion);
        // MATCH-ONLY: the local steers the load scheduling of the call arguments (2 instructions still differ).
        float rate = 1.0f;
        moduleAccesser->getMotionModule().addPartialAnimChr(0.0f, rate, 1, Fighter::Motion::Glide_Wing,
                                                            param->m_wingBlend, 0, 0);
    }
}

// HYPOTHESIS: per-frame glide. The stick changes the angle speed (pull up / push down), the angle is clamped
// and drives the glide animation frame; power is lost when climbing and gained when diving; the velocity is
// power along the angle minus an accumulating gravity pull. When power runs out the glide stalls and the STOP
// energy falls with the normal air physics until the fighter points down fast enough again.
void ftStatusUniqProcessGlide::execStatus(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getStatusModule().getStatusKind() == Fighter::Status::Glide) {
        float lr = moduleAccesser->getPostureModule().getLr();
        ftGlideParam* param = (ftGlideParam*)soValueAccesser::getConstantIndefinite(moduleAccesser, 0xa80b, 0);
        ftKineticEnergyStop* energy = (ftKineticEnergyStop*)__dynamic_cast(
            moduleAccesser->getKineticModule().getEnergy(3), 0, __RTTI__19ftKineticEnergyStop,
            __RTTI__15soKineticEnergy, 1);
        float angle = moduleAccesser->getWorkManageModule().getFloat(Glide_Float_Angle);
        float angleSpeed = moduleAccesser->getWorkManageModule().getFloat(Glide_Float_AngleSpeed);
        // stick direction in degrees, mirrored so that "forward" is the same for both facing directions
        float stickAngle = moduleAccesser->getControllerModule().getStickAngle();
        if (lr > 0.0f) {
            stickAngle = 57.29578f * stickAngle;
        } else {
            float deg = stickAngle * 57.29578f;
            float sign = (deg > 0.0f) ? 1.0f : -1.0f;
            stickAngle = 180.0f * sign - deg;
        }
        float stickX = moduleAccesser->getControllerModule().getStickX();
        float stickY = moduleAccesser->getControllerModule().getStickY();
        float stickLen = calcLength(Vec2f(stickX, stickY));
        if (stickLen > param->m_radialStick) {
            float accel;
            if (stickAngle >= 0.0f) {
                if (stickAngle < 45.0f) {
                    accel = -param->m_downAngleAccel;
                } else {
                    accel = param->m_upAngleAccel;
                }
            } else if (stickAngle < -135.0f) {
                accel = param->m_upAngleAccel;
            } else {
                accel = -param->m_downAngleAccel;
            }
            accel = accel * ((stickLen - param->m_radialStick) / (1.0f - param->m_radialStick));
            if (angleSpeed * accel < 0.0f) {
                angleSpeed = 0.0f;
            }
            angleSpeed += accel;
            angleSpeed = clampf(angleSpeed, -param->m_maxAngleSpeed, param->m_maxAngleSpeed);
            moduleAccesser->getWorkManageModule().setFloat(angleSpeed, Glide_Float_AngleSpeed);
            angle += angleSpeed;
        } else if (moduleAccesser->getWorkManageModule().isFlag(Glide_Flag_Stall) == true) {
            // stick (almost) centered while stalled
            if (angleSpeed < 0.0f) {
                angleSpeed = 0.0f;
            }
            angleSpeed += param->m_stallAngleAccel;
            angleSpeed = clampf(angleSpeed, -param->m_maxAngleSpeed, param->m_maxAngleSpeed);
            moduleAccesser->getWorkManageModule().setFloat(angleSpeed, Glide_Float_AngleSpeed);
            angle += angleSpeed;
        }
        angle = clampf(angle, param->m_angleMin, param->m_angleMax);
        // MATCH-ONLY: unused, but the original has -90.0f in its constant pool at this spot.
        float unusedMin = -90.0f;
        if (moduleAccesser->getWorkManageModule().isFlag(Glide_Flag_Stall) == false) {
            float power = moduleAccesser->getWorkManageModule().getFloat(Glide_Float_Power)
                          - param->m_speedChange * (angle / 90.0f);
            if (moduleAccesser->getWorkManageModule().isFlag(Glide_Flag_Touch) == true) {
                power -= 0.01f;
            }
            if (power < 0.0f) {
                power = 0.0f;
            }
            if (moduleAccesser->getWorkManageModule().isFlag(Glide_Flag_RapidFall)) {
                if (angle > 0.0f) {
                    moduleAccesser->getWorkManageModule().offFlag(Glide_Flag_RapidFall);
                }
            } else if (angle < param->m_angleMoreSpeed) {
                power += param->m_downSpeedAdd
                         * ((param->m_angleMoreSpeed - angle) / (param->m_angleMoreSpeed - param->m_angleMin));
            }
            Vec2f velocity;
            Vec2f forward(power * moduleAccesser->getPostureModule().getLr(), 0.0f);
            forward.rot(&velocity, 0.017453292f * (angle * moduleAccesser->getPostureModule().getLr()));
            float gravity = moduleAccesser->getWorkManageModule().getFloat(Glide_Float_Gravity);
            gravity = gravity + param->m_gravityAccel;
            gravity = clampf(gravity, -param->m_gravitySpeed, param->m_gravitySpeed);
            moduleAccesser->getWorkManageModule().setFloat(gravity, Glide_Float_Gravity);
            velocity.m_y -= gravity;
            float speedLen = calcLength(velocity);
            if (speedLen > param->m_maxSpeed) {
                velocity = velocity * (param->m_maxSpeed / speedLen);
            }
            if (speedLen < param->m_minSpeed || power <= 0.0f) {
                moduleAccesser->getWorkManageModule().onFlag(Glide_Flag_Stall);
                moduleAccesser->getWorkManageModule().setFloat(0.0f, Glide_Float_AngleSpeed);
            }
            energy->m_speed.m_x = velocity.m_x;
            energy->m_speed.m_y = velocity.m_y;
            moduleAccesser->getWorkManageModule().setFloat(power, Glide_Float_Power);
        } else {
            // stalled: fall with the common air physics (the constants are the fighter's air parameters)
            Vec2f target(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0), -1.0f);
            float airSpeedYStable = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd0, 0);
            Vec2f limit(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd8, 0), airSpeedYStable);
            Vec2f accel(0.0f, -soValueAccesser::getConstantFloat(moduleAccesser, 0xbcf, 0));
            Vec2f brake(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd6, 0), 0.0f);
            Vec2f delta;
            Vec2f::copy(delta, soKineticUtility::brakeSpeed(&energy->getSpeed(), &accel, &target, &brake));
            Vec2f limited;
            Vec2f::copy(limited, soKineticUtility::limitSpeed(&(energy->getSpeed() + delta), &limit));
            energy->m_speed = limited;
            if (angle < param->m_stallRecoverAngle) {
                float currentLen = calcLength(energy->getSpeed());
                if (currentLen > param->m_minSpeed) {
                    moduleAccesser->getWorkManageModule().setFloat(currentLen, Glide_Float_Power);
                    moduleAccesser->getWorkManageModule().offFlag(Glide_Flag_Stall);
                }
            }
        }
        moduleAccesser->getMotionModule().setFrame(90.0f - angle);
        moduleAccesser->getWorkManageModule().setFloat(angle, Glide_Float_Angle);
    }
}

// HYPOTHESIS: remembers whether the fighter is touching a surface (used by execStatus to bleed off power).
void ftStatusUniqProcessGlide::execFixPos(soModuleAccesser* moduleAccesser) {
    Vec2f pos;
    Vec2f normal;
    u32 touch = ftUtil::getAirGroundTouchInfo(moduleAccesser, &pos, &normal);
    if ((touch & 6) != 0) {
        moduleAccesser->getWorkManageModule().onFlag(Glide_Flag_Touch);
    } else {
        moduleAccesser->getWorkManageModule().offFlag(Glide_Flag_Touch);
    }
}

// HYPOTHESIS: drops the wing partial animation started by initStatus.
void ftStatusUniqProcessGlide::exitStatus(soModuleAccesser* moduleAccesser, int) {
    moduleAccesser->getMotionModule().removePartialAnimChr(1);
}
