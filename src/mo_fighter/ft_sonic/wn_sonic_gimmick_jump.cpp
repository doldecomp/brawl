// MATCH-ONLY: retain the original article callback scheduling.
#pragma scheduling off
// MATCH-ONLY: Spring's native getter relocations target sora_melee's existing
// specialization; this TU must not inline or emit a replacement getter body.
#define SO_EVENT_OBSERVER_ID_OUT_OF_LINE
// MATCH-ONLY: the spring offset uses its original module-local Vec2 constructor.
#define MT_VEC2F_CTOR_NOINLINE
// MATCH-ONLY: status resets call the original scalar Vec2 assignment.
#define MT_VEC2F_ASSIGN_NOINLINE
// MATCH-ONLY: the spring emits its native XY-plus-Z constructor.
#define MT_VEC3F_FROM_VEC2_CTOR_NOINLINE
// MATCH-ONLY: retain the original named zero-rotation constructor in reset.
#define MT_VEC3F_CTOR_NOINLINE
#include <wn/sonic/wn_sonic_gimmick_jump.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/so_kinetic_energy_normal.h>
#include <so/so_kinetic_energy_rot_normal.h>
#include <mt/mt_prng.h>

soGimmickEventPresenter::soGimmickEventPresenter(int manageID, int sendID)
    : soEventPresenter<soGimmickEventObserver>(manageID, static_cast<short>(3)), m_sendID(sendID) { }
soGimmickEventPresenter::~soGimmickEventPresenter() { }

void wnSonicGimmickJump::onDeactivate() {
    soEventManageModule& events = m_moduleAccesser->getEventManageModule();
    int sender = static_cast<s16>(soGimmickEventObserver::getObserverId());
    soGimmickEventPresenter presenter(static_cast<soEventManager&>(events).getManageId(), sender);
    soModuleAccesser* acc = m_moduleAccesser;
    soGimmickEventArgs_Disable args;
    presenter.presentEventGimmick(&args, acc, -1);
}

void wnSonicGimmickJump::shoot() {
    if (!m_moduleAccesser->getWorkManageModule().isFlag(0x12000003) &&
        m_moduleAccesser->getGroundModule().attachGround(0) == true) {
        m_moduleAccesser->getSituationModule().setKind(Situation_Ground, false);
        m_moduleAccesser->getWorkManageModule().onFlag(0x22000000);
        m_moduleAccesser->getAreaModule().enableArea(0, true, -1);
    } else {
        m_moduleAccesser->getStatusModule().changeStatusRequest(1, m_moduleAccesser);
    }
}

