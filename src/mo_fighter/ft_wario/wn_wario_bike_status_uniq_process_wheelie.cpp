// MATCH-ONLY: retain native fighter-module scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/wn_kinetic_energy_gravity.h>
#include <so/so_kinetic_energy_normal.h>
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <so/so_module_accesser.h>
#include <wn/wario/wn_wario_bike_link_event.h>
#include <math.h>

void wnWarioBikeStatusUniqProcessWheelie::initStatus(soModuleAccesser* a) {
    ftWarioBikeLinkEvent event(0x839);
    a->getLinkModule().sendEventParents(3, event);
    a->getKineticModule().changeKinetic(0x22, a);
    a->getWorkManageModule().offFlag(0x22000008);
}
void wnWarioBikeStatusUniqProcessWheelie::execStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soControllerModule& controller = a->getControllerModule();
    soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(*a->getKineticModule().getEnergy(0));
    normal.m_accel = Vec2f(0.0f, 0.0f);
    wnWarioBike& bike = dynamic_cast<wnWarioBike&>(a->getStageObject());
    wnWarioBikeParam* param = bike.m_param;
    float stick = controller.getStickY();
    float angle = work.getFloat(0x21000000) - param->unk64;
    if (stick > 0.0f) {
        angle += param->unk60 * stick;
        if (angle > param->unk5C) angle = param->unk5C;
    }
    work.setFloat(angle, 0x21000000);
    if (angle >= param->unk5C) work.incInt(0x20000002);
    else work.setInt(0, 0x20000002);
    wnWarioBikeStatusUniqProcessUtility::execStatus(a);
}
void wnWarioBikeStatusUniqProcessWheelie::execFixPos(soModuleAccesser* a) {
    // MATCH-ONLY: preserve native down-transition temporary lifetime.
    bool down;
    soWorkManageModule& work = a->getWorkManageModule();
    soKineticModule& kinetic = a->getKineticModule();
    soStatusModule& status = a->getStatusModule();
    soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(0));
    // MATCH-ONLY: retain native parameter-pointer lifetime before the energy cast.
    wnWarioBikeParam* param;
    wnKineticEnergyGravity& gravity = dynamic_cast<wnKineticEnergyGravity&>(*kinetic.getEnergy(1));
    param = dynamic_cast<wnWarioBike&>(a->getStageObject()).m_param;
    float angle = work.getFloat(0x21000002);
    float previousAngle = work.getFloat(0x21000003);
    if (!work.isFlag(0x22000005)) {
        status.changeStatusRequest(2, a);
    } else if (angle - previousAngle > param->unk48) {
        Vec2f velocity = normal.getSpeed();
        velocity.m_x *= param->unk68;
        normal.m_speed = velocity;
        velocity = gravity.getSpeed();
        velocity.m_y += param->unk6C;
        gravity.m_speedY = velocity.m_y;
        gravity.enable();
        kinetic.changeKinetic(0x21, a);
        a->getWorkManageModule().onFlag(0x22000008);
    } else {
        down = false;
        if (normal.getSpeed().length() < param->unk14) {
            if (work.getInt(0x20000002) >= param->unk70) down = true;
        }
        if (down) status.changeStatusRequest(0xd, a);
    }
}
void wnWarioBikeStatusUniqProcessWheelie::execFixPosCounter(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soKineticModule& kinetic = a->getKineticModule();
    soCollisionAttackModule& attacks = a->getCollisionAttackModule();
    wnWarioBikeParam* param = dynamic_cast<wnWarioBike&>(a->getStageObject()).m_param;
    float speed = kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(1)).length();
    float threshold = param->unk34;
    if (speed <= threshold) {
        if (attacks.isAttack(0, 0)) {
            attacks.clear(0);
            work.onFlag(0x2200000a);
        }
    } else {
        float power = param->unk30 * ((speed - threshold) / (param->unkC - threshold));
        if (attacks.isAttack(0, 0)) attacks.setPowerMul(power);
        else if (work.isFlag(0x2200000a)) {
            attacks.set(0, 0);
            attacks.setPowerMul(power);
            work.offFlag(0x2200000a);
        }
    }
}
wnWarioBikeStatusUniqProcessWheelie g_wnWarioBikeStatusUniqProcessWheelie;
