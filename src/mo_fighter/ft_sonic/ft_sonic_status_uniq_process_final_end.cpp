// MATCH-ONLY: preserve the original instruction scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/sonic/ft_sonic_status_uniq_process_final_end.h>
#include <so/stageobject.h>
#include <so/article/so_article.h>
#include <so/article/so_generate_article_manage_module.h>
#include <so/so_module_accesser.h>
#include <so/so_external_value_accesser.h>

void ftSonicStatusUniqProcessFinalEnd::initStatus(soModuleAccesser* acc) {
    soGenerateArticleManageModule* articles = static_cast<soGenerateArticleManageModule*>(acc->m_enumerationStart->m_generateArticleManageModule);
    // Restore position and facing from Super Sonic, then try to attach to ground.
    StageObject* article = &dynamic_cast<StageObject&>(*articles->getArticle(1));
    acc->getLinkModule().removeModelConstraint(true);
    soPostureModule& posturePos = acc->getPostureModule();
    Vec3f pos = soExternalValueAccesser::getPos(article);
    posturePos.initPos(&pos);
    acc->getPostureModule().setLr(soExternalValueAccesser::getLr(article));
    acc->getPostureModule().updateRotYLr();
    acc->getStageObject().updateNodeSRT();
    if (soExternalValueAccesser::getSituationKind(article) == Situation_Ground && acc->getGroundModule().attachGround(0) == true) {
        acc->getSituationModule().setKind(Situation_Ground, false);
    } else {
        acc->getSituationModule().setKind(Situation_Air, false);
        acc->getGroundModule().setCorrect(soGroundShapeImpl::Correct_Air, 0);
    }
    static_cast<soGenerateArticleManageModule*>(acc->m_enumerationStart->m_generateArticleManageModule)->removeExist(1, 0);
}
ftSonicStatusUniqProcessFinalEnd g_ftSonicStatusUniqProcessFinalEnd;
