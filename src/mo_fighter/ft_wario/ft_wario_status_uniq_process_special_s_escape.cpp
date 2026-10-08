// MATCH-ONLY: retain the original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_s.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

void ftWarioStatusUniqProcessSpecialSEscape::execFixPosCounter(soModuleAccesser* a) {
    ftWarioBikeRiderParam* param;
    soWorkManageModule* work = &a->getWorkManageModule();
    soSituationModule* situation = &a->getSituationModule();
    soGroundModule* ground = &a->getGroundModule();
    soKineticModule* kinetic = &a->getKineticModule();
    soPostureModule* posture = &a->getPostureModule();
    soModelModule* model = &a->getModelModule();
    soLinkModule* link = &a->getLinkModule();
    StageObject* fighter = &a->getStageObject();
    if (fighter->soGetSubKind() == 0x15)
        param = dynamic_cast<ftWario&>(*fighter).getExtendParam()->bikeRider;
    else
        param = dynamic_cast<ftWarioMan&>(*fighter).getExtendParam()->bikeRider;
    if (work->isFlag(0x22000011)) {
        float lr = posture->getLr();
        int node = model->getCorrectNodeId(0x12d);
        Vec3f nodePos = model->getNodeGlobalOffsetFromTop(node);
        Vec3f posturePos = posture->getPos();
        Vec3f pos;
        Vec3fAdd(&pos, &posturePos, &nodePos);
        Vec2f speed(param->unk10 * lr, param->unk14);
        float angle = 0.0f;
        pos.m_z = 0.0f;
        posture->setPos(&pos);
        if (link->isLink(6)) {
            ftWarioBikeSpeedEvent event(0x457);
            link->sendEventParents(6, event);
            Vec3f rot = link->getParentRot(6);
            angle = rot.m_x * 0.5f;
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
