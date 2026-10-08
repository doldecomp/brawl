#include <ft/marth/ft_marth_status_uniq_process.h>
#include <ft/ft_kinetic_energy.h>
#include <ft/ft_manager.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

// Counter preserves horizontal speed on entry and changes kinetic setup on landing/takeoff.
void ftKineticEnergyDisableAndClear(int index, soModuleAccesser* moduleAccesser);

void ftMarthStatusUniqProcessSpecialLw::initStatus(soModuleAccesser* moduleAccesser) {
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
    Vec2f sumSpeed;
    Vec2f::copy(sumSpeed, moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
    // MATCH-ONLY: copy the returned vector with the original integer-load/store path.
    float speedX = sumSpeed.m_x;
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x115:
        if (moduleAccesser->getSituationModule().getKind() == 2) {
            speedX *= soValueAccesser::getConstantFloat(moduleAccesser, 0xfb0, 0);
            float zero = 0.0f;
            stop.resetEnergy(6, &Vec2f(speedX, zero), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
            stop.soKineticEnergyNormal::setBrake(&Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xfb1, 0), 0.0f));
            stop.enable();
            gravity.resetEnergy(0, &Vec2f(0.0f, zero), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
            gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xfb2, 0);
            gravity.m_fallSpeedMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb3, 0);
            gravity.enable();
            ftKineticEnergyDisableAndClear(2, moduleAccesser);
            moduleAccesser->getWorkManageModule().setInt(2, 0x20000000);
        } else {
            moduleAccesser->getWorkManageModule().setInt(0, 0x20000000);
        }
        break;
    case 0x11d: {
        // Scale the stored hit power, then apply the configured minimum and maximum.
        float incomingPower = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
        float powerMultiplier = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb4, 0);
        float powerMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb7, 0);
        if (static_cast<u8>(g_ftManager->m_mode) == 1) {
            powerMultiplier = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb5, 0);
            powerMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb8, 0);
        }
        float counterPower = incomingPower * powerMultiplier;
        if (counterPower < soValueAccesser::getConstantFloat(moduleAccesser, 0xfb6, 0)) {
            counterPower = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb6, 0);
        }
        if (counterPower > powerMax) {
            counterPower = powerMax;
        }
        moduleAccesser->getWorkManageModule().setFloat(counterPower, 0x21000004);
        break;
    }
    }
}

void soKineticEnergyNormal::setBrake(Vec2f* brake) {
    m_brake.m_x = brake->m_x;
    m_brake.m_y = brake->m_y;
}

void ftMarthStatusUniqProcessSpecialLw::execStatus(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
        case 0x115: {
            soWorkManageModule& work = moduleAccesser->getWorkManageModule();
            soSituationModule& situation = moduleAccesser->getSituationModule();
            if (situation.getKind() != work.getInt(0x20000000)) {
                ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
                ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
                Vec2f sumSpeed;
                Vec2f::copy(sumSpeed, moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
                float speedX = sumSpeed.m_x;
                float speedY = sumSpeed.m_y;
                if (moduleAccesser->getSituationModule().getKind() == 2) {
                    stop.resetEnergy(6, &Vec2f(speedX, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                    stop.soKineticEnergyNormal::setBrake(&Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xfb1, 0), 0.0f));
                    stop.enable();
                    gravity.resetEnergy(0, &Vec2f(0.0f, speedY), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                    gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xfb2, 0);
                    gravity.m_fallSpeedMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb3, 0);
                    gravity.enable();
                    ftKineticEnergyDisableAndClear(2, moduleAccesser);
                    moduleAccesser->getWorkManageModule().setInt(2, 0x20000000);
                } else {
                    moduleAccesser->getWorkManageModule().setInt(0, 0x20000000);
                }
            }
            break;
        }
        case 0x11d:
            break;
    }
}

void ftMarthStatusUniqProcessSpecialLw::execStop(soModuleAccesser*) {}

void ftMarthStatusUniqProcessSpecialLw::execFixPos(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
        case 0x115:
            if (!moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
                if (moduleAccesser->getWorkManageModule().isFlag(0x22000011)) {
                    moduleAccesser->getCollisionShieldModule().setStatus(0, 1, 1);
                    moduleAccesser->getWorkManageModule().onFlag(0x22000012);
                }
            } else if (!moduleAccesser->getWorkManageModule().isFlag(0x22000011)) {
                moduleAccesser->getCollisionShieldModule().setStatus(0, 0, 1);
                moduleAccesser->getWorkManageModule().offFlag(0x22000012);
            }
            break;
        case 0x11d: {
            soCollisionAttackModule& attack = moduleAccesser->getCollisionAttackModule();
            float power = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
            if (!(power <= 0.0f)) {
                for (int i = 0; i < (int)attack.getPartSize(); i++) {
                    if (attack.isAttack(i, false)) {
                        attack.setPower(i, (int)power, false);
                    }
                }
            }
            break;
        }
    }
}

void ftMarthStatusUniqProcessSpecialLw::exitStatus(soModuleAccesser* moduleAccesser, int) {
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
        moduleAccesser->getCollisionShieldModule().setStatus(0, 0, 1);
    }
}

ftMarthStatusUniqProcessSpecialLw g_ftMarthStatusUniqProcessSpecialLw;