void wnSonicGimmickJump::notifyEventChangeStatus(int kind, int prevKind, soStatusData* data, soModuleAccesser* acc) {
    Weapon::notifyEventChangeStatus(kind, prevKind, data, acc);
    // HYPOTHESIS: names of the spring's article statuses remain unresolved.
    if (kind == 1) {
        soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(
            *m_moduleAccesser->getKineticModule().getEnergy(0));
        soModuleAccesser* ownAcc = m_moduleAccesser;
        float speedY = soValueAccesser::getConstantFloat(acc, 0xFA4, 0);
        Vec2f speed;
        speed.m_x = 0.0f;
        speed.m_y = speedY;
        Vec3f rotation(0.0f, 0.0f, 0.0f);
        normal.resetEnergy(0, &speed, &rotation, ownAcc);
        float accelerationY = soValueAccesser::getConstantFloat(acc, 0xFA5, 0);
        Vec2f acceleration;
        acceleration.m_x = 0.0f;
        acceleration.m_y = accelerationY;
        normal.m_accel = acceleration;
        float targetY = soValueAccesser::getConstantFloat(acc, 0xFA6, 0);
        Vec2f target;
        target.m_x = 0.0f;
        target.m_y = targetY;
        normal.m_speedTarget = target;
        m_moduleAccesser->getKineticModule().enableEnergy(0);
        soKineticEnergyRotNormal& angular = dynamic_cast<soKineticEnergyRotNormal&>(
            *m_moduleAccesser->getKineticModule().getEnergy(1));
        float minimum = soValueAccesser::getConstantFloat(acc, 0xFA7, 0);
        float range = soValueAccesser::getConstantFloat(acc, 0xFA8, 0) - minimum;
        float rate = randf() * range;
        rate = soValueAccesser::getConstantFloat(acc, 0xFA7, 0) + rate;
        // Native bge takes the positive direction when LR is unordered as well.
        int sign = m_moduleAccesser->getPostureModule().getLr() < 0.0f ? -1 : 1;
        float signedRate = rate * sign;
        Vec3f angularSpeed;
        angularSpeed.m_x = 0.0f;
        angularSpeed.m_y = 0.0f;
        angularSpeed.m_z = signedRate;
        angular.m_rotSpeed = angularSpeed;
        m_moduleAccesser->getKineticModule().enableEnergy(1);
    }
    if (kind == 3) {
        soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(
            *m_moduleAccesser->getKineticModule().getEnergy(0));
        soModuleAccesser* ownAcc = m_moduleAccesser;
        float speedY = soValueAccesser::getConstantFloat(acc, 0xFA9, 0);
        Vec2f speed;
        speed.m_x = 0.0f;
        speed.m_y = speedY;
        Vec3f rotation(0.0f, 0.0f, 0.0f);
        normal.resetEnergy(0, &speed, &rotation, ownAcc);
        float accelerationY = soValueAccesser::getConstantFloat(acc, 0xFA5, 0);
        Vec2f acceleration;
        acceleration.m_x = 0.0f;
        acceleration.m_y = accelerationY;
        normal.m_accel = acceleration;
        float targetY = soValueAccesser::getConstantFloat(acc, 0xFA6, 0);
        Vec2f target;
        target.m_x = 0.0f;
        target.m_y = targetY;
        normal.m_speedTarget = target;
        m_moduleAccesser->getKineticModule().enableEnergy(0);
        soKineticEnergyRotNormal& angular = dynamic_cast<soKineticEnergyRotNormal&>(
            *m_moduleAccesser->getKineticModule().getEnergy(1));
        int sign = m_moduleAccesser->getPostureModule().getLr() < 0.0f ? -1 : 1;
        float direction = sign;
        float rate = soValueAccesser::getConstantFloat(acc, 0xFAA, 0);
        float signedRate = rate * direction;
        Vec3f angularSpeed;
        angularSpeed.m_x = 0.0f;
        angularSpeed.m_y = 0.0f;
        angularSpeed.m_z = signedRate;
        angular.m_rotSpeed = angularSpeed;
        m_moduleAccesser->getKineticModule().enableEnergy(1);
    }
}

void wnSonicGimmickJump::updateNodeSRT() {
    float scale = m_moduleAccesser->getPostureModule().getScale();
    Vec3f scaling;
    scaling.m_x = scale;
    scaling.m_y = scale;
    scaling.m_z = scale;
    Vec3f position = m_moduleAccesser->getPostureModule().getPos();
    Vec3f rotation = m_moduleAccesser->getPostureModule().getRot(0);
    m_moduleAccesser->getModelModule().setNodeRotate(4, &rotation);
    m_moduleAccesser->getModelModule().setNodeScale(0, &scaling);
    m_moduleAccesser->getModelModule().setNodeTranslate(0, &position);
}

void wnSonicGimmickJump::notifyEventGimmick(soGimmickEventArgs* args, int*) {
    if (args->m_kind == Gimmick::Event_Exit) return;
    // MATCH-ONLY: preserve the original exclusive range comparisons.
    if (args->m_kind <= Gimmick::Spring_Event_On - 1 || args->m_kind >= Gimmick::Spring_Event_Pos + 1) return;
    switch (args->m_kind) {
    case Gimmick::Spring_Event_On: {
        soModuleAccesser* acc = m_moduleAccesser;
        float offsetY = soValueAccesser::getConstantFloat(acc, 0xFA2, 0);
        float offsetX = soValueAccesser::getConstantFloat(acc, 0xFA1, 0);
        Vec2f offset(offsetX, offsetY);
        Vec3f position = m_moduleAccesser->getPostureModule().getPos();
        Vec2f position2;
        position2.m_x = position.m_x;
        position2.m_y = position.m_y;
        Vec2f top2 = position2 + offset;
        Vec3f top(top2, 0.0f);
        static_cast<soGimmickSpringEventArgs*>(args)->m_topPos = top;
        soGimmickSpringEventArgs_Shoot event(Vec3f(top2, 0.0f),
            soValueAccesser::getConstantFloat(m_moduleAccesser, 0xFA0, 0), 0.0f);
        soEventManageModule& events = m_moduleAccesser->getEventManageModule();
        int sender = static_cast<s16>(soGimmickEventObserver::getObserverId());
        soGimmickEventPresenter presenter(static_cast<soEventManager&>(events).getManageId(), sender);
        presenter.presentEventGimmick(&event, m_moduleAccesser, -1);
        m_moduleAccesser->getSoundModule().playSE(static_cast<SndID>(0x1989), false, 1, 0);
        break;
    }
    default: break;
    }
}
