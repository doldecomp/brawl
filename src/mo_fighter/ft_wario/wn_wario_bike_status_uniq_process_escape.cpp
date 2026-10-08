#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <so/so_module_accesser.h>
#include <so/so_kinetic_energy_normal.h>
#include <math.h>

void wnWarioBikeStatusUniqProcessEscape::execFixPos(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soPostureModule& posture = a->getPostureModule();
    float angle = work.getFloat(0x21000000);
    wnWarioBikeParam* param = dynamic_cast<wnWarioBike&>(a->getStageObject()).m_param;
    float speedX = a->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)).m_x;
    float lr = posture.getLr();
    bool speedInRange = (lr == 1.0f) ? speedX <= param->unk8C : speedX >= -param->unk8C;
    bool front = work.isFlag(0x22000004);
    bool rear = work.isFlag(0x22000005);
    bool groundTouch = work.isFlag(0x22000006);
    if (speedInRange && (front || rear || groundTouch)) {
        a->getStatusModule().changeStatus(11, a);
    }

    if (groundTouch) {
        float groundAngle = work.getFloat(0x21000002);
        float step = param->unk64;
        if (angle > groundAngle) {
            angle -= step;
            if (angle < groundAngle) angle = groundAngle;
        } else if (angle < groundAngle) {
            angle += step;
            if (angle > groundAngle) angle = groundAngle;
        }
    } else {
        float step = param->unk64;
        if (rear && !front) {
            angle -= step;
        } else if (front && !rear) {
            angle += step;
        } else {
            a->getStatusModule().changeStatus(13, a);
        }
    }
    work.setFloat(angle, 0x21000000);
}

wnWarioBikeStatusUniqProcessEscape g_wnWarioBikeStatusUniqProcessEscape;
