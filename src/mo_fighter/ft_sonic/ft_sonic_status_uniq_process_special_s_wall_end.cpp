// MATCH-ONLY: preserve the instruction order of this status process.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/sonic/ft_sonic_status_uniq_process_special_s_wall_end.h>
#include <ft/ft_util.h>
#include <so/so_module_accesser.h>

void ftSonicStatusUniqProcessSpecialSWallEnd::initStatus(soModuleAccesser* moduleAccesser) {
    // Motion IDs identify the two wall-contact exit animations; original names are unavailable.
    if (moduleAccesser->getGroundModule().isTouch(grCollStatus::TOUCH_MASK_RIGHT, 0) == true) {
        soMotionChangeParam motion(0x1db, 0.0f, 1.0f, 0, 0, 0, 0);
        moduleAccesser->getMotionModule().changeMotionRequest(&motion);
    } else {
        soMotionChangeParam motion(0x1dc, 0.0f, 1.0f, 0, 0, 0, 0);
        moduleAccesser->getMotionModule().changeMotionRequest(&motion);
    }
    float lr = moduleAccesser->getPostureModule().getLr();
    ftUtil::adjustWall(moduleAccesser, lr, -lr, 1.0f, 1);
}
ftSonicStatusUniqProcessSpecialSWallEnd g_ftSonicStatusUniqProcessSpecialSWallEnd;
