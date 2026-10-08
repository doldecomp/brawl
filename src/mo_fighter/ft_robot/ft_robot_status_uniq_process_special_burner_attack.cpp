#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/robot/ft_robot_status_uniq_process_special_burner_attack.h>
#include <ft/robot/ft_robot_status_uniq_process_special_burner.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>

void ftRobotStatusUniqProcessSpecialBurnerAttack::initStatus(soModuleAccesser* moduleAccesser) {
    // The start/thrust flame flags are cleared so controlEffect starts them again for this status.
    moduleAccesser->getWorkManageModule().offFlag(0x22000013);
    moduleAccesser->getWorkManageModule().offFlag(0x22000014);
    execStatus(moduleAccesser);
    moduleAccesser->getEffectModule().reqFollow(static_cast<EfID>(0x240002), 0x60, &Vec3f(0.0f, 0.0f, 0.0f), &Vec3f(0.0f, 0.0f, -90.0f), 1.0f, false, 1, 0, -1);
}

void ftRobotStatusUniqProcessSpecialBurnerAttack::execStatus(soModuleAccesser* moduleAccesser) {
    ftRobotStatusUniqProcessSpecialBurner::specialButtonPushCheck(moduleAccesser);
    ftRobotStatusUniqProcessSpecialBurner::controlBurner(moduleAccesser, true);
    ftRobotStatusUniqProcessSpecialBurner::controlEffect(moduleAccesser);
}

// Bumping a wall while thrusting bounces the sideways speed back.
void ftRobotStatusUniqProcessSpecialBurnerAttack::execFixPos(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getGroundModule().isTouch(static_cast<grCollStatus::TouchMask>(2), 0) || moduleAccesser->getGroundModule().isTouch(static_cast<grCollStatus::TouchMask>(4), 0)) {
        ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(*moduleAccesser->getKineticModule().getEnergy(2));
        Vec2f speed;
        Vec2f::copy(speed, controller.getSpeed());
        speed.m_x = -speed.m_x * soValueAccesser::getConstantFloat(moduleAccesser, 0xfcb, 0);
        controller.m_speed = speed;
    }
}

void ftRobotStatusUniqProcessSpecialBurnerAttack::exitStatus(soModuleAccesser* moduleAccesser, int nextStatus) {
    moduleAccesser->getControllerModule().stopRumbleKind(2, 7);
    moduleAccesser->getControllerModule().stopRumbleKind(8, 7);
}

ftRobotStatusUniqProcessSpecialBurnerAttack g_ftRobotStatusUniqProcessSpecialBurnerAttack;
