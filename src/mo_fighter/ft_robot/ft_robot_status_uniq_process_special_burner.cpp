#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/robot/ft_robot_status_uniq_process_special_burner.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/controller/so_controller_impl.h>

// Work variables (HYPOTHESIS names, from how the status and ftRobot::updateSpecialHi use them):
//   float 0x11000015  burner fuel; drains while the thrust is on, the burner shuts off at 0
//   flag  0x22000012  thrust input held (special button held, or stick pushed up far enough)
//   flag  0x22000013  start flame effect is running (handle in int 0x20000001)
//   flag  0x22000014  thrust flame effect is running (handle in int 0x20000002)
//   flag  0x22000015  the burner is thrusting this frame
//   flag  0x22000016  the thrust sound loop is playing (handle in int 0x20000003)

void ftRobotStatusUniqProcessSpecialBurner::initStatus(soModuleAccesser* moduleAccesser) {
    ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(*moduleAccesser->getKineticModule().getEnergy(2));
    // Keep the upward speed the fighter already has, but no more than the entry speed limit.
    Vec2f speed;
    Vec2f::copy(speed, moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
    if (speed.m_x > soValueAccesser::getConstantFloat(moduleAccesser, 0xfc2, 0)) {
        speed.m_x = soValueAccesser::getConstantFloat(moduleAccesser, 0xfc2, 0);
    }
    controller.resetEnergy(0xb, &Vec2f(speed.m_x, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
    controller.m_speed = Vec2f(speed.m_x, 0.0f);
    controller.m_unk40 = soValueAccesser::getConstantFloat(moduleAccesser, 0xfc7, 0);
    controller.m_speedTarget = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xfc8, 0), 0.0f);
    controller.enable();
    execStatus(moduleAccesser);
    int flame = moduleAccesser->getEffectModule().reqFollow(static_cast<EfID>(0x240002), 0x60, &Vec3f(0.0f, 0.0f, 0.0f), &Vec3f(0.0f, 0.0f, -90.0f), 1.0f, false, 1, 0, -1);
    moduleAccesser->getWorkManageModule().setInt(flame, 0x20000001);
    moduleAccesser->getWorkManageModule().onFlag(0x22000013);
    moduleAccesser->getControllerModule().setRumble(2, 0, false, 7);
}

void ftRobotStatusUniqProcessSpecialBurner::execStatus(soModuleAccesser* moduleAccesser) {
    specialButtonPushCheck(moduleAccesser);
    controlBurner(moduleAccesser, true);
    controlEffect(moduleAccesser);
    controlRumble(moduleAccesser);
}

// Bumping a wall while thrusting bounces the sideways speed back.
void ftRobotStatusUniqProcessSpecialBurner::execFixPos(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getGroundModule().isTouch(static_cast<grCollStatus::TouchMask>(2), 0) || moduleAccesser->getGroundModule().isTouch(static_cast<grCollStatus::TouchMask>(4), 0)) {
        ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(*moduleAccesser->getKineticModule().getEnergy(2));
        Vec2f speed;
        Vec2f::copy(speed, controller.getSpeed());
        speed.m_x = -speed.m_x * soValueAccesser::getConstantFloat(moduleAccesser, 0xfcb, 0);
        controller.m_speed = speed;
    }
}

void ftRobotStatusUniqProcessSpecialBurner::execStop(soModuleAccesser* moduleAccesser) { }

void ftRobotStatusUniqProcessSpecialBurner::exitStatus(soModuleAccesser* moduleAccesser, int nextStatus) {
    // HYPOTHESIS: 0x119 and 0x11A are the other Robo Burner statuses; leaving to anything else ends the rumble.
    if (nextStatus >= 0x11b || nextStatus < 0x119) {
        moduleAccesser->getControllerModule().stopRumbleKind(2, 7);
        moduleAccesser->getControllerModule().stopRumbleKind(8, 7);
    }
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000016)) {
        int sound = moduleAccesser->getWorkManageModule().getInt(0x20000003);
        if (sound >= 0) {
            moduleAccesser->getSoundModule().stopSEHandle(sound, 0);
        }
        moduleAccesser->getWorkManageModule().offFlag(0x22000016);
    }
}

// The thrust is requested by holding the special button, or by pushing the stick up past a threshold.
void ftRobotStatusUniqProcessSpecialBurner::specialButtonPushCheck(soModuleAccesser* moduleAccesser) {
    soControllerModule& controller = moduleAccesser->getControllerModule();
    u32 specialMask = soController::getButtonMask(soController::Pad_Button_Special);
    int held = controller.getButton();
    if (held & specialMask) {
        moduleAccesser->getWorkManageModule().onFlag(0x22000012);
    } else {
        moduleAccesser->getWorkManageModule().offFlag(0x22000012);
    }
    soControllerModule& stickController = moduleAccesser->getControllerModule();
    float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xc42, 0);
    if (stickController.getStickY() >= threshold) {
        moduleAccesser->getWorkManageModule().onFlag(0x22000012);
    }
}

