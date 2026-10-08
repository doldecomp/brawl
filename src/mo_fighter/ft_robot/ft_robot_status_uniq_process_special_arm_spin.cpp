// This is the first status unit of the REL, so it emits the shared soStatusUniqProcess inline virtuals (and their dtor).
#include <ft/robot/ft_robot_status_uniq_process_special_arm_spin.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <math.h>

void ftKineticEnergyDisableAndClear(int index, soModuleAccesser* moduleAccesser);

// HYPOTHESIS: view of the common fighter parameters used for the "stick pushed forward fast enough" test.
struct ftArmSpinCommonParamView {
    u8 unk00[0x18];
    float stickThreshold; // 0x18
    int flickFrames;      // 0x1c
    float flickMargin;    // 0x20
};
inline ftArmSpinCommonParamView* getCommonParamView() {
    return reinterpret_cast<ftArmSpinCommonParamView*>(g_ftCommonDataAccesser.getParamCommon());
}

// HYPOTHESIS: shared absolute value helper of the ft_robot REL (emitted once as an 8-byte function).
inline float absValue(float value) __attribute__((never_inline)) { return __fabsf(value); }
inline float absValueInline(float value) { return __fabsf(value); }

// Work variables (HYPOTHESIS names, from how the status uses them):
//   int   0x20000000  frames since the spin started
//   int   0x20000001  frames since the last extra boost (capped at const 0x5dc4)
//   int   0x20000002  extra boosts used so far
//   int   0x20000003  situation (ground/air) the energies were last set up for
//   float 0x21000004  spin power; drains every frame and the spin ends at 0
//   float 0x21000005  power lost per frame (const 0xfb8, reset to const 0xfbb)
//   float 0x21000007  lean (rotation around Y) of the waist node while spinning
//   float 0x21000009  accumulated spin rotation (around X) of the waist node
//   flag  0x22000011  the special button was released since the last boost (a new press may boost again)
//   flag  0x22000012  stick pushed forward on entry (strong spin)
//   flag  0x22000013  set on entry
//   flag  0x22000014  the spin's launch speed still has to be applied / energies have to be set up again

