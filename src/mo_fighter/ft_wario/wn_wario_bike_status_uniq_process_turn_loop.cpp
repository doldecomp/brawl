// MATCH-ONLY: retain the native article status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#define MT_VEC3F_CTOR_NOINLINE
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <wn/wario/wn_wario_bike_link_event.h>
#include <so/so_kinetic_energy_normal.h>
#include <so/so_module_accesser.h>
#include <mt/mt_prng.h>
#include <math.h>

void wnWarioBikeStatusUniqProcessTurnLoop::initStatus(soModuleAccesser* a) {
    soLinkModule& link = a->getLinkModule();
    ftWarioBikeLinkEvent event(0x83b);
    link.sendEventParents(3, event);
}

void wnWarioBikeStatusUniqProcessTurnLoop::execStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soPostureModule& posture = a->getPostureModule();
    soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(
        *a->getKineticModule().getEnergy(0));
    Vec2f speed;
    Vec2f::copy(speed, normal.getSpeed());
    float lr = posture.getLr();
    if (1.0f == lr) {
        if (speed.m_x <= 0.0f) work.onFlag(0x22000003);
    } else {
        if (speed.m_x >= 0.0f) work.onFlag(0x22000003);
    }
    float angle = work.getFloat(0x21000000);
    Vec3f rotation;
    rotation.m_x = -angle;
    rotation.m_y = 0.0f;
    rotation.m_z = 0.0f;
    posture.setRot(&rotation, 0);
}

void wnWarioBikeStatusUniqProcessTurnLoop::execFixPosCounter(soModuleAccesser* a) {
    if (a->getMotionModule().isLooped()) {
        soEffectModule& effects = a->getEffectModule();
        effects.req(static_cast<EfID>(0xa), 9,
                    &Vec3f(0.0f, 0.0f, 0.0f), &Vec3f(0.0f, 180.0f, 0.0f),
                    1.0f, &Vec3f(0.0f, 0.0f, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f),
                    false, 0);
    }
}

void wnWarioBikeStatusUniqProcessTurnLoop::execFixPos(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soGroundModule& ground = a->getGroundModule();
    if (ground.isTouch((grCollStatus::TouchMask)8, 0)) {
        float lr = a->getPostureModule().getLr();
        Vec2f normal;
        Vec2f::copy(normal, ground.getTouchNormal((grCollStatus::TouchMask)8, 0));
        float angle = 57.29578f * (float)atan2(-(normal.m_x * lr), normal.m_y);
        work.setFloat(angle, 0x21000000);
    }
}

wnWarioBikeStatusUniqProcessTurnLoop g_wnWarioBikeStatusUniqProcessTurnLoop;
