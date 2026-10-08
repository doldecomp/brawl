// MATCH-ONLY: preserve the original status instruction scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_s_drive.h>
#include <so/so_module_accesser.h>

void ftWarioStatusUniqProcessSpecialSDrive::initStatus(soModuleAccesser* moduleAccesser) {
    soMotionModule& motion = moduleAccesser->getMotionModule();
    soMotionChangeParam param;
    param.m_kind = 0x1e7;
    param.m_frame = 0.0f;
    param.m_rate = 1.0f;
    param._12 = 0;
    param._13 = 0;
    param._14 = 0;
    param._15 = 0;
    motion.changeMotionRequest(&param);
    motion.setRate(0.0f);
    ftWarioStatusUniqProcessSpecialSCommon::initStatus(moduleAccesser);
    execStatus(moduleAccesser);
}

void ftWarioStatusUniqProcessSpecialSDrive::execStatus(soModuleAccesser* moduleAccesser) {
    soMotionModule& motion = moduleAccesser->getMotionModule();
    soLinkModule& link = moduleAccesser->getLinkModule();
    // Linked parent rotation X selects the rider pose in the frozen animation.
    if (link.isLink(6)) {
        Vec3f rotation = link.getParentRot(6);
        float frame = 45.0f + rotation.m_x;
        if (frame < 0.0f) {
            frame = 0.0f;
        } else if (frame > 90.0f) {
            frame = 90.0f;
        }
        motion.setFrame(frame);
    }
}

ftWarioStatusUniqProcessSpecialSDrive g_ftWarioStatusUniqProcessSpecialSDrive;
