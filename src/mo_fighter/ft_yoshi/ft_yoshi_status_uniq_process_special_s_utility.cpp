// MATCH-ONLY: preserve the shared out-of-line vector constructor calls.
#pragma dont_inline on
#include <mt/mt_vector.h>
#pragma dont_inline reset
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi_special_s_param.h>
#include <ft/ft_common_data_accesser.h>
#include <so/so_module_accesser.h>
#include <so/model/so_model_module_impl.h>
#include <math.h>

// Original module-owned template specialization; ownership still under review.
// HYPOTHESIS: source namespace spelling inferred from the original map.
namespace ftyoshi { template <class T> T ABS(T); }
int g_ftYoshiSpecialSBodyChange[15] = {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1};
float g_ftYoshiSpecialSBodyScaleY[4] = {0.65f, 0.7f, 0.8f, 1.0f};
float g_ftYoshiSpecialSBodyScaleZ[4] = {1.1f, 1.35f, 1.3f, 1.2f};

bool ftYoshiStatusUniqProcessSpecialSUtility::checkLife(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    int remaining = work.getInt(0x20000000);
    bool ended = false;
    --remaining;
    if (remaining <= 0) { remaining = 0; ended = true; }
    work.setInt(remaining, 0x20000000);
    return ended;
}
bool ftYoshiStatusUniqProcessSpecialSUtility::checkCancel(soModuleAccesser* acc) {
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    if (acc->getWorkManageModule().getInt(0x20000000) < param->life - param->cancelDelay) {
        soControllerModule& controller = acc->getControllerModule();
        int button = soController::getButtonMask(soController::Pad_Button_Special);
        if (button & controller.getTrigger()) return true;
    }
    return false;
}
void ftYoshiStatusUniqProcessSpecialSUtility::setBodyChange(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    bool changing = work.isFlag(0x22000011);
    bool restart = work.isFlag(0x22000012);
    int index = work.getInt(0x20000001);
    int changes = work.getInt(0x20000007);
    if (restart) { index = 0; ++changes; }
    else if (changing) ++index;
    if (index >= 0 && index < 14) {
        acc->getVisibilityModule().set(1, g_ftYoshiSpecialSBodyChange[index]);
        if (restart) {
            work.offFlag(0x22000011);
            work.offFlag(0x22000012);
            index = -1;
        }
    } else {
        work.offFlag(0x22000011);
        work.offFlag(0x22000012);
    }
    work.setInt(index, 0x20000001);
    work.setInt(changes, 0x20000007);
}
void ftYoshiStatusUniqProcessSpecialSUtility::setBodyScale(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soModelModule& model = acc->getModelModule();
    Vec3f scale(1.0f, 1.0f, 1.0f);
    int index = work.getInt(0x20000002);
    if (index >= 0 && index < 4) {
        scale.m_y *= g_ftYoshiSpecialSBodyScaleY[index];
        scale.m_z *= g_ftYoshiSpecialSBodyScaleZ[index];
        ++index;
    }
    model.setNodeScale(2, &scale);
    work.setInt(index, 0x20000002);
}
void ftYoshiStatusUniqProcessSpecialSUtility::resetYoshiSpecialS(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soModelModuleImpl& model = dynamic_cast<soModelModuleImpl&>(acc->getModelModule());
    if (acc->getStatusModule().getStatusKind() != 0x11A) acc->getVisibilityModule().set(1, 0);
    Vec3f scale(1.0f, 1.0f, 1.0f);
    model.setNodeScale(2, &scale);
    model.setNodeRotateY(3, 0.0f);
    model.setNodeRotateZ(2, 0.0f);
    float lr = work.getFloat(0x21000008);
    if (lr != 0.0f) acc->getPostureModule().setLr(lr);
    work.setFloat(0.0f, 0x21000008);
}
void ftYoshiStatusUniqProcessSpecialSUtility::resetYoshiSpecialS2(soModuleAccesser* acc) {
    acc->getStatusModule().getStatusKind();
    resetYoshiSpecialS(acc);
}
void ftYoshiStatusUniqProcessSpecialSUtility::audioDash(soModuleAccesser*) {}
void ftYoshiStatusUniqProcessSpecialSUtility::procHit(soModuleAccesser* acc) {
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    soWorkManageModule& work = acc->getWorkManageModule();
    soSituationModule& situation = acc->getSituationModule();
    int life = work.getInt(0x20000000);
    int counter = work.getInt(0x20000003);
    float speed = work.getFloat(0x21000006);
    if (acc->getStatusModule().getStatusKind() == 0x119) {
        life -= param->hitLifeCost;
        float minimum = situation.getKind() == 2 ? param->minimumAirSpeed : param->minimumGroundSpeed;
        if (ftyoshi::ABS(speed) > minimum) {
            if (speed > 0.0f) { speed -= param->hitSpeedDeceleration; if (speed < minimum) speed = minimum; }
            else { speed += param->hitSpeedDeceleration; if (speed > -minimum) speed = -minimum; }
        } else if (speed == 0.0f) speed = minimum * acc->getPostureModule().getLr();
    }
    work.setInt(life, 0x20000000);
    work.setInt(counter, 0x20000003);
    work.setFloat(speed, 0x21000006);
}
void ftYoshiStatusUniqProcessSpecialSUtility::procHitWall(soModuleAccesser* acc, int touch) {
    // HYPOTHESIS: the original wrapper forwards int unchanged; the existing
    // ground interface narrows to u8. Observed Egg Roll callers use only 2/4/8.
    Vec2f normal = acc->getGroundModule().getTouchNormal(static_cast<grCollStatus::TouchMask>(touch), 0);
    Vec2f position = acc->getGroundModule().getTouchPos(static_cast<grCollStatus::TouchMask>(touch), 0);
    float angle = atan2(-normal.m_x, normal.m_y);
    acc->getEffectModule().req(static_cast<EfID>(9), &Vec3f(position.m_x, position.m_y, 0.0f), &Vec3f(0.0f, 0.0f, angle), 1.0f, 0, -1);
}
bool ftYoshiStatusUniqProcessSpecialSUtility::getFlick(soModuleAccesser* acc) {
    soControllerModule& controller = acc->getControllerModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    return static_cast<float>(controller.getFlickNoResetX()) < param->flickThreshold;
}
void ftYoshiStatusUniqProcessSpecialSUtility::setRot(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soModelModuleImpl& model = dynamic_cast<soModelModuleImpl&>(acc->getModelModule());
    g_ftCommonDataAccesser.getData(Fighter_Yoshi);
    float angle = work.getFloat(0x21000005);
    if (angle < 0.0f) angle += 6.2831855f;
    if (angle > 6.2831855f) angle -= 6.2831855f;
    model.setNodeRotateX(3, angle * 57.29578f);
    work.setFloat(angle, 0x21000005);
}
void ftYoshiStatusUniqProcessSpecialSUtility::setAttack(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soCollisionAttackModule& attack = acc->getCollisionAttackModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    int counter = work.getInt(0x20000003);
    int interval = param->attackInterval;
    ++counter;
    if (counter >= interval && attack.isAttack(0, false)) counter = 0;
    work.setInt(counter, 0x20000003);
}
void ftYoshiStatusUniqProcessSpecialSUtility::setPower(soModuleAccesser* acc) {
    soCollisionAttackModule& attack = acc->getCollisionAttackModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    if (attack.isAttack(0, false)) {
        Vec2f speed = acc->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(-1));
        int power = (param->attackPowerBase + ftyoshi::ABS(speed.m_x)) * param->attackPowerMultiplier;
        if (power < 1) power = 1;
        attack.setPower(0, power, false);
        attack.setPower(1, power, false);
    }
}
