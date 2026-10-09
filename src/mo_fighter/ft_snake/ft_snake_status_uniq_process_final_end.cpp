#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/snake/ft_snake_status_uniq_process_final.h>
#include <cm/cm_camera_controller.h>
#include <cm/cm_controller_ai.h>
#include <mt/mt_vector.h>
#include <so/so_external_value_accesser.h>
#include <so/so_value_accesser.h>
#include <so/so_module_accesser.h>
#include <so/work/so_work_manage_module_impl.h>

extern cmAIController* g_cmAIController;

ftSnakeStatusUniqProcessFinalEnd g_ftSnakeStatusUniqProcessFinalEnd;

ftSnakeStatusUniqProcessFinalEnd::~ftSnakeStatusUniqProcessFinalEnd() {}

void ftSnakeStatusUniqProcessFinalEnd::initStatus(soModuleAccesser* acc) {
    acc->getWorkManageModule().setInt(
        soValueAccesser::getConstantInt(acc, 24000, 0), 0x20000002);
}

void ftSnakeStatusUniqProcessFinalEnd::execFixPosCounter(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    if (work.getInt(0x20000002) > 0)
        work.decInt(0x20000002);
}

void ftSnakeStatusUniqProcessFinalEnd::execFixPos(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    int count = work.getInt(0x20000002);
    int maximum = soValueAccesser::getConstantInt(acc, 24000, 0);
    if (count > 0 && maximum != 0)
        ftSnakeStatusUniqProcessFinalCommon::setCameraOffsetZ(
            acc, static_cast<float>(count) / static_cast<float>(maximum));
}

void ftSnakeStatusUniqProcessFinalEnd::exitStatus(soModuleAccesser* acc, int next) {
    CameraController* camera = CameraController::getInstance();
    if (camera) {
        char* fields = reinterpret_cast<char*>(camera);
        Vec3f pos((*reinterpret_cast<float*>(fields + 0x148) +
                   *reinterpret_cast<float*>(fields + 0x14C)) * 0.5f,
                  *reinterpret_cast<float*>(fields + 0x150), 0.0f);
        acc->getPostureModule().setPos(&pos);
        // Native soPhysicsModuleImpl vtable +0xE4 is sync2ndSavedPosition().
        void* physics = acc->m_enumerationStart->m_physicsModule;
        void** physicsVtable = *reinterpret_cast<void***>(
            reinterpret_cast<unsigned char*>(physics) + 8);
        reinterpret_cast<void (*)(void*)>(physicsVtable[0xE4 / 4])(physics);
        StageObject& object = acc->getStageObject();
        object.updateNodeSRT();
        object.updateRoughPos();
    }
    Vec3f zero(0.0f, 0.0f, 0.0f);
    acc->getPostureModule().setRot(&zero, 0);
    if (g_cmAIController) {
        g_cmAIController->setUserDistMin(0.0f);
        ftSnakeStatusUniqProcessFinalCommon::exitStatusCommon(acc, next);
    }
}
