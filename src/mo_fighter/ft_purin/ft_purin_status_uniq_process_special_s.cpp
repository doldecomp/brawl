#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/purin/ft_purin_status_uniq_process.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <math.h>

void ftPurinStatusUniqProcessSpecialS::initStatus(soModuleAccesser*) { }
void ftPurinStatusUniqProcessSpecialS::exitStatus(soModuleAccesser*, int) { }

// Work flags request one-shot launch and reset for aerial Pound.
void ftPurinStatusUniqProcessSpecialS::execStatus(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getSituationModule().getKind() == Situation_Air) {
        if (moduleAccesser->getWorkManageModule().isFlag(0x22000011)) {
            moduleAccesser->getWorkManageModule().offFlag(0x22000011);
            ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
            ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
            float angle = getAngleSpecialAirSPurin(moduleAccesser->getControllerModule().getStickY(), moduleAccesser);
            Vec2f launchSpeed;
            float launchComponent = static_cast<float>(cos(angle));
            soPostureModule& posture = moduleAccesser->getPostureModule();
            launchSpeed.m_x = posture.getLr() * (launchComponent * soValueAccesser::getConstantFloat(moduleAccesser, 0xFCB, 0));
            launchComponent = static_cast<float>(sin(angle));
            launchSpeed.m_y = launchComponent * soValueAccesser::getConstantFloat(moduleAccesser, 0xFCB, 0);
            stop.setSpeed(&Vec2f(launchSpeed.m_x, 0.0f));
            gravity.m_speedY = launchSpeed.m_y;
        }

        switch (moduleAccesser->getWorkManageModule().getInt(0x20000000)) {
        case 1: {
            Vec2f speed;
            Vec2f::copy(speed, moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
            ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
            ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
            float speedX = speed.m_x * soValueAccesser::getConstantFloat(moduleAccesser, 0xFCC, 0);
            float speedY = speed.m_y * soValueAccesser::getConstantFloat(moduleAccesser, 0xFCC, 0);
            if (moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
                stop.resetEnergy(0x16, &Vec2f(speedX, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                gravity.m_gravity = 0.0f;
                gravity.m_speedY = speedY;
                gravity.unk18 = 0.0f;
                moduleAccesser->getWorkManageModule().offFlag(0x22000012);
            } else {
                stop.setSpeed(&Vec2f(speedX, 0.0f));
                gravity.m_speedY = speedY;
            }
            break;
        }
        }
        // A reset request is consumed even outside the velocity-scaling phase.
        if (moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
            moduleAccesser->getWorkManageModule().offFlag(0x22000012);
        }
    }
}

#pragma dont_inline on
// MATCH-ONLY: this unit retains its small speed setter as an external call.
inline void soKineticEnergyNormal::setSpeed(Vec2f* speed) {
    m_speed.m_x = speed->m_x;
    m_speed.m_y = speed->m_y;
}

// Apply the vertical-stick dead zone, cap its magnitude, and convert the
// configured maximum steering angle from degrees to radians.
float ftPurinStatusUniqProcessSpecialS::getAngleSpecialAirSPurin(float stickY, soModuleAccesser* moduleAccesser) {
    float magnitude = __fabsf(stickY);
    if (magnitude > soValueAccesser::getConstantFloat(moduleAccesser, 0xFC7, 0)) {
        magnitude = soValueAccesser::getConstantFloat(moduleAccesser, 0xFC7, 0);
    }
    magnitude -= soValueAccesser::getConstantFloat(moduleAccesser, 0xFC6, 0);
    if (magnitude < 0.0f) magnitude = 0.0f;
    if (stickY < 0.0f) magnitude = -magnitude;
    float minimum = soValueAccesser::getConstantFloat(moduleAccesser, 0xFC6, 0);
    float range = soValueAccesser::getConstantFloat(moduleAccesser, 0xFC7, 0) - minimum;
    float maximumAngle = soValueAccesser::getConstantFloat(moduleAccesser, 0xFC8, 0);
    return 0.01745329238474369f * (magnitude * maximumAngle / range);
}

// Shared defaults owned by the Pound unit, in native function order.
bool soStatusUniqProcess::checkTransitionPrecede(soModuleAccesser*, void*, int) { return true; }
void soStatusUniqProcess::leaveStop(soModuleAccesser*, int, bool) { }
bool soStatusUniqProcess::onChangeLr(soModuleAccesser*, float, float) { return false; }
void soStatusUniqProcess::checkAttack(soModuleAccesser*, void*, float) { }
bool soStatusUniqProcess::checkDamage(soModuleAccesser*, void*) { return false; }
void soStatusUniqProcess::execFixCamera(soModuleAccesser*) { }
void soStatusUniqProcess::execFixPos(soModuleAccesser*) { }
void soStatusUniqProcess::execFixPosCounter(soModuleAccesser*) { }
void soStatusUniqProcess::execMapCorrection(soModuleAccesser*) { }
void soStatusUniqProcess::execStop(soModuleAccesser*) { }

#pragma dont_inline reset

ftPurinStatusUniqProcessSpecialS g_ftPurinStatusUniqProcessSpecialS;
