#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi_special_s_param.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <so/model/so_model_module_impl.h>
#include <so/motion/so_motion_change_param.h>
namespace ftyoshi { template <class T> T ABS(T); }

void ftYoshiStatusUniqProcessSpecialSLoop::initStatus(soModuleAccesser* acc) {
    soSituationModule& situation = acc->getSituationModule();
    soKineticModule& kinetic = acc->getKineticModule();
    soGroundModule& ground = acc->getGroundModule();
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
    if (situation.getKind() == Situation_Ground) {
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(1), 0);
        kinetic.changeKinetic(0x64, acc);
    } else {
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(5), 0);
        kinetic.changeKinetic(0x65, acc);
    }
    stop.m_unk30 = true;
    acc->getVisibilityModule().set(1, 1);
    acc->getEffectModule().reqCommon(0.0f, 0x23);
    acc->getWorkManageModule().setInt(-1, 0x20000008);
}
void ftYoshiStatusUniqProcessSpecialSLoop::execStatus(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    float speed = work.getFloat(0x21000006);
    float angle = work.getFloat(0x21000005);
    work.setFloat(0.0f, 0x21000008);
    ftYoshiStatusUniqProcessSpecialSUtility::setBodyChange(acc);
    ftYoshiStatusUniqProcessSpecialSUtility::setBodyScale(acc);
    ftYoshiStatusUniqProcessSpecialSUtility::setAttack(acc);
    ftYoshiStatusUniqProcessSpecialSUtility::setPower(acc);
    work.setFloat(angle + 0.25132743f * (param->rollRotationMultiplier * ftyoshi::ABS(speed)), 0x21000005);
    ftYoshiStatusUniqProcessSpecialSUtility::setRot(acc);
    if (ftYoshiStatusUniqProcessSpecialSUtility::checkLife(acc)) work.setInt(0x11A, 0x20000008);
    if (ftYoshiStatusUniqProcessSpecialSUtility::checkCancel(acc)) {
        work.setFloat(0.0f, 0x21000008);
        work.setInt(0x11A, 0x20000008);
    }
}
void ftYoshiStatusUniqProcessSpecialSLoop::execFixPosCounter(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soControllerModule& controller = acc->getControllerModule();
    soSituationModule& situation = acc->getSituationModule();
    soKineticModule& kinetic = acc->getKineticModule();
    soPostureModule& posture = acc->getPostureModule();
    soGroundModule& ground = acc->getGroundModule();
    soMotionModule& motion = acc->getMotionModule();
    soModelModule& model = acc->getModelModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    // MATCH-ONLY: retain the original aggregate word copy.
    Vec2f velocity;
    Vec2f::copy(velocity, kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(1)));
    float lr = posture.getLr();
    float speed = work.getFloat(0x21000006);
    float angle = work.getFloat(0x21000005);
    bool grounded = situation.getKind() == Situation_Ground;
    if (grounded) {
        int groundedFrames = work.getInt(0x20000006);
        float stick = controller.getStickX();
        if (groundedFrames != 0 && velocity.m_x != 0.0f && ftyoshi::ABS(stick) > param->turnStickThreshold) {
            float requestedLr = stick > 0.0f ? 1.0f : -1.0f;
            if (lr != requestedLr) {
                acc->getCollisionAttackModule().clearAll();
                work.setFloat(requestedLr, 0x21000008);
                work.setFloat(velocity.m_x, 0x21000004);
                work.setFloat(-0.05f * velocity.m_x, 0x21000007);
                work.setInt(0, 0x20000004);
                work.setInt(0x11B, 0x20000008);
                ftYoshiStatusUniqProcessSpecialSUtility::setRot(acc);
            }
        }
    }
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
        grounded = false;
    } else if (situation.isSituationChanged()) {
        if (grounded) {
            velocity.m_y = ftyoshi::ABS(velocity.m_y * param->landingBounceMultiplier);
            if (velocity.m_y < param->landingBounceThreshold) {
                soMotionChangeParam change(0x1D5, motion.getFrame(), 0.0f, 0, 1, 0, 0);
                motion.changeMotionRequest(&change);
                ftYoshiStatusUniqProcessSpecialSUtility::audioDash(acc);
                if (ftyoshi::ABS(speed) < 0.01f) speed = 0.01f;
                velocity.m_x = speed * lr;
                velocity.m_y = 0.0f;
                work.setFloat(angle + 0.25132743f * (param->rollRotationMultiplier * ftyoshi::ABS(speed)), 0x21000005);
                ftYoshiStatusUniqProcessSpecialSUtility::setRot(acc);
            } else {
                grounded = false;
                float stick = controller.getStickX();
                if (ftyoshi::ABS(stick) > param->turnStickThreshold) {
                    lr = stick > 0.0f ? 1.0f : -1.0f;
                    speed = param->unk74 * ftyoshi::ABS(stick);
                    velocity.m_x = speed * lr;
                    posture.setLr(lr);
                    posture.updateRotYLr();
                    model.setNodeRotateY(3, 0.0f);
                }
                ftYoshiStatusUniqProcessSpecialSUtility::setRot(acc);
            }
            work.setInt(0, 0x20000002);
        } else {
            soMotionChangeParam change(0x1D8, motion.getFrame(), 0.0f, 0, 1, 0, 0);
            motion.changeMotionRequest(&change);
            ftYoshiStatusUniqProcessSpecialSUtility::setRot(acc);
        }
    }
    work.setFloat(ftyoshi::ABS(velocity.m_x), 0x21000006);
    if (grounded) {
        situation.setKind(Situation_Ground, false);
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(1), 0);
        kinetic.changeKinetic(0x64, acc);
        ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
        // MATCH-ONLY: retain the original call-temporary stack order.
        stop.setSpeed(&Vec2f(velocity.m_x, 0.0f));
        work.incInt(0x20000006);
    } else {
        situation.setKind(Situation_Air, false);
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(5), 0);
        kinetic.changeKinetic(0x65, acc);
        ftKineticEnergyController& control = dynamic_cast<ftKineticEnergyController&>(*kinetic.getEnergy(2));
        ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
        // MATCH-ONLY: retain the original call-temporary stack order.
        control.setSpeed(&Vec2f(velocity.m_x, 0.0f));
        gravity.m_speedY = velocity.m_y;
        work.setInt(0, 0x20000006);
    }
}
// Original emitted constructor and setter belong to the natural Loop TU.
soMotionChangeParam::soMotionChangeParam(int kind, float frame, float rate, u8 a, u8 b, u8 c, u8 d) {
    m_kind = kind; m_frame = frame; m_rate = rate;
    _12 = a; _13 = b; _14 = c; _15 = d;
}
void soKineticEnergyNormal::setSpeed(Vec2f* speed) {
    m_speed.m_x = speed->m_x;
    m_speed.m_y = speed->m_y;
}
void ftYoshiStatusUniqProcessSpecialSLoop::execFixPos(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soStatusModule& status = acc->getStatusModule();
    int target = work.getInt(0x20000008);
    if (target != -1) status.changeStatusRequest(target, acc);
}
void ftYoshiStatusUniqProcessSpecialSLoop::exitStatus(soModuleAccesser* acc, int nextStatus) {
    if (nextStatus == 0x113 || static_cast<unsigned>(nextStatus - 0x119) <= 3) ftYoshiStatusUniqProcessSpecialSUtility::resetYoshiSpecialS2(acc);
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*acc->getKineticModule().getEnergy(3));
    stop.m_unk30 = false;
    acc->getEffectModule().removeCommon(0x23);
}
ftYoshiStatusUniqProcessSpecialSLoop g_ftYoshiStatusUniqProcessSpecialSLoop;