// Applies one frame of thrust: while input is held and fuel remains, gravity is replaced by a lift that depends on the
// current vertical speed and the fuel drains; otherwise normal gravity is restored and the thrust sound is stopped.
void ftRobotStatusUniqProcessSpecialBurner::controlBurner(soModuleAccesser* moduleAccesser, bool consumeFuel) {
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000012) && moduleAccesser->getWorkManageModule().getFloat(0x11000015) > 0.0f) {
        float lift = soValueAccesser::getConstantFloat(moduleAccesser, 0xfc4, 0);
        Vec2f speed;
        Vec2f::copy(speed, gravity.getSpeed());
        if (speed.m_y >= soValueAccesser::getConstantFloat(moduleAccesser, 0xfc5, 0)) {
            lift = soValueAccesser::getConstantFloat(moduleAccesser, 0xfc6, 0);
        }
        gravity.m_gravity = lift - soValueAccesser::getConstantFloat(moduleAccesser, 0xfc9, 0);
        if (consumeFuel) {
            float rate = 1.0f;
            if (!(soValueAccesser::getConstantFloat(moduleAccesser, 0xfcd, 0) == 0.0f)) {
                rate *= soValueAccesser::getConstantFloat(moduleAccesser, 0xfce, 0);
            }
            moduleAccesser->getWorkManageModule().addFloat(-rate, 0x11000015);
        }
        moduleAccesser->getWorkManageModule().onFlag(0x22000015);
        if (!moduleAccesser->getWorkManageModule().isFlag(0x22000016)) {
            bool noPan = false;
            int sound = moduleAccesser->getSoundModule().playSE(static_cast<SndID>(0x1775), noPan, noPan, 0);
            moduleAccesser->getWorkManageModule().setInt(sound, 0x20000003);
            moduleAccesser->getWorkManageModule().onFlag(0x22000016);
        }
    } else {
        gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xfc9, 0);
        gravity.m_fallSpeedMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xfca, 0);
        moduleAccesser->getWorkManageModule().offFlag(0x22000015);
        if (moduleAccesser->getWorkManageModule().isFlag(0x22000016)) {
            int sound = moduleAccesser->getWorkManageModule().getInt(0x20000003);
            if (sound >= 0) {
                moduleAccesser->getSoundModule().stopSEHandle(sound, 0);
            }
            moduleAccesser->getWorkManageModule().offFlag(0x22000016);
        }
    }
}

// Two flame effects: the start flame while the burner is idle, the thrust flame while it is firing.
void ftRobotStatusUniqProcessSpecialBurner::controlEffect(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000015)) {
        if (!moduleAccesser->getWorkManageModule().isFlag(0x22000014)) {
            int flame = moduleAccesser->getEffectModule().reqFollow(static_cast<EfID>(0x24000a), 0x60, &Vec3f(0.0f, 0.0f, 0.0f), &Vec3f(0.0f, 0.0f, -90.0f), 1.0f, false, 1, 0, -1);
            moduleAccesser->getWorkManageModule().setInt(flame, 0x20000002);
            moduleAccesser->getWorkManageModule().onFlag(0x22000014);
        }
    } else if (moduleAccesser->getWorkManageModule().isFlag(0x22000014)) {
        moduleAccesser->getEffectModule().kill(moduleAccesser->getWorkManageModule().getInt(0x20000002), true, true);
        moduleAccesser->getWorkManageModule().offFlag(0x22000014);
    }
    if (moduleAccesser->getWorkManageModule().getFloat(0x11000015) <= 0.0f) {
        if (moduleAccesser->getWorkManageModule().isFlag(0x22000013)) {
            int startFlame = moduleAccesser->getWorkManageModule().getInt(0x20000001);
            moduleAccesser->getEffectModule().kill(startFlame, true, true);
        }
        if (moduleAccesser->getWorkManageModule().isFlag(0x22000014)) {
            int thrustFlame = moduleAccesser->getWorkManageModule().getInt(0x20000002);
            moduleAccesser->getEffectModule().kill(thrustFlame, true, true);
        }
    }
}

// A strong rumble while thrusting (kind 8) and the rest of the rumbles are cut when the fuel runs out.
void ftRobotStatusUniqProcessSpecialBurner::controlRumble(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000015)) {
        moduleAccesser->getControllerModule().setRumble(8, 0, false, 7);
    } else {
        moduleAccesser->getControllerModule().stopRumbleKind(8, 7);
    }
    if (moduleAccesser->getWorkManageModule().getFloat(0x11000015) <= 0.0f) {
        moduleAccesser->getControllerModule().stopRumbleKind(2, 7);
        moduleAccesser->getControllerModule().stopRumbleKind(4, 7);
        moduleAccesser->getControllerModule().stopRumbleKind(8, 7);
    }
}

ftRobotStatusUniqProcessSpecialBurner g_ftRobotStatusUniqProcessSpecialBurner;
