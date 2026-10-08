// MATCH-ONLY: retain native fighter-module scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/wn_kinetic_energy_gravity.h>
#include <so/so_kinetic_energy_normal.h>
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <so/so_module_accesser.h>
#include <wn/wario/wn_wario_bike_link_event.h>
#include <math.h>

void wnWarioBikeStatusUniqProcessDrive::initStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soLinkModule& link = a->getLinkModule();
    if (work.isFlag(0x22000000)) work.offFlag(0x22000000);
    else {
        ftWarioBikeLinkEvent event(0x838);
        link.sendEventParents(3, event);
    }
    work.offFlag(0x22000002);
    int previous = a->getStatusModule().getPrevStatusKind(0);
    if (previous != 3 && previous != 0xe) work.offFlag(0x2200000a);
    work.setInt(0, 0x20000004);
    work.onFlag(0x2200000c);
}
void wnWarioBikeStatusUniqProcessDrive::execFixPosCounter(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soKineticModule& kinetic = a->getKineticModule();
    soCollisionAttackModule& attack = a->getCollisionAttackModule();
    wnWarioBike& bike = dynamic_cast<wnWarioBike&>(a->getStageObject());
    wnWarioBikeParam* param = bike.m_param;
    float speed = kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(1)).length();
    if (speed <= param->unk34) {
        if (attack.isAttack(0, false)) {
            attack.clear(0);
            work.onFlag(0x2200000a);
        }
    } else {
        float power = param->unk30 * ((speed - param->unk34) / (param->unkC - param->unk34));
        if (attack.isAttack(0, false)) attack.setPowerMul(power);
        else if (work.isFlag(0x2200000a)) {
            attack.set(0, 0);
            attack.setPowerMul(power);
            work.offFlag(0x2200000a);
        }
    }
    wnWarioBikeStatusUniqProcessUtility::execFixPosCounter(a);
}
void wnWarioBikeStatusUniqProcessDrive::execFixPos(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soControllerModule& controller = a->getControllerModule();
    soSituationModule& situation = a->getSituationModule();
    soKineticModule& kinetic = a->getKineticModule();
    soPostureModule& posture = a->getPostureModule();
    soStatusModule& status = a->getStatusModule();
    soMotionModule& motion = a->getMotionModule();
    soGroundModule& ground = a->getGroundModule();
    wnWarioBike& bike = dynamic_cast<wnWarioBike&>(a->getStageObject());
    wnWarioBikeParam* param = bike.m_param;
    bool front = work.isFlag(0x22000004);
    bool rear = work.isFlag(0x22000005);
    bool touch = work.isFlag(0x22000006);
    float angle = work.getFloat(0x21000000);
    float groundAngle = work.getFloat(0x21000002);
    float previousGroundAngle = work.getFloat(0x21000003);
    float stickX = controller.getStickX();
    float stickY = controller.getStickY();
    float lr = posture.getLr();
    soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(0));
    wnKineticEnergyGravity& gravity = dynamic_cast<wnKineticEnergyGravity&>(*kinetic.getEnergy(1));
    bool launch = false;
    float launchSpeed = 0.0f;
    if (work.isFlag(0x22000002)) {
        if (front || rear) {
            float difference = fabsf(angle - groundAngle);
            if (difference > param->unk48 && !work.isFlag(0x22000007)) {
                work.onFlag(0x22000007);
                launchSpeed = difference / 90.0f * param->unk50;
                launch = true;
            }
        }
        work.offFlag(0x22000002);
    } else if (touch) {
        work.offFlag(0x22000007);
        float difference = groundAngle - previousGroundAngle;
        if (difference > param->unk48) {
            launchSpeed = difference / 90.0f * param->unk50;
            launch = true;
        }
    }
    if (launch) {
        gravity.m_speedY = launchSpeed;
        gravity.enable();
        kinetic.changeKinetic(0x21, a);
        situation.setKind(Situation_Air, false);
        ground.setCorrect(soGroundShapeImpl::Correct_Air, false);
        work.offFlag(0x22000004);
        work.offFlag(0x22000005);
        work.offFlag(0x22000006);
    } else if (front || rear || touch) {
        float increase = 0.0f;
        if (rear && stickY > 0.0f) {
            increase = param->unk60 * stickY;
            if (increase > param->unk5C) increase = param->unk5C;
        }
        if (increase > param->unk64) {
            status.changeStatusRequest(3, a);
            angle += increase;
        } else {
            int stickSign = stickX < 0.0f ? -1 : 1;
            normal.m_accel = Vec2f(lr == (float)stickSign ? param->unk54 * stickX : 0.0f, 0.0f);
            if (!work.isFlag(0x2200000c) && stickX * lr >= param->unk94) {
                work.onFlag(0x2200000c);
                a->getSoundModule().playSENo3d(SndID(0x12ba), false);
            } else if (work.isFlag(0x2200000c) && fabsf(stickX) <= param->unk98)
                work.offFlag(0x2200000c);
            if (touch) {
                if (angle > groundAngle) {
                    angle -= param->unk64;
                    if (angle < groundAngle) angle = groundAngle;
                } else if (angle < groundAngle) {
                    angle += param->unk64;
                    if (angle > groundAngle) angle = groundAngle;
                }
            } else if (rear && !front) {
                angle -= param->unk64;
                if (angle < -45.0f) angle = -45.0f;
            } else if (front && !rear) {
                angle += param->unk64;
                if (angle > 45.0f) angle = 45.0f;
            }
            if (touch && 0.0f != fabsf(stickX) && lr != (float)(stickX < 0.0f ? -1 : 1))
                status.changeStatusRequest(5, a);
        }
    } else if (lr == (float)(stickX < 0.0f ? -1 : 1)) {
        angle -= param->unk4C * fabsf(stickX);
        if (angle < -45.0f) angle = -45.0f;
    } else if (fabsf(stickX) > 0.0f) {
        angle += param->unk4C * fabsf(stickX);
        if (angle > 45.0f) angle = 45.0f;
    }
    work.setFloat(angle, 0x21000000);
    float speed = normal.getSpeed().length();
    float minimum = front || rear ? param->unk14 : param->unk20;
    float maximum = front || rear ? param->unkC : param->unk18;
    float elapsed = speed - minimum;
    float range = maximum - minimum;
    if (elapsed < 0.0f) elapsed = 0.0f;
    else if (elapsed > range) elapsed = range;
    float fraction = elapsed / range;
    motion.setRate(param->unk44 + fraction * (param->unk40 - param->unk44));
}
wnWarioBikeStatusUniqProcessDrive g_wnWarioBikeStatusUniqProcessDrive;
