#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/lucas/ft_lucas_status_uniq_process_special_hi.h>
#include <ft/ft_common_data_accesser.h>
#include <so/so_module_accesser.h>
#include <so/link/so_link_module_impl.h>
#include <so/article/so_generate_article_manage_module.h>
#include <so/so_external_value_accesser.h>
#include <so/ground/so_ground_module_impl.h>
#include <mt/mt_vector.h>

// Native helper: vec2fAngle__FP5Vec2fP5Vec2f at 0x8003DDD0.
float vec2fAngle(Vec2f*, Vec2f*);
void ftLucasStatusUniqProcessSpecialHi::initStatus(soModuleAccesser* a) {
    a->getWorkManageModule().setInt(1, 0x20000003);
    // HYPOTHESIS: This observed call may lazily initialize or cache fighter data.
    g_ftCommonDataAccesser.getData(Fighter_Lucas);
}
void ftLucasStatusUniqProcessSpecialHi::execFixPosCounter(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soLinkModule& link = a->getLinkModule();
    if (!link.isLinked(6)) return;

    ftData* lucasData = g_ftCommonDataAccesser.getData(Fighter_Lucas);
    const u8* lucasParamGroup3 = static_cast<const u8*>(lucasData->extendParam[2]);
    float angleAllowance = *reinterpret_cast<const float*>(lucasParamGroup3 + 0x24);

    soPostureModule& posture = a->getPostureModule();
    soSituationModule& situation = a->getSituationModule();
    soGroundModule& ground = a->getGroundModule();

    int phase = work.getInt(0x20000003);
    work.getInt(0x20000004);
    float scale = posture.getScale();
    Vec3f fighterPos = posture.getPos();
    u32 parentNode = 0;
    Vec3f targetPos = link.getParentModelNodeGlobalPosition(6, parentNode, false);
    // The native path also queries the alternate parent model position; its
    // returned vector is not used by the observed transition logic.
    link.getParentModelNodeGlobalPosition(6, parentNode, true);

    float dx = fighterPos.m_x - targetPos.m_x;
    float dy = fighterPos.m_y + scale * 5.0f - targetPos.m_y;
    bool inAimWindow = fabsf(dx) < scale * 8.333333f &&
                       fabsf(dy) < scale * 12.333333f;

    if (phase == 1 && !inAimWindow) {
        phase = 0;
    } else if (phase == 0 && inAimWindow) {
        phase = 2;
        posture.setLr(dx < 0.0f ? -1.0f : 1.0f);
        work.setFloat(dy < 0.0f ? -1.0f : 1.0f, 0x21000005);
        work.setFloat(atan2f(dy, dx), 0x21000004);
        work.onFlag(0x22000011);

        if (situation.getKind() == Situation_Ground) {
            Vec2f groundNormal = ground.getTouchNormal(
                static_cast<grCollStatus::TouchMask>(8), 0);
            Vec2f aimDirection(dx, dy);
            groundNormal.normalize();
            aimDirection.normalize();
            float angle = vec2fAngle(&groundNormal, &aimDirection);
            if (angle < 1.5707964f) work.offFlag(0x22000011);

            // HYPOTHESIS: Lucas extend-param group 3 +0x24 is the
            // per-move angular allowance; native adds 90 degrees.
            if (angle <= (angleAllowance + 90.0f) * 0.017453292f) {
                a->getStatusModule().changeStatusRequest(0x11c, a);
            } else {
                a->getStatusModule().changeStatusRequest(0x4a, a);
            }
        } else {
            work.offFlag(0x22000011);
            a->getStatusModule().changeStatusRequest(0x11c, a);
        }
    }

    work.setInt(phase, 0x20000003);
}
void ftLucasStatusUniqProcessSpecialHi::exitStatus(soModuleAccesser* a, int nextStatus) {
    soLinkModule& link = a->getLinkModule();
    soWorkManageModule& work = a->getWorkManageModule();
    if (link.isLinked(6)) link.unlink(6);
    soGenerateArticleManageModule& articleManage = *reinterpret_cast<soGenerateArticleManageModule*>(
        const_cast<soModuleEnumeration*>(a->m_enumerationStart)->m_generateArticleManageModule);
    articleManage.removeExist(2, 0);
    work.setInt(0, 0x20000003);
    if (nextStatus == 0x10) {
        // HYPOTHESIS: This observed call may lazily initialize or cache fighter data.
        g_ftCommonDataAccesser.getData(Fighter_Lucas);
    }
}
ftLucasStatusUniqProcessSpecialHi::~ftLucasStatusUniqProcessSpecialHi() {}
ftLucasStatusUniqProcessSpecialHi g_ftLucasStatusUniqProcessSpecialHi;