void ftRobotStatusUniqProcessSpecialArmSpin::initStatus(soModuleAccesser* moduleAccesser) {
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
    Vec2f sumSpeed;
    Vec2f::copy(sumSpeed, moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
    float speedX = sumSpeed.m_x;
    float speedY = sumSpeed.m_y;
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x113: {
        // Pushing the stick forward hard and fast enough starts the stronger spin.
        float stick = (float)fabs(moduleAccesser->getControllerModule().getStickX());
        if (stick >= getCommonParamView()->stickThreshold) {
            soControllerModule& controller = moduleAccesser->getControllerModule();
            float flickBase = getCommonParamView()->flickMargin;
            float flickAdd = (float)getCommonParamView()->flickFrames;
            float window = flickAdd + flickBase;
            if ((float)controller.getFlickNoResetX() < window) {
                moduleAccesser->getWorkManageModule().onFlag(0x22000012);
            }
        }
        float startSpin = soValueAccesser::getConstantFloat(moduleAccesser, 0xfae, 0);
        moduleAccesser->getWorkManageModule().setFloat(startSpin, 0x21000004);
        moduleAccesser->getWorkManageModule().setFloat(soValueAccesser::getConstantFloat(moduleAccesser, 0xfb8, 0), 0x21000005);
        moduleAccesser->getWorkManageModule().setFloat(soValueAccesser::getConstantFloat(moduleAccesser, 0xfbb, 0), 0x21000006);
        moduleAccesser->getWorkManageModule().setFloat(0.0f, 0x21000007);
        moduleAccesser->getWorkManageModule().setInt(soValueAccesser::getConstantInt(moduleAccesser, 0x5dc4, 0), 0x20000001);
        soControllerModule& controller = moduleAccesser->getControllerModule();
        int specialMask = soController::getButtonMask(soController::Pad_Button_Special);
        int held = controller.getButton();
        if (held & specialMask) {
            moduleAccesser->getWorkManageModule().offFlag(0x22000011);
        } else {
            moduleAccesser->getWorkManageModule().onFlag(0x22000011);
        }
        moduleAccesser->getWorkManageModule().onFlag(0x22000013);
        break;
    }
    case 0x117:
        if (moduleAccesser->getSituationModule().getKind() == 2) {
            stop.resetEnergy(6, &Vec2f(speedX, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
            stop.enable();
            if (speedY < -soValueAccesser::getConstantFloat(moduleAccesser, 0xfb0, 0)) {
                speedY = -soValueAccesser::getConstantFloat(moduleAccesser, 0xfb0, 0);
            }
            gravity.resetEnergy(0, &Vec2f(0.0f, speedY), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
            gravity.enable();
        } else {
            stop.resetEnergy(0, &Vec2f(speedX, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
            stop.enable();
            ftKineticEnergyDisableAndClear(1, moduleAccesser);
        }
        ftKineticEnergyDisableAndClear(2, moduleAccesser);
        moduleAccesser->getWorkManageModule().setInt(moduleAccesser->getSituationModule().getKind(), 0x20000003);
        break;
    }
}

void ftRobotStatusUniqProcessSpecialArmSpin::exitStatus(soModuleAccesser* moduleAccesser, int nextStatus) {
    moduleAccesser->getPostureModule().initRot();
}

void ftRobotStatusUniqProcessSpecialArmSpin::execStatus(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x117: {
        Vec2f sumSpeed;
        Vec2f::copy(sumSpeed, moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
        float speedX = sumSpeed.m_x;
        float speedY = sumSpeed.m_y;
        float launch = moduleAccesser->getPostureModule().getLr();
        float baseSpeed = soValueAccesser::getConstantFloat(moduleAccesser, 0xfbe, 0);
        float speedScale = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0);
        float topSpeed = speedScale * baseSpeed;
        int situation = moduleAccesser->getSituationModule().getKind();
        if (work.isFlag(0x22000014)) {
            if (situation == 2) {
                if (work.isFlag(0x22000012)) {
                    launch *= soValueAccesser::getConstantFloat(moduleAccesser, 0xfb4, 0);
                } else {
                    launch *= soValueAccesser::getConstantFloat(moduleAccesser, 0xfb3, 0);
                }
            } else {
                if (work.isFlag(0x22000012)) {
                    launch *= soValueAccesser::getConstantFloat(moduleAccesser, 0xfb2, 0);
                } else {
                    launch *= soValueAccesser::getConstantFloat(moduleAccesser, 0xfb1, 0);
                }
            }
            speedX += launch;
        }
        if (work.isFlag(0x22000014) || moduleAccesser->getSituationModule().getKind() != work.getInt(0x20000003)) {
            if (situation == 2) {
                ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(*moduleAccesser->getKineticModule().getEnergy(2));
                ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
                int resetMode = 0;
                controller.resetEnergy(resetMode, &Vec2f(speedX, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                controller.m_speedTarget = Vec2f(topSpeed, 0.0f);
                controller.enable();
                gravity.resetEnergy(0, &Vec2f(0.0f, speedY), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                gravity.enable();
                ftKineticEnergyDisableAndClear(3, moduleAccesser);
            } else {
                ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
                stop.resetEnergy(0, &Vec2f(speedX, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                stop.enable();
                ftKineticEnergyDisableAndClear(1, moduleAccesser);
                ftKineticEnergyDisableAndClear(2, moduleAccesser);
            }
            work.offFlag(0x22000014);
            work.setInt(situation, 0x20000003);
        }
        int frame = work.getInt(0x20000000);
        Vec3f bodyRot = moduleAccesser->getPostureModule().getRot(0);
        float spin = work.getFloat(0x21000004);
        int sinceBoost = work.getInt(0x20000001);
        work.setInt(frame + 1, 0x20000000);
        if (situation == 2) {
            ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
            if (frame + 1 <= soValueAccesser::getConstantInt(moduleAccesser, 0x5dc2, 0)) {
                gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xbcf, 0) * soValueAccesser::getConstantFloat(moduleAccesser, 0xfb5, 0);
            } else {
                gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xbcf, 0);
            }
        }
        // Pressing the special button again, after releasing it, boosts the spin once per press.
        soControllerModule& controller = moduleAccesser->getControllerModule();
        int specialMask = soController::getButtonMask(soController::Pad_Button_Special);
        int held = controller.getButton();
        if (!(held & specialMask)) {
            work.onFlag(0x22000011);
        }
        if (sinceBoost >= soValueAccesser::getConstantInt(moduleAccesser, 0x5dc4, 0)) {
            if (work.isFlag(0x22000011)) {
                if (work.getInt(0x20000002) < soValueAccesser::getConstantInt(moduleAccesser, 0x5dc5, 0)) {
                    soControllerModule& boostController = moduleAccesser->getControllerModule();
                    int boostMask = soController::getButtonMask(soController::Pad_Button_Special);
                    int boostHeld = boostController.getButton();
                    if (boostHeld & boostMask) {
                        spin += soValueAccesser::getConstantFloat(moduleAccesser, 0xfbc, 0);
                        work.addInt(1, 0x20000002);
                        work.offFlag(0x22000011);
                        sinceBoost = 0;
                    }
                }
            }
        }
        if (sinceBoost < soValueAccesser::getConstantInt(moduleAccesser, 0x5dc4, 0)) {
            sinceBoost++;
        }
        work.setInt(sinceBoost, 0x20000001);
        // The waist node turns with the spin and leans with the stick.
        int node = moduleAccesser->getModelModule().getNodeId("Waist6NCon");
        Vec3f rot = moduleAccesser->getModelModule().getNodeRotate(node);
        work.addFloat(spin, 0x21000009);
        rot.m_x = work.getFloat(0x21000009);
        float stickX = moduleAccesser->getControllerModule().getStickX();
        float sway = moduleAccesser->getWorkManageModule().getFloat(0x21000007);
        if (absValue(stickX) > 0.0f) {
            float lr = moduleAccesser->getPostureModule().getLr();
            float swayRate = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb7, 0);
            float push = stickX * -swayRate;
            float step = push * lr;
            float limit = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb6, 0);
            sway += step;
            if (absValue(sway) > limit) {
                if (sway < 0.0f) {
                    limit = -limit;
                }
                sway = limit;
            }
        } else {
            float decay = soValueAccesser::getConstantFloat(moduleAccesser, 0xfbd, 0);
            if (sway < 0.0f) {
                sway += decay;
                if (sway > 0.0f) {
                    sway = 0.0f;
                }
            } else if (sway > 0.0f) {
                sway -= decay;
                if (sway < 0.0f) {
                    sway = 0.0f;
                }
            }
        }
        rot.m_y = sway;
        moduleAccesser->getModelModule().setNodeRotate(node, &rot);
        work.setFloat(sway, 0x21000007);
        float drain = moduleAccesser->getWorkManageModule().getFloat(0x21000005);
        if (frame + 1 >= soValueAccesser::getConstantInt(moduleAccesser, 0x5dc3, 0)) {
            drain = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb9, 0);
        }
        spin -= drain;
        work.setFloat(spin, 0x21000004);
        break;
    }
    }
}

void ftRobotStatusUniqProcessSpecialArmSpin::execStop(soModuleAccesser* moduleAccesser) {
    int node = moduleAccesser->getModelModule().getNodeId("Waist6NCon");
    Vec3f rot = moduleAccesser->getModelModule().getNodeRotate(node);
    rot.m_x = moduleAccesser->getWorkManageModule().getFloat(0x21000009);
    rot.m_y = moduleAccesser->getWorkManageModule().getFloat(0x21000007);
    moduleAccesser->getModelModule().setNodeRotate(node, &rot);
}

void ftRobotStatusUniqProcessSpecialArmSpin::setEventCollisionAttack(soModuleAccesser* moduleAccesser) {
    float spin = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
    spin -= soValueAccesser::getConstantFloat(moduleAccesser, 0xfba, 0);
    if (spin < 0.0f) {
        spin = 0.0f;
    }
    moduleAccesser->getWorkManageModule().setFloat(spin, 0x21000004);
}

ftRobotStatusUniqProcessSpecialArmSpin g_ftRobotStatusUniqProcessSpecialArmSpin;
