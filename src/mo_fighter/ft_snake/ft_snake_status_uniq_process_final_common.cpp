#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/snake/ft_snake_status_uniq_process_final.h>
#include <cm/cm_camera_controller.h>
#include <cm/cm_controller_ai.h>
#include <ft/ft_manager.h>
#include <ft/ft_owner.h>
#include <gf/gf_camera.h>
#include <nw4r/g3d/g3d_scnobj.h>
#include <so/effect/so_effect_module_impl.h>
#include <so/so_module_accesser.h>
#include <so/so_photo_call_back.h>
#include <so/so_value_accesser.h>
#include <math.h>
extern cmAIController* g_cmAIController;
extern char g_soWorld[];
extern char lbl_122_data_774[], lbl_122_data_8C98[];
extern "C" void* __dynamic_cast(void*, int, void*, void*, int);
nw4r::g3d::ScnObj* ftSnakeStatusUniqProcessFinalCommon::getStatusNodeZero(
    soModuleAccesser* acc) {
    void* model = acc->m_enumerationStart->m_modelModule;
    void** vtable = *reinterpret_cast<void***>(
        reinterpret_cast<unsigned char*>(model) + 8);
    typedef void* (*GetNode)(void*, int);
    return static_cast<nw4r::g3d::ScnObj*>(
        reinterpret_cast<GetNode>(vtable[0x40 / 4])(model, 0));
}

void ftSnakeStatusUniqProcessFinalCommon::selectCameraInput(
    soModuleAccesser* acc, int input) {
    void* model = acc->m_enumerationStart->m_modelModule;
    void** vtable = *reinterpret_cast<void***>(
        reinterpret_cast<unsigned char*>(model) + 8);
    reinterpret_cast<void (*)(void*, int)>(
        vtable[0x50 / 4])(model, input);
}

void ftSnakeStatusUniqProcessFinalCommon::setModelSecondaryValue(
    soModuleAccesser* acc, float value) {
    void* model = acc->m_enumerationStart->m_modelModule;
    void** vtable = *reinterpret_cast<void***>(
        reinterpret_cast<unsigned char*>(model) + 8);
    reinterpret_cast<void (*)(void*, float)>(
        vtable[0xE8 / 4])(model, value);
}

void ftSnakeStatusUniqProcessFinalCommon::setCameraOffsetZ(
    soModuleAccesser* acc, float scale) {
    CameraController* controller = CameraController::getInstance();
    gfCamera* camera = controller->getCameraInternal();
    if (g_cmAIController || camera) {
        float value = soValueAccesser::getConstantFloat(acc, 0xFB1, 0) * scale;
        float tangent = tanf(camera->unkD0);
        float correction = tangent > 0.0f
            ? tanf(30.0f * 0.017453292f) / tangent : 1.0f;
        g_cmAIController->setUserDistMin(value * correction);
    }
}
void ftSnakeStatusUniqProcessFinalCommon::exitStatusCommon(
    soModuleAccesser* acc, int next) {
    if (next >= 0x131 && next <= 0x132) return;
    nw4r::g3d::ScnObj* node =
        ftSnakeStatusUniqProcessFinalCommon::getStatusNodeZero(acc);
    if (node)
        node->SetPriorityDrawOpa(acc->getWorkManageModule().getInt(0x10000041));
    int ownerId = acc->getWorkManageModule().getInt(0x10000000);
    ftOwner* owner = ftManager::getInstance()->getOwner(ownerId);
    ftSnakeStatusUniqProcessFinalCommon::selectCameraInput(
        acc, owner->getSpycloak() ? 5 : 1);
    void* snake = __dynamic_cast(&acc->getStageObject(), 0x3C,
        lbl_122_data_774, lbl_122_data_8C98, 0);
    if (snake) {
        reinterpret_cast<soPhotoCallBack*>(
            reinterpret_cast<unsigned char*>(snake) + 0x2D020)->removeCallBack();
        ftSnakeStatusUniqProcessFinalCommon::setModelSecondaryValue(
            acc, *reinterpret_cast<float*>(g_soWorld + 8));
        acc->getEffectModule().setShieldEffect(0);
    }
}
