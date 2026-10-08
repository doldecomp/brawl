#include <wn/wn_kinetic_energy_gravity.h>
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <so/so_kinetic_energy_normal.h>
#include <so/so_module_accesser.h>
#include <math.h>

#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE

void wnWarioBikeStatusUniqProcessAppeal::execFixPosCounter(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soKineticModule& kinetic = a->getKineticModule();
    soCollisionAttackModule& attack = a->getCollisionAttackModule();
    wnWarioBikeParam* param = dynamic_cast<wnWarioBike&>(a->getStageObject()).m_param;
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
}

void wnWarioBikeStatusUniqProcessAppeal::execFixPos(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soSituationModule& situation = a->getSituationModule();
    soGroundModule& ground = a->getGroundModule();
    soKineticModule& kinetic = a->getKineticModule();
    soPostureModule& posture = a->getPostureModule();
    wnWarioBikeParam* param = dynamic_cast<wnWarioBike&>(a->getStageObject()).m_param;

    bool frontContact = work.isFlag(0x22000004);
    bool rearContact = work.isFlag(0x22000005);
    bool groundContact = work.isFlag(0x22000006);
    bool supportTransition = work.isFlag(0x22000002);
    bool correctionActive = work.isFlag(0x22000007);
    float phase = work.getFloat(0x21000000);
    float groundPhase = work.getFloat(0x21000002);
    float targetPhase = work.getFloat(0x21000003);
    bool changeKinetic = false;
    float correctionSpeed = 0.0f;

    if (supportTransition) {
        if (frontContact || rearContact) {
            float difference = fabsf(phase - groundPhase);
            if (difference > param->unk48 && !correctionActive) {
                work.onFlag(0x22000007);
                correctionSpeed = (difference / 90.0f) * param->unk50;
                changeKinetic = true;
            }
        }
        work.offFlag(0x22000002);
    } else if (groundContact) {
        work.offFlag(0x22000007);
        float difference = groundPhase - targetPhase;
        if (difference > param->unk48) {
            correctionSpeed = (difference / 90.0f) * param->unk50;
            changeKinetic = true;
        }
    }

    if (changeKinetic) {
        wnKineticEnergyGravity& gravity =
            dynamic_cast<wnKineticEnergyGravity&>(*kinetic.getEnergy(1));
        gravity.m_speedY = correctionSpeed;
        gravity.enable();
        kinetic.changeKinetic(33, a);
        situation.setKind(Situation_Air, false);
        ground.setCorrect(soGroundShapeImpl::Correct_Air, 0);
        work.offFlag(0x22000004);
        work.offFlag(0x22000005);
        work.offFlag(0x22000006);
    } else if (frontContact || rearContact || groundContact) {
        float phaseStep = param->unk64;
        if (groundContact) {
            if (phase > groundPhase) {
                phase -= phaseStep;
                if (phase < groundPhase) phase = groundPhase;
            } else if (phase < groundPhase) {
                phase += phaseStep;
                if (phase > groundPhase) phase = groundPhase;
            }
        } else if (rearContact && !frontContact) {
            phase -= phaseStep;
            if (phase < -45.0f) phase = -45.0f;
        } else if (frontContact && !rearContact) {
            phase += phaseStep;
            if (phase > 45.0f) phase = 45.0f;
        }
    }
    work.setFloat(phase, 0x21000000);

    float minimum;
    float maximum;
    if (frontContact || rearContact) {
        minimum = param->unk14;
        maximum = param->unkC;
    } else {
        minimum = param->unk20;
        maximum = param->unk18;
    }
    soKineticEnergyNormal& normal =
        dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(0));
    float speed = normal.getSpeed().length();
    float range = maximum - minimum;
    float position = speed - minimum;
    if (position < 0.0f) position = 0.0f;
    else if (position > range) position = range;
    float blend = position / range;
    float lr = param->unk44 + blend * (param->unk40 - param->unk44);
    posture.setLr(lr);
}

wnWarioBikeStatusUniqProcessAppeal g_wnWarioBikeStatusUniqProcessAppeal;
