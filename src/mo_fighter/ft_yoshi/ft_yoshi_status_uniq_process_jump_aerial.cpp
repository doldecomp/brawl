#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi.h>
#include <so/so_module_accesser.h>
#include <ft/ft_common_data_accesser.h>
// HYPOTHESIS: grouping and names follow the aerial-jump rotation use.
struct ftYoshiJumpAerialParam { int rotationFrames; };
struct ftYoshiJumpAerialData { u8 unk0[0x8c]; ftYoshiJumpAerialParam* jumpAerial; };
void ftYoshiStatusUniqProcessJumpAerial::execStatus(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soPostureModule& posture = acc->getPostureModule();
    ftYoshiJumpAerialParam* param = reinterpret_cast<ftYoshiJumpAerialData*>(
        g_ftCommonDataAccesser.getData(Fighter_Yoshi))->jumpAerial;
    // HYPOTHESIS: 0x10000041 is the remaining rotation-frame countdown.
    if (work.getInt(0x10000041) > 0) {
        work.decInt(0x10000041);
        Vec3f rotation = posture.getRot(0);
        rotation.m_y -= 180.0f / param->rotationFrames;
        posture.setRot(&rotation, 0);
        if (param->rotationFrames / 2 == work.getInt(0x10000041)) posture.reverseLr();
    }
}
void ftYoshiStatusUniqProcessJumpAerial::exitStatus(soModuleAccesser* acc, int) {
    Vec3f rotation(0.0f, 0.0f, 0.0f);
    acc->getPostureModule().setRot(&rotation, 0);
}
ftYoshiStatusUniqProcessJumpAerial g_ftYoshiStatusUniqProcessJumpAerial;
