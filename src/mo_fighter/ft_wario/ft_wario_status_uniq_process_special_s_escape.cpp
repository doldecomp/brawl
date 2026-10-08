// MATCH-ONLY: retain the original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_s.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

void ftWarioStatusUniqProcessSpecialSEscape::execFixPosCounter(soModuleAccesser* a) {
    // MATCH-ONLY: declaration order preserves native module and vector allocation.
    soGroundModule* ground;
    soWorkManageModule* work = &a->getWorkManageModule();
    soSituationModule* situation = &a->getSituationModule();
    ground = &a->getGroundModule();
    soKineticModule* kinetic = &a->getKineticModule();
    soPostureModule* posture = &a->getPostureModule();
    soModelModule* model = &a->getModelModule();
    soLinkModule* link = &a->getLinkModule();
    StageObject* fighter = &a->getStageObject();
    ftWarioBikeRiderParam* param;
    if (fighter->soGetSubKind() == 0x15) {
        ftWario& wario = dynamic_cast<ftWario&>(*fighter);
        param = wario.getExtendParam()->bikeRider;
    } else {
        ftWarioMan& wario = dynamic_cast<ftWarioMan&>(*fighter);
        param = wario.getExtendParam()->bikeRider;
    }
    if (work->isFlag(0x22000011)) {
        float lr = posture->getLr();
        int node = model->getCorrectNodeId(0x12d);
        Vec3f nodePos = model->getNodeGlobalOffsetFromTop(node);
        Vec3f pos;
        Vec3f posturePos = posture->getPos();
        Vec3fAdd(&pos, &posturePos, &nodePos);
        Vec2f speed(param->unk10 * lr, param->unk14);
        float angle = 0.0f;
        pos.m_z = 0.0f;
        posture->setPos(&pos);
        if (link->isLink(6)) {
            ftWarioBikeSpeedEvent event(0x457);
            link->sendEventParents(6, event);
            Vec3f rot = link->getParentRot(6);
            float parentAngleX = rot.m_x;
            angle = parentAngleX * 0.5f;
            link->removeModelConstraint(true);
            link->unlink(6);
            a->getSituationModule().setKind(Situation_Air, false);
        }
        speed.rot(&speed, 0.017453292f * (-angle * lr));
        a->getStageObject().updateNodeSRT();
        ftKineticEnergyStop& horizontal = dynamic_cast<ftKineticEnergyStop&>(*kinetic->getEnergy(3));
        ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic->getEnergy(1));
        kinetic->changeKinetic(10, a);
        horizontal.m_speed = Vec2f(speed.m_x, 0.0f);
        gravity.m_speedY = speed.m_y;
        situation->setKind(Situation_Air, false);
        ground->setCorrect((soGroundShapeImpl::CorrectKind)5, 0);
        work->offFlag(0x22000011);
    }
}
ftWarioStatusUniqProcessSpecialSEscape g_ftWarioStatusUniqProcessSpecialSEscape;
