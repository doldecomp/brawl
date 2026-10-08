// MATCH-ONLY: preserve the original DF08 vector-assignment call.
#define MT_VEC2F_ASSIGN_NOINLINE
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi_special_s_param.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
namespace ftyoshi { template <class T> T ABS(T); }

void ftYoshiStatusUniqProcessSpecialAirSJump::initStatus(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soSituationModule& situation = acc->getSituationModule();
    soPostureModule& posture = acc->getPostureModule();
    soKineticModule& kinetic = acc->getKineticModule();
    Vec2f speed;
    if (situation.getKind() != Situation_Air) {
        float lr = posture.getLr();
        speed.m_x = work.getFloat(0x21000006) * lr;
        speed.m_y = 0.0f;
    } else {
        Vec2f incoming = kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(-1));
        speed.m_x = incoming.m_x;
        speed.m_y = incoming.m_y;
    }
    kinetic.changeKinetic(0x65, acc);
    ftKineticEnergyController& control = dynamic_cast<ftKineticEnergyController&>(*kinetic.getEnergy(2));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
    control.m_speed.m_x = speed.m_x;
    control.m_speed.m_y = 0.0f;
    gravity.m_speedY = speed.m_y;
    work.setInt(-1, 0x20000008);
}
void ftYoshiStatusUniqProcessSpecialAirSJump::execStatus(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    work.setFloat(0.0f, 0x21000008);
    work.setInt(0, 0x20000006);
    work.setFloat(work.getFloat(0x21000005) + 0.10471976f * param->unk18, 0x21000005);
    ftYoshiStatusUniqProcessSpecialSUtility::setRot(acc);
    if (ftYoshiStatusUniqProcessSpecialSUtility::checkLife(acc) || ftYoshiStatusUniqProcessSpecialSUtility::checkCancel(acc)) work.setInt(0x11A, 0x20000008);
    ftYoshiStatusUniqProcessSpecialSUtility::setBodyChange(acc);
    ftYoshiStatusUniqProcessSpecialSUtility::setBodyScale(acc);
}
void ftYoshiStatusUniqProcessSpecialAirSJump::execFixPosCounter(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soControllerModule& controller = acc->getControllerModule();
    soSituationModule& situation = acc->getSituationModule();
    soKineticModule& kinetic = acc->getKineticModule();
    soPostureModule& posture = acc->getPostureModule();
    soGroundModule& ground = acc->getGroundModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    // MATCH-ONLY: retain the original aggregate word copy.
    Vec2f velocity;
    Vec2f::copy(velocity, kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(1)));
    float speed = work.getFloat(0x21000006);
    float lr = posture.getLr();
    bool grounded = situation.getKind() == Situation_Ground;
    bool hitWall;
    if (lr == 1.0f) {
        hitWall = ground.isTouch(static_cast<grCollStatus::TouchMask>(4), 0);
        if (hitWall) ftYoshiStatusUniqProcessSpecialSUtility::procHitWall(acc, 4);
    } else {
        hitWall = ground.isTouch(static_cast<grCollStatus::TouchMask>(2), 0);
        if (hitWall) ftYoshiStatusUniqProcessSpecialSUtility::procHitWall(acc, 2);
    }
    if (hitWall) {
        work.setInt(0x11A, 0x20000008);
        velocity.m_x *= -param->wallReboundHorizontal;
        velocity.m_y = param->wallReboundVertical;
    } else if (grounded) {
        velocity.m_y = ftyoshi::ABS(velocity.m_y * param->landingBounceMultiplier);
        if (velocity.m_y < param->landingBounceThreshold) {
            situation.setKind(Situation_Ground, false);
            ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(1), 0);
            ftYoshiStatusUniqProcessSpecialSUtility::audioDash(acc);
            velocity.m_y = 0.0f;
            if (ftyoshi::ABS(velocity.m_x) < 0.01f) velocity.m_x = 0.01f * lr;
            float stick = controller.getStickX();
            speed = stick;
            if (ftyoshi::ABS(stick) > param->turnStickThreshold) {
                lr = stick > 0.0f ? 1.0f : -1.0f;
                speed = param->unk74 * ftyoshi::ABS(stick);
                velocity.m_x = speed * lr;
                posture.setLr(lr);
                posture.updateRotYLr();
            }
        } else {
            ftYoshiStatusUniqProcessSpecialSUtility::setRot(acc);
            situation.setKind(Situation_Air, false);
            ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(5), 0);
        }
        work.setInt(0x119, 0x20000008);
        speed = param->unk1C;
        if (ftYoshiStatusUniqProcessSpecialSUtility::getFlick(acc)) speed *= param->flickSpeedMultiplier;
        velocity.m_x = speed * lr;
        work.setInt(0, 0x20000002);
    }
    work.setFloat(speed, 0x21000006);
    ftKineticEnergyController& control = dynamic_cast<ftKineticEnergyController&>(*kinetic.getEnergy(2));
    // MATCH-ONLY: retain the original temporary assignment lifetime.
    control.m_speed = Vec2f(velocity.m_x, 0.0f);
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
    gravity.m_speedY = velocity.m_y;
}
void ftYoshiStatusUniqProcessSpecialAirSJump::execFixPos(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soStatusModule& status = acc->getStatusModule();
    int target = work.getInt(0x20000008);
    if (target != -1) status.changeStatusRequest(target, acc);
}
void ftYoshiStatusUniqProcessSpecialAirSJump::exitStatus(soModuleAccesser* acc, int nextStatus) {
    if (nextStatus != 0x113) {
        if (static_cast<unsigned>(nextStatus - 0x119) > 3) return;
    }
    ftYoshiStatusUniqProcessSpecialSUtility::resetYoshiSpecialS2(acc);
}
ftYoshiStatusUniqProcessSpecialAirSJump g_ftYoshiStatusUniqProcessSpecialAirSJump;
