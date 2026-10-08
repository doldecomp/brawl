#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <cm/cm_camera_controller.h>
#include <so/article/so_generate_article_manage_module.h>
#include <so/so_module_accesser.h>
#include <ft/yoshi/ft_yoshi_final_param.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_value_accesser.h>

namespace ftyoshi { template <class T> T ABS(T); }
void ftYoshiStatusUniqProcessFinalCommon::execStatus(soModuleAccesser* acc) {
    ftData* data = g_ftCommonDataAccesser.getData(Fighter_Yoshi);
    ftYoshiFinalParam* param = static_cast<ftYoshiFinalParam*>(data->extendParam[3]);
    soKineticModule& kinetic = acc->getKineticModule();
    ftKineticEnergyStop* stop = dynamic_cast<ftKineticEnergyStop*>(kinetic.getEnergy(3));
    ftKineticEnergyGravity* gravity = dynamic_cast<ftKineticEnergyGravity*>(kinetic.getEnergy(1));
    ftKineticEnergyController* controller = dynamic_cast<ftKineticEnergyController*>(kinetic.getEnergy(2));
    Vec2f stopSpeed = stop->getSpeed();
    Vec2f gravitySpeed = gravity->getSpeed();
    Vec2f controllerSpeed = controller->getSpeed();
    float stickAngle = acc->getControllerModule().getStickAngle();
    float stickY = acc->getControllerModule().getStickY();
    int status = acc->getStatusModule().getStatusKind();
    // HYPOTHESIS: extension offsets are speed limits and animation-rate tuning values.
    if (status == 0x120 || status == 0x122) {
        if (stickAngle != 0.0f) {
            controllerSpeed.m_x += stopSpeed.m_x;
            stopSpeed.m_x = 0.0f;
            stop->disable();
        } else {
            float directedSpeed = controllerSpeed.m_x * stickAngle;
            if (directedSpeed >= 0.0f && directedSpeed <= param->unk00 && !stop->isEnable()) {
                stopSpeed.m_x = param->unk00 * stickAngle;
                controllerSpeed.m_x = 0.0f;
                stop->enable();
            }
        }
    }
    if (status >= 0x120 && status <= 0x122) {
        if (stickY != 0.0f) {
            gravitySpeed.m_y += controllerSpeed.m_y;
            controllerSpeed.m_y = 0.0f;
            gravity->disable();
        } else if (gravitySpeed.m_y > -param->unk20 && gravitySpeed.m_y <= 0.0f && !gravity->isEnable()) {
            controllerSpeed.m_y = gravitySpeed.m_y;
            gravitySpeed.m_y = 0.0f;
            gravity->enable();
        }
    }
    stop->setSpeed(&stopSpeed);
    gravity->m_speedY = gravitySpeed.m_y;
    controller->setSpeed(&controllerSpeed);
    float rate;
    if (status == 0x121 || status == 0x123) rate = 1.0f;
    else {
        rate = ftyoshi::ABS(controllerSpeed.m_y) / param->unk14;
        if (controllerSpeed.m_y > 0.0f) rate *= param->unk24 - 1.0f;
        else if (controllerSpeed.m_y < 0.0f) rate *= param->unk28 - 1.0f;
        rate += 1.0f;
    }
    acc->getMotionModule().setRate(rate);
    static_cast<soGenerateArticleManageModule*>(acc->m_enumerationStart->m_generateArticleManageModule)->setRate(2, rate);
}
void ftYoshiStatusUniqProcessFinalCommon::execFixPosCounter(soModuleAccesser* acc) {
    soKineticModule& kinetic = acc->getKineticModule();
    ftKineticEnergyGravity* gravity = dynamic_cast<ftKineticEnergyGravity*>(kinetic.getEnergy(1));
    ftKineticEnergyController* controller = dynamic_cast<ftKineticEnergyController*>(kinetic.getEnergy(2));
    Vec2f gravitySpeed = gravity->getSpeed();
    Vec2f controllerSpeed = controller->getSpeed();
    if (acc->getSituationModule().getKind() == 0) {
        soGroundModule& ground = acc->getGroundModule();
        bool attached = ground.attachGround(0);
        bool keepGravity = false;
        if (attached) {
            float threshold = soValueAccesser::getConstantFloat(acc, 0xC5F, 0);
            float stickAngle = acc->getControllerModule().getStickAngle();
            keepGravity = !(stickAngle >= threshold);
        }
        if (keepGravity) {
            // Native calls isOnDynamicCollision(8) here; its result is unused.
            ground.isOnDynamicCollision(8);
            gravity->resume();
        } else {
            if (gravitySpeed.m_y < 0.0f) gravitySpeed.m_y = 0.0f;
            if (controllerSpeed.m_y < 0.0f) controllerSpeed.m_y = 0.0f;
            gravity->suspend();
        }
    } else gravity->resume();
    gravity->m_speedY = controllerSpeed.m_y;
    controller->setSpeed(&controllerSpeed);
}

void ftYoshiStatusUniqProcessFinalCommon::execFixPos(soModuleAccesser* acc) {
    Vec3f pos = acc->getPostureModule().getPos();
    CameraController* camera = CameraController::getInstance();
    if (pos.m_x < camera->unk158) pos.m_x = camera->unk158;
    else if (pos.m_x > camera->unk15C) pos.m_x = camera->unk15C;
    if (pos.m_y < camera->unk164) pos.m_y = camera->unk164;
    else if (pos.m_y > camera->unk160) pos.m_y = camera->unk160;
    acc->getPostureModule().setPos(&pos);
}

void ftYoshiStatusUniqProcessFinalCommon::exitStatus(soModuleAccesser* acc, int nextStatus) {
    if (nextStatus == 0x116 || (nextStatus >= 0x120 && nextStatus <= 0x124)) return;

    static_cast<soGenerateArticleManageModule*>(acc->m_enumerationStart->m_generateArticleManageModule)
        ->removeExist(2, 0);
    acc->getMotionModule().changeMotion(nullptr);
    acc->getVisibilityModule().setWhole(1);
}

bool ftYoshiStatusUniqProcessFinalCommon::checkDamage(soModuleAccesser*, void*) {
    return true;
}

ftYoshiStatusUniqProcessFinalCommon g_ftYoshiStatusUniqProcessFinalCommon;