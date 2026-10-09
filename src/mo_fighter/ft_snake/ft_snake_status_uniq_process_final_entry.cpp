#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/snake/ft_snake_status_uniq_process_final.h>
#include <nw4r/g3d/g3d_scnobj.h>
#include <so/so_module_accesser.h>
#include <so/so_photo_call_back.h>
#include <so/so_value_accesser.h>
#include <so/posture/so_posture_module_impl.h>
#include <so/work/so_work_manage_module_impl.h>
extern char lbl_122_data_774[], lbl_122_data_8C98[];
extern "C" void* __dynamic_cast(void*, int, void*, void*, int);

ftSnakeStatusUniqProcessFinalEntry g_ftSnakeStatusUniqProcessFinalEntry;
ftSnakeStatusUniqProcessFinalEntry::~ftSnakeStatusUniqProcessFinalEntry() {}
void ftSnakeStatusUniqProcessFinalEntry::initStatus(soModuleAccesser* acc) {
    acc->getPostureModule().setScale(1.0f);
    void* snake = __dynamic_cast(&acc->getStageObject(), 0x3C,
        lbl_122_data_774, lbl_122_data_8C98, 0);
    if (snake) {
        reinterpret_cast<soPhotoCallBack*>(
            reinterpret_cast<unsigned char*>(snake) + 0x2D020)->addCallback();
        ftSnakeStatusUniqProcessFinalCommon::setModelSecondaryValue(acc, 1.0f);
        acc->getEffectModule().setShieldEffect(1);
        nw4r::g3d::ScnObj* node =
            ftSnakeStatusUniqProcessFinalCommon::getStatusNodeZero(acc);
        if (node) {
            int* savedPriority = reinterpret_cast<int*>(
                reinterpret_cast<unsigned char*>(node) + 0xD0);
            acc->getWorkManageModule().setInt(*savedPriority, 0x10000041);
            node->SetPriorityDrawOpa(0xFF);
        }
        ftSnakeStatusUniqProcessFinalCommon::selectCameraInput(acc, 5);
    }
}
void ftSnakeStatusUniqProcessFinalEntry::execFixPosCounter(soModuleAccesser* acc) {
    acc->getWorkManageModule().incInt(0x20000002);
}
void ftSnakeStatusUniqProcessFinalEntry::execFixPos(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    int maximum = soValueAccesser::getConstantInt(acc, 24000, 0);
    int count = work.getInt(0x20000002);
    if (count <= maximum && maximum != 0)
        ftSnakeStatusUniqProcessFinalCommon::setCameraOffsetZ(
            acc, static_cast<float>(count) / static_cast<float>(maximum));
}
void ftSnakeStatusUniqProcessFinalEntry::exitStatus(soModuleAccesser* acc, int next) {
    ftSnakeStatusUniqProcessFinalCommon::exitStatusCommon(acc, next);
}
