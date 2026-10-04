#include <ft/ft_kinetic_energy.h>
#include <ft/ft_status_uniq_process_guard.h>
#include <so/motion/so_motion_module_impl.h>
#include <so/so_value_accesser.h>
#include <types.h>

ftStatusUniqProcessGuardDamage g_ftStatusUniqProcessGuardDamage;

void ftStatusUniqProcessGuardDamage::initStatus(soModuleAccesser* moduleAccesser) {
    moduleAccesser->getCollisionShieldModule().setStatus(0, 1, 0);

    // HYPOTHESIS: shield stun (in frames) is derived from the incoming damage stored in
    // work float 0x21000008 and a few ftCommonData shield constants; the shield-damage
    // motion (kind 0x42) is retimed so that it lasts exactly that long.
    soWorkManageModule* workManage = &moduleAccesser->getWorkManageModule();
    float stun = soValueAccesser::getConstantFloat(moduleAccesser, 0xcab, 0) +
                 soValueAccesser::getConstantFloat(moduleAccesser, 0xcaa, 0) *
                     (workManage->getFloat(0x21000008) * (1.0f - soValueAccesser::getConstantFloat(moduleAccesser, 0xcb1, 0)));
    int stunFrames = (int)stun;
    moduleAccesser->getWorkManageModule().setInt(stunFrames, 0x20000005);

    float rate = 1.0f;
    if (moduleAccesser->getMotionModule().isAnimResFile(0x42) == 1) {
        rate = moduleAccesser->getMotionModule().getEndFrame(0x42) / (float)stunFrames;
    }
    soMotionChangeParam motionParam;
    motionParam.m_kind = 0x42;
    motionParam.m_frame = 0.0f;
    motionParam.m_rate = rate;
    motionParam._12 = 0;
    motionParam._13 = 0;
    motionParam._14 = 0;
    motionParam._15 = 0;
    moduleAccesser->getMotionModule().changeMotionRequest(&motionParam);

    // HYPOTHESIS: pushback speed applied to the shield-damage kinetic energy.
    float pushback = stun * soValueAccesser::getConstantFloat(moduleAccesser, 0xcac, 0);
    if (moduleAccesser->getWorkManageModule().getInt(0x20000001) > 0) {
        pushback *= soValueAccesser::getConstantFloat(moduleAccesser, 0xcb3, 0);
    }
    if (pushback > soValueAccesser::getConstantFloat(moduleAccesser, 0xcad, 0)) {
        pushback = soValueAccesser::getConstantFloat(moduleAccesser, 0xcad, 0);
    }

    soKineticEnergyNormal* energy = &dynamic_cast<soKineticEnergyNormal&>(*moduleAccesser->getKineticModule().getEnergy(4));
    Vec2f speed;
    speed.m_x = pushback * -moduleAccesser->getWorkManageModule().getFloat(0x21000009);
    speed.m_y = 0.0f;
    Vec3f rot;
    rot.m_x = 0.0f;
    rot.m_y = 0.0f;
    rot.m_z = 0.0f;
    energy->resetEnergy(0xb, &speed, &rot, moduleAccesser);
    energy->enable();

    m_guardFunc->setShieldScale(moduleAccesser);
}

void ftStatusUniqProcessGuardDamage::execStatus(soModuleAccesser* moduleAccesser) {
    m_guardFunc->setShieldScale(moduleAccesser);
}

void ftStatusUniqProcessGuardDamage::exitStatus(soModuleAccesser* moduleAccesser, int) {
    moduleAccesser->getCollisionShieldModule().setStatus(0, 0, 0);
    moduleAccesser->getEffectModule().removeCommon(0x1b);
}
