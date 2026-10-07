#include <ft/marth/ft_marth_status_uniq_process.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

void ftKineticEnergyDisableAndClear(int index, soModuleAccesser* moduleAccesser);

void ftMarthStatusUniqProcessSpecialHi::initStatus(soModuleAccesser* moduleAccesser) {
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
    Vec2f sumSpeed;
    Vec2f::copy(sumSpeed, moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
    float speedX = sumSpeed.m_x;
    if (moduleAccesser->getSituationModule().getKind() == 2) {
        speedX *= soValueAccesser::getConstantFloat(moduleAccesser, 0xfac, 0);
        float zero = 0.0f;
        stop.resetEnergy(6, &Vec2f(speedX, zero), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
        stop.enable();
        gravity.resetEnergy(0, &Vec2f(0.0f, zero), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
        gravity.enable();
        soKineticEnergyNormal& motion = dynamic_cast<soKineticEnergyNormal&>(*moduleAccesser->getKineticModule().getEnergy(0));
        motion.resetEnergy(5, &Vec2f(0.0f, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
        motion.enable();
        ftKineticEnergyDisableAndClear(2, moduleAccesser);
    } else {
        soKineticEnergyNormal& motion = dynamic_cast<soKineticEnergyNormal&>(*moduleAccesser->getKineticModule().getEnergy(0));
        motion.resetEnergy(3, &Vec2f(0.0f, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
        motion.enable();
        ftKineticEnergyDisableAndClear(3, moduleAccesser);
        ftKineticEnergyDisableAndClear(1, moduleAccesser);
        ftKineticEnergyDisableAndClear(2, moduleAccesser);
    }
}

#pragma dont_inline on
static float absValue(float value);
#pragma dont_inline off

static inline void resetGravity(ftKineticEnergyGravity& gravity, float speedY, soModuleAccesser* moduleAccesser) {
    Vec2f speed(0.0f, speedY);
    gravity.resetEnergy(0, &speed, &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
}
static inline void resetController(ftKineticEnergyController& controller, int mode, float speedX, soModuleAccesser* moduleAccesser) {
    Vec2f speed(speedX, 0.0f);
    controller.resetEnergy(mode, &speed, &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
}
// MATCH-ONLY: retain the reset mode across Vec3f construction; the inline helpers
// keep the speed vectors in the original temporary slots.
#pragma opt_propagation off
void ftMarthStatusUniqProcessSpecialHi::execStatus(soModuleAccesser* moduleAccesser) {
    ftKineticEnergyMotion& motion = dynamic_cast<ftKineticEnergyMotion&>(*moduleAccesser->getKineticModule().getEnergy(0));
    float stickMagnitude = absValue(moduleAccesser->getControllerModule().getStickX());
    if (!moduleAccesser->getWorkManageModule().isFlag(0x22000016)) {
        float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xfaa, 0);
        if (stickMagnitude > threshold) {
            float angle = (stickMagnitude - threshold) / (1.0f - threshold);
            angle *= soValueAccesser::getConstantFloat(moduleAccesser, 0xfab, 0);
            if (moduleAccesser->getControllerModule().getStickX() > 0.0f) {
                angle = -(0.01745329238474369f * angle);
            } else {
                angle = 0.01745329238474369f * angle;
            }
            // Keep the strongest stick-derived angle sampled during the launch window.
            float previousAngle = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
            float previousMagnitude = absValue(previousAngle);
            if (absValue(angle) > previousMagnitude) previousAngle = angle;
            moduleAccesser->getWorkManageModule().setFloat(previousAngle, 0x21000004);
        }
    }
    Vec2f sumSpeed;
    Vec2f::copy(sumSpeed, moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000010)) {
        if (!moduleAccesser->getWorkManageModule().isFlag(0x22000013)) {
            if (moduleAccesser->getMotionModule().getKind() == 0x1e9) {
                motion.unk40 = soValueAccesser::getConstantFloat(moduleAccesser, 0xfad, 0);
            }
            // After the first active update, falling starts the gravity/control handoff.
            if (moduleAccesser->getWorkManageModule().isFlag(0x22000014) && sumSpeed.m_y < 0.0f) {
                moduleAccesser->getWorkManageModule().onFlag(0x22000013);
            }
        } else {
            if (moduleAccesser->getKineticModule().getEnergy(1)->isEnable() == 0) {
                ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
                resetGravity(gravity, sumSpeed.m_y, moduleAccesser);
                gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xfae, 0);
                gravity.m_fallSpeedMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xfaf, 0);
                gravity.enable();
            }
            if (moduleAccesser->getKineticModule().getEnergy(2)->isEnable() == 0) {
                ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(*moduleAccesser->getKineticModule().getEnergy(2));
                int resetType = 0xb;
                resetController(controller, resetType, sumSpeed.m_x, moduleAccesser);
                controller.mulXAccelMul(soValueAccesser::getConstantFloat(moduleAccesser, 0xfa7, 0));
                controller.mulXSpeedMax(soValueAccesser::getConstantFloat(moduleAccesser, 0xfa7, 0));
                controller.enable();
            }
            motion.disable();
        }
        moduleAccesser->getWorkManageModule().onFlag(0x22000014);
    }
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000015)) {
        motion.unk3C = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
        moduleAccesser->getWorkManageModule().offFlag(0x22000015);
    }
}

#pragma opt_propagation reset
#pragma dont_inline on
static float absValue(float value) { return __fabsf(value); }
#pragma dont_inline off
void ftMarthStatusUniqProcessSpecialHi::execStop(soModuleAccesser*) {}
void ftMarthStatusUniqProcessSpecialHi::execFixPos(soModuleAccesser*) {}

void ftMarthStatusUniqProcessSpecialHi::exitStatus(soModuleAccesser* moduleAccesser, int) {
    float valueFA8 = soValueAccesser::getConstantFloat(moduleAccesser, 0xfa8, 0);
    moduleAccesser->getWorkManageModule().setFloat(valueFA8, 0x11000000);
    float valueFA7 = soValueAccesser::getConstantFloat(moduleAccesser, 0xfa7, 0);
    moduleAccesser->getWorkManageModule().setFloat(valueFA7, 0x11000001);
    moduleAccesser->getWorkManageModule().onFlag(0x12000003);
}

bool ftMarthStatusUniqProcessSpecialHi::onChangeLr(soModuleAccesser* moduleAccesser, float, float) {
    moduleAccesser->getWorkManageModule().setFloat(0.0f, 0x21000004);
    moduleAccesser->getWorkManageModule().onFlag(0x22000016);
    return true;
}

ftMarthStatusUniqProcessSpecialHi g_ftMarthStatusUniqProcessSpecialHi;
