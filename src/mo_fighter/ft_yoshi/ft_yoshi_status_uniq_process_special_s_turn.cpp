// MATCH-ONLY: preserve the original DF08 vector-assignment calls.
#define MT_VEC2F_ASSIGN_NOINLINE
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi_special_s_param.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <math.h>
namespace ftyoshi { template <class T> T ABS(T); }

void ftYoshiStatusUniqProcessSpecialSTurn::initStatus(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soSituationModule& situation = acc->getSituationModule();
    soKineticModule& kinetic = acc->getKineticModule();
    soGroundModule& ground = acc->getGroundModule();
    if (situation.getKind() != Situation_Air) {
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(1), 0);
        kinetic.changeKinetic(0x64, acc);
        float acceleration = work.getFloat(0x21000007);
        ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
        Vec2f value;
        value.m_x = acceleration; value.m_y = 0.0f;
        stop.m_accel = value;
    } else ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(5), 0);
    acc->getVisibilityModule().set(1, 1);
    work.setInt(-1, 0x20000008);
}
void ftYoshiStatusUniqProcessSpecialSTurn::execStatus(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soKineticModule& kinetic = acc->getKineticModule();
    soPostureModule& posture = acc->getPostureModule();
    soModelModule& model = acc->getModelModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    // MATCH-ONLY: retain the original aggregate word copy.
    Vec2f velocity;
    Vec2f::copy(velocity, kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(-1)));
    float angle = work.getFloat(0x21000005);
    float oldSpeed = work.getFloat(0x21000004);
    ftYoshiStatusUniqProcessSpecialSUtility::setBodyChange(acc);
    ftYoshiStatusUniqProcessSpecialSUtility::setBodyScale(acc);
    work.setFloat(angle + 0.25132743f * param->turnRotation, 0x21000005);
    ftYoshiStatusUniqProcessSpecialSUtility::setRot(acc);
    float oldMagnitude = ftyoshi::ABS(oldSpeed);
    float magnitude = ftyoshi::ABS(velocity.m_x);
    // MATCH-ONLY: preserve the native discarded out-of-line ABS call.
    ftyoshi::ABS(param->turnModelAngle);
    float modelAngle = ftyoshi::ABS(param->turnModelAngle);
    if (oldSpeed > 0.0f) {
        if (velocity.m_x <= 0.0f) oldMagnitude *= 0.7f;
    } else if (velocity.m_x >= 0.0f) oldMagnitude *= 0.7f;
    float transitionMagnitude = 0.7f * ftyoshi::ABS(oldSpeed);
    float denominator = ftyoshi::ABS(oldSpeed) + transitionMagnitude;
    float yaw;
    if (oldSpeed > 0.0f) {
        float delta;
        if (velocity.m_x > 0.0f) {
            float currentMagnitude = ftyoshi::ABS(velocity.m_x);
            delta = ftyoshi::ABS(oldSpeed) - currentMagnitude;
        } else {
            float currentMagnitude = ftyoshi::ABS(velocity.m_x);
            delta = ftyoshi::ABS(oldSpeed) + currentMagnitude;
        }
        yaw = 1.5707964f + 3.1415927f * (delta / denominator);
    } else {
        float delta;
        if (velocity.m_x < 0.0f) {
            float currentMagnitude = ftyoshi::ABS(velocity.m_x);
            delta = ftyoshi::ABS(oldSpeed) - currentMagnitude;
        } else {
            float currentMagnitude = ftyoshi::ABS(velocity.m_x);
            delta = ftyoshi::ABS(oldSpeed) + currentMagnitude;
        }
        yaw = 4.712389f + 3.1415927f * (delta / denominator);
    }
    while (yaw < 0.0f) yaw += 6.2831855f;
    while (yaw > 6.2831855f) yaw -= 6.2831855f;
    model.setNodeRotateY(3, yaw * 57.29578f);
    model.setNodeRotateZ(2, (-param->turnModelAngle + modelAngle * (magnitude / oldMagnitude)) * 57.29578f);
    if (ftYoshiStatusUniqProcessSpecialSUtility::checkLife(acc) || ftYoshiStatusUniqProcessSpecialSUtility::checkCancel(acc)) work.setInt(0x11A, 0x20000008);
    else if (((oldSpeed > 0.0f && velocity.m_x < 0.0f) || (oldSpeed <= 0.0f && velocity.m_x > 0.0f)) && ftyoshi::ABS(velocity.m_x) > 0.7f * ftyoshi::ABS(oldSpeed)) {
        work.setInt(0x119, 0x20000008);
        ftYoshiStatusUniqProcessSpecialSUtility::audioDash(acc);
        float lr = work.getFloat(0x21000008);
        work.getInt(0x20000003);
        if (lr != 0.0f) posture.setLr(lr);
        model.setNodeRotateY(3, 0.0f);
        model.setNodeRotateZ(2, 0.0f);
        ftYoshiStatusUniqProcessSpecialSUtility::setRot(acc);
    }
}
void ftYoshiStatusUniqProcessSpecialSTurn::execFixPosCounter(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soSituationModule& situation = acc->getSituationModule();
    soGroundModule& ground = acc->getGroundModule();
    soKineticModule& kinetic = acc->getKineticModule();
    soPostureModule& posture = acc->getPostureModule();
    soModelModule& model = acc->getModelModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    bool grounded = situation.getKind() == Situation_Ground;
    // MATCH-ONLY: retain the original aggregate word copy.
    Vec2f speed;
    Vec2f::copy(speed, kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(-1)));
    bool hitWall;
    if (speed.m_x > 0.0f) {
        hitWall = ground.isTouch(static_cast<grCollStatus::TouchMask>(4), 0);
        if (hitWall) ftYoshiStatusUniqProcessSpecialSUtility::procHitWall(acc, 4);
    } else {
        hitWall = ground.isTouch(static_cast<grCollStatus::TouchMask>(2), 0);
        if (hitWall) ftYoshiStatusUniqProcessSpecialSUtility::procHitWall(acc, 2);
    }
    if (hitWall) {
        speed.m_x *= -param->wallReboundHorizontal;
        speed.m_y = param->wallReboundVertical;
        ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
        // MATCH-ONLY: retain the original temporary assignment lifetime.
        stop.m_speed = Vec2f(speed.m_x, 0.0f);
        situation.setKind(Situation_Air, false);
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(5), 0);
        work.setInt(0x11A, 0x20000008);
        grounded = false;
    } else if (!grounded) {
        situation.setKind(Situation_Air, false);
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(5), 0);
        work.setInt(0x119, 0x20000008);
        float lr = work.getFloat(0x21000008);
        if (lr != 0.0f) {
            posture.setLr(lr);
            work.setFloat(ftyoshi::ABS(speed.m_x), 0x21000006);
        }
        model.setNodeRotateY(3, 0.0f);
        model.setNodeRotateZ(2, 0.0f);
    }
    if (grounded) {
        if (ftyoshi::ABS(speed.m_x) > param->groundCorrectThreshold)
            ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(1), 0);
        else
            ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(2), 0);
        int counter = work.getInt(0x20000004);
        if (counter % param->dustInterval == 0) {
            // MATCH-ONLY: retain the original aggregate word copy.
            Vec2f normal;
            Vec2f::copy(normal, ground.getTouchNormal(static_cast<grCollStatus::TouchMask>(8), 0));
            float yaw = speed.m_x < 0.0f ? -1.5707964f : 1.5707964f;
            float normalY = normal.m_y;
            float slope = atan2(-normal.m_x, normalY);
            Vec3f rotation;
            rotation.m_x = 0.0f; rotation.m_y = yaw; rotation.m_z = slope;
            soEffectModule& effect = acc->getEffectModule();
            Vec3f position = posture.getPos();
            effect.req(static_cast<EfID>(10), &position, &rotation, 1.0f, 0, -1);
        }
        work.setInt(counter + 1, 0x20000004);
    }
}
void ftYoshiStatusUniqProcessSpecialSTurn::execFixPos(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soStatusModule& status = acc->getStatusModule();
    int target = work.getInt(0x20000008);
    if (target != -1) status.changeStatusRequest(target, acc);
}
void ftYoshiStatusUniqProcessSpecialSTurn::exitStatus(soModuleAccesser* acc, int nextStatus) {
    if (nextStatus == 0x113 || static_cast<unsigned>(nextStatus - 0x119) <= 3)
        ftYoshiStatusUniqProcessSpecialSUtility::resetYoshiSpecialS2(acc);
}
ftYoshiStatusUniqProcessSpecialSTurn g_ftYoshiStatusUniqProcessSpecialSTurn;
