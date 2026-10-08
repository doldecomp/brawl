// MATCH-ONLY: retain the original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_s.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <so/article/so_generate_article_manage_module.h>

void ftWarioStatusUniqProcessSpecialSCommon::initStatus(soModuleAccesser* a) {
    if (a->getStatusModule().getStatusKind() == 0x127) {
        soLinkModule& link = a->getLinkModule();
        if (link.isLink(6)) {
            int node = a->getModelModule().getCorrectNodeId(0x130);
            link.removeModelConstraint(true);
            link.setModelConstraintPosOrt(6, node, 0, 3, false);
        }
    }
}
void ftWarioStatusUniqProcessSpecialSCommon::execFixPos(soModuleAccesser* a) {
    soPostureModule& posture = a->getPostureModule();
    soLinkModule& link = a->getLinkModule();
    if (link.isLink(6)) {
        Vec3f pos = link.getParentModelNodeGlobalPosition(6, (u32)0, false);
        float lr = link.getParentLr(6);
        posture.setPos(&pos);
        posture.setLr(lr);
        posture.updateRotYLr();
        if (link.getParentSituationKind(6) == 0)
            a->getCollisionHitModule().setMultiSituation(Situation_Ground, 0);
        else
            a->getCollisionHitModule().initMultiSituation(0);
    }
}
void ftWarioStatusUniqProcessSpecialSCommon::exitStatus(soModuleAccesser* a, int next) {
    a->getCollisionHitModule().initMultiSituation(0);
    soLinkModule& link = a->getLinkModule();
    if (!link.isLink(6)) return;
    if (next == 0x10b || next == -1) {
        a->getWorkManageModule().onFlag(0x12000041);
        static_cast<soGenerateArticleManageModule*>(a->m_enumerationStart->m_generateArticleManageModule)->removeExist(0, 0);
    } else if ((u32)(next - 0x43) <= 3) {
        soDamageLog* damage = a->getDamageModule().getDamageLog();
        ftWarioBikeSpeedEvent event(0x45a);
        event.speed = damage->m_speed;
        link.sendEventParents(6, event);
        if (link.isModelConstraint()) link.removeModelConstraint(true);
        link.unlink(6);
    } else if (next < 0x121 || next > 0x12d) {
        ftWarioBikeSpeedEvent event(0x457);
        link.sendEventParents(6, event);
        if (link.isModelConstraint()) link.removeModelConstraint(true);
        link.unlink(6);
    }
    if (a->getStatusModule().getStatusKind() == 0x129 && next == 0x124) {
        soLinkModule& link = a->getLinkModule();
        if (link.isLink(6)) {
            int node = a->getModelModule().getCorrectNodeId(0x130);
            link.removeModelConstraint(true);
            link.setModelConstraintPosOrt(6, node, 8, 3, false);
        }
    }
}
bool ftWarioStatusUniqProcessSpecialSCommon::checkDamage(soModuleAccesser* a, void* info) {
    soLinkModule& link = a->getLinkModule();
    if (!link.isLink(6)) return false;
    StageObject& fighter = a->getStageObject();
    ftWarioBikeRiderParam* param;
    if (fighter.soGetSubKind() == 0x15)
        param = dynamic_cast<ftWario&>(fighter).getExtendParam()->bikeRider;
    else
        param = dynamic_cast<ftWarioMan&>(fighter).getExtendParam()->bikeRider;
    // soDamage::m_reaction is verified at offset0xC.
    float reaction = static_cast<soDamage*>(info)->m_reaction;
    if (reaction <= param->unkC) return true;
    if (reaction < param->unk8) {
        ftWarioBikeLinkEvent event(0x459);
        link.sendEventParents(6, event);
        return true;
    }
    return false;
}
ftWarioStatusUniqProcessSpecialSCommon g_ftWarioStatusUniqProcessSpecialSCommon;
