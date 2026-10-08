#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/lucas/ft_lucas_status_uniq_process_special_hi.h>
#include <so/model/so_model_module_impl.h>
#include <so/so_module_accesser.h>
#include <so/stageobject.h>

void ftLucasStatusUniqProcessSpecialHiAttackEnd::initStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soStatusModule& status = a->getStatusModule();
    soModelModuleImpl& model = dynamic_cast<soModelModuleImpl&>(a->getModelModule());
    float angle = work.getFloat(0x21000004);
    if (status.getStatusKind() == 0x11e) angle = -angle;
    model.setNodeRotateX(3, angle * 57.29578f);
    a->getStageObject().updateNodeSRT();
}

void ftLucasStatusUniqProcessSpecialHiAttackEnd::execStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soStatusModule& status = a->getStatusModule();
    soModelModuleImpl& model = dynamic_cast<soModelModuleImpl&>(a->getModelModule());
    float angle = work.getFloat(0x21000004);
    float step = work.getFloat(0x21000006);
    if (angle <= 0.0f) {
        angle += step;
        if (angle > 0.0f) angle = 0.0f;
    } else {
        angle -= step;
        if (angle < 0.0f) angle = 0.0f;
    }
    work.setFloat(angle, 0x21000004);
    if (status.getStatusKind() == 0x11e) angle = -angle;
    model.setNodeRotateX(3, angle * 57.29578f);
}

void ftLucasStatusUniqProcessSpecialHiAttackEnd::exitStatus(soModuleAccesser* a, int) {
    soModelModuleImpl& model = dynamic_cast<soModelModuleImpl&>(a->getModelModule());
    model.setNodeRotateX(3, 0.0f);
    soPostureModule& posture = a->getPostureModule();
    Vec3f zero(0.0f, 0.0f, 0.0f);
    posture.setRot(&zero, 0);
}

ftLucasStatusUniqProcessSpecialHiAttackEnd::~ftLucasStatusUniqProcessSpecialHiAttackEnd() {}
ftLucasStatusUniqProcessSpecialHiAttackEnd g_ftLucasStatusUniqProcessSpecialHiAttackEnd;
