// MATCH-ONLY: retain the original instruction scheduling and out-of-line helpers.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/sonic/ft_sonic_status_uniq_process_special_s_dash.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/controller/so_controller_impl.h>
#include <math.h>
#include <so/templates/so_array_value_soTransitionTermPack.h>

// These weak callbacks belong to Sonic's dash translation unit in this REL.
#pragma force_active on
inline bool soStatusUniqProcess::checkTransitionPrecede(soModuleAccesser*, void*, int) { return true; }
inline void soStatusUniqProcess::leaveStop(soModuleAccesser*, int, bool) {}
inline bool soStatusUniqProcess::onChangeLr(soModuleAccesser*, float, float) { return false; }
inline void soStatusUniqProcess::checkAttack(soModuleAccesser*, void*, float) {}
inline bool soStatusUniqProcess::checkDamage(soModuleAccesser*, void*) { return false; }
inline void soStatusUniqProcess::execFixCamera(soModuleAccesser*) {}
inline void soStatusUniqProcess::execFixPosCounter(soModuleAccesser*) {}
inline void soStatusUniqProcess::execMapCorrection(soModuleAccesser*) {}
inline void soStatusUniqProcess::execStop(soModuleAccesser*) {}
inline void soStatusUniqProcess::exitStatus(soModuleAccesser*, int) {}
__declspec(weak) void soStatusUniqProcess::execFixPos(soModuleAccesser*) {}
__declspec(weak) void soStatusUniqProcess::execStatus(soModuleAccesser*) {}
#pragma force_active reset

void ftSonicStatusUniqProcessSpecialSDash::initStatus(soModuleAccesser* acc) {
    if (acc->getStatusModule().getPrevStatusKind(0) != 0x120) {
        acc->getWorkManageModule().setInt(soValueAccesser::getConstantInt(acc, 0x5dc8, 0), 0x20000003);
    }
    if (acc->getStatusModule().getPrevStatusKind(0) != 0x124 &&
        acc->getStatusModule().getPrevStatusKind(0) != 0x120) {
        acc->getWorkManageModule().onFlag(0x22000012);
    } else {
        processChangeGroundMotion(acc);
        processChangeGroundCorrect(acc);
        syncSpeedMotionRate(acc);
    }
}
void ftSonicStatusUniqProcessSpecialSDash::execStatus(soModuleAccesser* acc) {
    if (!acc->getWorkManageModule().isFlag(0x22000012)) {
        processCheckAttack(acc);
    }
    acc->getWorkManageModule().onFlag(0x22000013);
}
void ftSonicStatusUniqProcessSpecialSDash::execFixPos(soModuleAccesser* acc) {
    syncSpeedAttackPower(acc);
    processChangeGroundMotion(acc);
    processChangeGroundCorrect(acc);
    syncSpeedMotionRate(acc);
}
void ftSonicStatusUniqProcessSpecialSDash::processChangeGroundMotion(soModuleAccesser* acc) {
    if (acc->getSituationModule().getKind() != 0) return;
    acc->getWorkManageModule().offFlag(0x22000012);
    if (acc->getMotionModule().getKind() == 0x1d9 || acc->getMotionModule().getKind() == 0x1e4) {
        soWorkManageModule& work = acc->getWorkManageModule();
        float limit = soValueAccesser::getConstantFloat(acc, 0xfbe, 0);
        if (work.getFloat(0x21000004) > limit) {
            soMotionChangeParam param(0x1d8, 0.0f, 1.0f, 0, 0, 0, 0);
            acc->getMotionModule().changeMotionRequest(&param);
            acc->getGroundModule().setCorrect(soGroundShapeImpl::Correct_Ground, 0);
            addGroundMotionTransitionTerm(acc);
        }
    } else {
        soWorkManageModule& work = acc->getWorkManageModule();
        float limit = soValueAccesser::getConstantFloat(acc, 0xfbe, 0);
        if (work.getFloat(0x21000004) <= limit) {
            soMotionChangeParam param(0x1d9, 0.0f, 1.0f, 0, 0, 0, 0);
            acc->getMotionModule().changeMotionRequest(&param);
            addGroundMotionTransitionTerm(acc);
        }
    }
}
#pragma dont_inline on
soMotionChangeParam::soMotionChangeParam(int kind, float frame, float rate, u8 a, u8 b, u8 c, u8 d) :
    m_kind(kind), m_frame(frame), m_rate(rate), _12(a), _13(b), _14(c), _15(d) {}
#pragma dont_inline reset

