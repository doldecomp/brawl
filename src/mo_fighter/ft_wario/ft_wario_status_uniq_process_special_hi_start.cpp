// MATCH-ONLY: retain the original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_hi.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <math.h>

void ftWarioStatusUniqProcessSpecialHiStart::initStatus(soModuleAccesser* a) {
    soKineticModule& kinetic = a->getKineticModule();
    soSituationModule& situation = a->getSituationModule();
    StageObject& fighter = a->getStageObject();
    ftWarioSpecialHiParam* param;
    if (fighter.soGetSubKind() == 0x15) {
        ftWario& wario = dynamic_cast<ftWario&>(fighter);
        param = wario.getExtendParam()->specialHi;
    } else {
        ftWarioMan& wario = dynamic_cast<ftWarioMan&>(fighter);
        param = wario.getExtendParam()->specialHi;
    }
    if (situation.getKind() == Situation_Ground) kinetic.changeKinetic(6, a);
    else kinetic.changeKinetic(10, a);
    ftKineticEnergyStop& horizontal = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
    Vec2f speed = horizontal.getSpeed();
    speed.m_x *= param->unk0;
    horizontal.m_speed = speed;
    speed = gravity.getSpeed();
    speed.m_y += param->unk4;
    gravity.m_speedY = speed.m_y;
    gravity.m_gravity = param->unk8;
}
void ftWarioStatusUniqProcessSpecialHiStart::exitStatus(soModuleAccesser* a, int next) {
    if (next == 0x12e) {
        soControllerModule& controller = a->getControllerModule();
        soPostureModule& posture = a->getPostureModule();
        StageObject& fighter = a->getStageObject();
        ftWarioSpecialHiParam* param;
        if (fighter.soGetSubKind() == 0x15) {
            ftWario& wario = dynamic_cast<ftWario&>(fighter);
            param = wario.getExtendParam()->specialHi;
        } else {
            ftWarioMan& wario = dynamic_cast<ftWarioMan&>(fighter);
            param = wario.getExtendParam()->specialHi;
        }
        float lr = posture.getLr();
        float stick = controller.getStickX();
        if (__fabs(stick) >= param->unkC) {
            float stickSign = (float)(stick < 0.0f ? -1 : 1);
            float lrSign = (float)(lr < 0.0f ? -1 : 1);
            if (lrSign != stickSign) posture.reverseLr();
        }
    }
}
ftWarioStatusUniqProcessSpecialHiStart g_ftWarioStatusUniqProcessSpecialHiStart;
