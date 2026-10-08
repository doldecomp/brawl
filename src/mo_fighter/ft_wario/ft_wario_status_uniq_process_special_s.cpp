// MATCH-ONLY: retain the original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_s.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

#include <so/article/so_generate_article_manage_module.h>
#include <so/so_external_value_accesser.h>
#include <it/item.h>
void ftWarioStatusUniqProcessSpecialS::initStatus(soModuleAccesser* a) {
    ftWarioBikeRiderParam* param;
    const soModuleEnumeration* modules = a->m_enumerationStart;
    soGenerateArticleManageModule* articles = static_cast<soGenerateArticleManageModule*>(modules->m_generateArticleManageModule);
    soItemManageModule* items = modules->m_itemManageModule;
    soWorkManageModule* work = modules->m_workManageModule;
    soStatusModule* status = modules->m_statusModule;
    soLinkModule* link = modules->m_linkModule;
    StageObject* fighter = &a->getStageObject();
    if (fighter->soGetSubKind() == 0x15)
        param = dynamic_cast<ftWario&>(*fighter).getExtendParam()->bikeRider;
    else
        param = dynamic_cast<ftWarioMan&>(*fighter).getExtendParam()->bikeRider;
    if (items->getPickableItemKind() == 0x5c) {
        soItemInfo item;
        items->getPickableItemInfo(&item);
        BaseItem* bikeItem = item.m_item;
        soLinkModule* itemLink = soExternalValueAccesser::getLinkModule(static_cast<StageObject*>(bikeItem));
        if (itemLink->isLinked(7)) {
            work->setInt(itemLink->getNodeTaskId(7), 0x10000044);
            ftWarioBikeTaskEvent event(0x45c, fighter->m_taskId);
            itemLink->sendEventNodes(7, event, 0);
        }
        items->removeItem(bikeItem);
        status->changeStatusRequest(0x123, a);
    } else if (link->isLink(7)) {
        status->changeStatusRequest(0x122, a);
    } else if (work->getInt(0x10000043) < param->unk18) {
        status->changeStatusRequest(0x122, a);
    } else if (articles->isExist(0) == true) {
        status->changeStatusRequest(0x122, a);
    } else {
        work->setInt(0, 0x10000043);
        work->setInt(fighter->m_taskId, 0x10000044);
        status->changeStatusRequest(0x121, a);
    }
    work->offFlag(0x12000041);
}
ftWarioStatusUniqProcessSpecialS g_ftWarioStatusUniqProcessSpecialS;

// MATCH-ONLY: these shared base callbacks retain their original module-local ownership.
void soStatusUniqProcess::initStatus(soModuleAccesser*) {  }
void soStatusUniqProcess::exitStatus(soModuleAccesser*, int) {  }
void soStatusUniqProcess::execStatus(soModuleAccesser*) {  }
void soStatusUniqProcess::execFixPos(soModuleAccesser*) {  }
bool soStatusUniqProcess::checkDamage(soModuleAccesser*, void*) { return false; }
void soStatusUniqProcess::execStop(soModuleAccesser*) {  }
void soStatusUniqProcess::execMapCorrection(soModuleAccesser*) {  }
void soStatusUniqProcess::execFixPosCounter(soModuleAccesser*) {  }
void soStatusUniqProcess::execFixCamera(soModuleAccesser*) {  }
void soStatusUniqProcess::checkAttack(soModuleAccesser*, void*, float) {  }
bool soStatusUniqProcess::onChangeLr(soModuleAccesser*, float, float) { return false; }
void soStatusUniqProcess::leaveStop(soModuleAccesser*, int, bool) {  }
bool soStatusUniqProcess::checkTransitionPrecede(soModuleAccesser*, void*, int) { return true; }
