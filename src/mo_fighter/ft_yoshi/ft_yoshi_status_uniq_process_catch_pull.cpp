#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi.h>
#include <ft/ft_common_data_accesser.h>
#include <so/so_module_accesser.h>
#include <so/catch/so_catch_module.h>
// HYPOTHESIS: original record names are unknown; ranges and frame remapping are verified.
struct ftYoshiCatchFrameMap { float startFrame, endFrame; float* frames; };
struct ftYoshiCatchData {
    u8 unk0[0xa4];
    ftYoshiCatchFrameMap* standing;
    ftYoshiCatchFrameMap* dash;
    ftYoshiCatchFrameMap* turn;
};
void ftYoshiStatusUniqProcessCatchPull::initStatus(soModuleAccesser* acc) {
    ftStatusUniqProcessCatchPull::initStatus(acc);
    ftYoshiCatchData* data = reinterpret_cast<ftYoshiCatchData*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi));
    ftYoshiCatchFrameMap* map;
    int motion;
    switch (acc->getStatusModule().getPrevStatusKind(0)) {
    case Fighter::Status::Catch: map = data->standing; motion = 0x6c; break;
    case Fighter::Status::Catch_Dash: map = data->dash; motion = 0x6d; break;
    case Fighter::Status::Catch_Turn: map = data->turn; motion = 0x6e; break;
    default: return;
    }
    float frame = acc->getMotionModule().getFrame();
    if (frame >= map->startFrame && frame <= map->endFrame) {
        int index = frame - map->startFrame;
        frame = map->frames[index];
    }
    soMotionChangeParam param;
    param.m_kind = motion; param.m_frame = frame; param.m_rate = 1.0f;
    param._12 = 0; param._13 = 0; param._14 = 1; param._15 = 0;
    acc->getMotionModule().changeMotionRequest(&param);
    static_cast<soSlopeModule*>(acc->m_enumerationStart->m_slopeModule)->updateModelTopAngle();
}
void ftYoshiStatusUniqProcessCatchPull::exitStatus(soModuleAccesser* acc, int nextStatus) {
    switch (nextStatus) {
    case Fighter::Status::Catch_Wait: {
        // HYPOTHESIS: event0x452 informs the grabbed fighter about catch completion.
        struct CatchEvent : soLinkEventArgs { CatchEvent() : soLinkEventArgs(0x452) {} } event;
        acc->getLinkModule().sendEventNodes(0, event, 0);
        break;
    }
    default: {
        static_cast<soCatchModule*>(acc->m_enumerationStart->m_catchModule)->catchCut(false, false);
        break;
    }
    }
}
ftYoshiStatusUniqProcessCatchPull g_ftYoshiStatusUniqProcessCatchPull;
