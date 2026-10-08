// MATCH-ONLY: retain original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_lw.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

void ftWarioStatusUniqProcessSpecialLw::initStatus(soModuleAccesser* a) {
    soCollisionAttackModule& attacks = a->getCollisionAttackModule();
    soWorkManageModule& work = a->getWorkManageModule();
    StageObject& fighter = a->getStageObject();
    ftWarioSpecialLwParam* param;
    if (fighter.soGetSubKind() == 0x15) {
        ftWario& wario = dynamic_cast<ftWario&>(fighter);
        param = wario.getExtendParam()->specialLw;
    } else {
        ftWarioMan& wario = dynamic_cast<ftWarioMan&>(fighter);
        param = wario.getExtendParam()->specialLw;
    }
    int frames = work.getInt(0x10000041);
    int level = work.getInt(0x10000042);
    if (level == 2) {
        // MATCH-ONLY: this declaration order retains the native integer registers.
        int minimum;
        int maximum = param->unk0;
        if (frames > maximum * 60) frames = maximum * 60;
        minimum = param->unk8;
        frames -= minimum * 60;
        float range = (float)(maximum - minimum);
        float multiplier = (float)frames;
        multiplier /= 60.0f * range;
        multiplier = 1.0f + (param->unk10 - 1.0f) * multiplier;
        attacks.setPowerMul(multiplier);
    } else if (level == 1) {
        // MATCH-ONLY: this declaration order retains the native integer registers.
        int minimum;
        int maximum = param->unk8;
        if (frames > maximum * 60) frames = maximum * 60;
        minimum = param->unk4;
        frames -= minimum * 60;
        float range = (float)(maximum - minimum);
        float multiplier = (float)frames;
        multiplier /= 60.0f * range;
        multiplier = 1.0f + (param->unkC - 1.0f) * multiplier;
        attacks.setPowerMul(multiplier);
    } else {
        attacks.setPowerMul(1.0f);
    }
}
void ftWarioStatusUniqProcessSpecialLw::execStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soSituationModule& situation = a->getSituationModule();
    soGroundModule& ground = a->getGroundModule();
    soKineticModule& kinetic = a->getKineticModule();
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
    StageObject& fighter = a->getStageObject();
    ftWarioSpecialLwParam* param;
    if (fighter.soGetSubKind() == 0x15) {
        ftWario& wario = dynamic_cast<ftWario&>(fighter);
        param = wario.getExtendParam()->specialLw;
    } else {
        ftWarioMan& wario = dynamic_cast<ftWarioMan&>(fighter);
        param = wario.getExtendParam()->specialLw;
    }
    int frames = work.getInt(0x10000041);
    int level = work.getInt(0x10000042);
    if (work.isFlag(0x22000011)) {
        if (level >= 2) {
            float speedY;
            if (level == 2) {
                int maximum = param->unk0;
                if (frames > maximum * 60) frames = maximum * 60;
                int minimum = param->unk8;
                frames -= minimum * 60;
                if (frames < 0) frames = 0;
                float range = (float)(maximum - minimum);
                float elapsed = (float)frames;
                float fraction = elapsed / (60.0f * range);
                speedY = param->unk14 + fraction * (param->unk18 - param->unk14);
            } else {
                speedY = param->unk1C;
            }
            situation.setKind(Situation_Air, false);
            ground.setCorrect(soGroundShapeImpl::Correct_Air, false);
            kinetic.changeKinetic(0xA, a);
            gravity.m_speedY = speedY;
        }
        work.offFlag(0x22000011);
        work.onFlag(0x22000012);
    }
}
void ftWarioStatusUniqProcessSpecialLw::exitStatus(soModuleAccesser* a, int) {
    soCollisionAttackModule& attacks = a->getCollisionAttackModule();
    soWorkManageModule& work = a->getWorkManageModule();
    work.setInt(0, 0x10000041);
    work.setInt(0, 0x10000042);
    attacks.setPowerMul(1.0f);
    work.offFlag(0x1200003F);
    a->getEffectModule().removeCommon(0x27);
}
ftWarioStatusUniqProcessSpecialLw g_ftWarioStatusUniqProcessSpecialLw;