void ftSonicStatusUniqProcessSpecialSDash::addGroundMotionTransitionTerm(soModuleAccesser* acc) {
    static const acCmdArgConv argument = {6, 4};
    soTransitionTermPack term = {-1, acCmdArgList(&argument, 1)};
    acc->getMotionModule().addTransitionTerm(&term, 1, 0);
}
void ftSonicStatusUniqProcessSpecialSDash::processChangeGroundCorrect(soModuleAccesser* acc) {
    if (acc->getSituationModule().getKind() != 0) return;
    switch (acc->getMotionModule().getKind()) {
    case 0x1d9: break;
    default: return;
    }
    int direction = acc->getPostureModule().getLr() < 0.0f ? -1 : 1;
    float sign = direction;
    soControllerModule& controller = acc->getControllerModule();
    float threshold = soValueAccesser::getConstantFloat(acc, 0xc5c, 0);
    float stick = controller.getStickX();
    stick *= sign;
    if (stick <= threshold) {
        acc->getGroundModule().setCorrect(soGroundShapeImpl::Correct_Ground_Cliff_Stop, 0);
    } else {
        acc->getGroundModule().setCorrect(soGroundShapeImpl::Correct_Ground, 0);
    }
}
void ftSonicStatusUniqProcessSpecialSDash::syncSpeedMotionRate(soModuleAccesser* acc) {
    if (acc->getMotionModule().getKind() != 0x1d9) return;
    float ratio;
    if (acc->getSituationModule().getKind() == 0) {
        double magnitude = __fabs(acc->getWorkManageModule().getFloat(0x21000004));
        ratio = magnitude;
        ratio /= soValueAccesser::getConstantFloat(acc, 0xfbe, 0);
    } else {
        double magnitude = __fabs(acc->getWorkManageModule().getFloat(0x21000005));
        ratio = magnitude;
        ratio /= soValueAccesser::getConstantFloat(acc, 0xfbe, 0);
    }
    if (ratio < 0.0f) ratio = 0.0f;
    else if (ratio > 1.0f) ratio = 1.0f;
    acc->getMotionModule().setRate(ratio * soValueAccesser::getConstantFloat(acc, 0xfbf, 0));
}
void ftSonicStatusUniqProcessSpecialSDash::processCheckAttack(soModuleAccesser* acc) {
    float speed = getCurrentSpeed(acc);
    if (acc->getCollisionAttackModule().isAttack(0, false) == true) {
        if (speed <= soValueAccesser::getConstantFloat(acc, 0xfbe, 0)) acc->getCollisionAttackModule().clear(0);
    } else if (speed > soValueAccesser::getConstantFloat(acc, 0xfbe, 0)) {
        acc->getWorkManageModule().onFlag(0x22000010);
    }
}
void ftSonicStatusUniqProcessSpecialSDash::syncSpeedAttackPower(soModuleAccesser* acc) {
    if (!acc->getCollisionAttackModule().isAttack(0, false)) return;
    float limit = soValueAccesser::getConstantFloat(acc, 0xfbe, 0);
    float ratio = getCurrentSpeed(acc) - limit;
    if (0.0f != ratio) {
        if (acc->getSituationModule().getKind() == 0) {
            limit = soValueAccesser::getConstantFloat(acc, 0xfbe, 0);
            ratio /= soValueAccesser::getConstantFloat(acc, 0xfba, 0) - limit;
        } else {
            limit = soValueAccesser::getConstantFloat(acc, 0xfbe, 0);
            ratio /= soValueAccesser::getConstantFloat(acc, 0xfbb, 0) - limit;
        }
    }
    if (ratio > 1.0f) ratio = 1.0f;
    else if (ratio < 0.0f) ratio = 0.0f;
    limit = soValueAccesser::getConstantFloat(acc, 0xfc0, 0);
    ratio *= soValueAccesser::getConstantFloat(acc, 0xfc1, 0) - limit;
    ratio += soValueAccesser::getConstantFloat(acc, 0xfc0, 0);
    acc->getCollisionAttackModule().setPower(0, (int)ratio, false);
}
float ftSonicStatusUniqProcessSpecialSDash::getCurrentSpeed(soModuleAccesser* acc) {
    if (acc->getSituationModule().getKind() == 0) return acc->getWorkManageModule().getFloat(0x21000004);
    return acc->getWorkManageModule().getFloat(0x21000005);
}
ftSonicStatusUniqProcessSpecialSDash g_ftSonicStatusUniqProcessSpecialSDash;
