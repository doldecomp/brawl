#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/lucas/ft_lucas_status_uniq_process_special_hi.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <so/link/so_link_module_impl.h>
#include <so/so_kinetic_energy_normal.h>
#include <math.h>

struct ftLucasSpecialHiAttackParam { u8 unk00[0x18]; float launchSpeed; };
struct ftLucasAttackCommonParamData { u8 unk00[0x84]; ftLucasSpecialHiAttackParam* specialHi; };

void ftLucasStatusUniqProcessSpecialHiAttack::initStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soSituationModule& situation = a->getSituationModule();
    soKineticModule& kinetic = a->getKineticModule();
    soGroundModule& ground = a->getGroundModule();
    soPostureModule& posture = a->getPostureModule();
    ftLucasSpecialHiAttackParam* param = reinterpret_cast<ftLucasAttackCommonParamData*>(
        g_ftCommonDataAccesser.getData(Fighter_Lucas))->specialHi;
    float speed = param->launchSpeed;
    float angle = work.getFloat(0x21000004);
    soKineticEnergyNormal& flight = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(3));
    if (work.isFlag(0x22000011)) {
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(5), 0);
        situation.setKind(Situation_Air, false);
        flight.m_speed = Vec2f(speed * cosf(angle), speed * sinf(angle));
        ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
        gravity.m_speedY = 0.0f;
    } else {
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(1), 0);
        situation.setKind(Situation_Ground, false);
        flight.m_speed = Vec2f(speed * posture.getLr(), 0.0f);
    }
    kinetic.changeKinetic(situation.getKind() == Situation_Ground ? 0x67 : 0x68, a);
    posture.updateRotYLr();
}
void ftLucasStatusUniqProcessSpecialHiAttack::execStatus(soModuleAccesser* a) {
    soKineticModule& kinetic = a->getKineticModule();
    soPostureModule& posture = a->getPostureModule();
    soWorkManageModule& work = a->getWorkManageModule();
    Vec2f speed = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(3)).getSpeed();
    float rotation = atan2f(speed.m_y, speed.m_x * posture.getLr()) * 57.29578f;
    work.setFloat(rotation, 0x21000004);
    Vec3f rot(0.0f, 0.0f, rotation);
    posture.setRot(&rot, 3);
}
void ftLucasStatusUniqProcessSpecialHiAttack::execStop(soModuleAccesser* a) {
    execStatus(a);
}
void ftLucasStatusUniqProcessSpecialHiAttack::exitStatus(soModuleAccesser* a, int nextStatus) {
    soPostureModule& posture = a->getPostureModule();
    soWorkManageModule& work = a->getWorkManageModule();
    soKineticModule& kinetic = a->getKineticModule();
    Vec3f zero(0.0f, 0.0f, 0.0f);
    posture.setRot(&zero, 3);
    if (nextStatus == 0x11e || nextStatus == 0x11b) {
        Vec2f speed = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(3)).getSpeed();
        float angle = atan2f(speed.m_y, speed.m_x * posture.getLr());
        if (nextStatus == 0x11b) angle = 1.57079637f - angle;
        work.setFloat(angle, 0x21000004);
        work.setFloat(fabsf(angle * 0.1f), 0x21000006);
    } else {
        Vec3f zeroPos(0.0f, 0.0f, 0.0f);
        posture.setRot(&zeroPos, 0);
    }
}
ftLucasStatusUniqProcessSpecialHiAttack::~ftLucasStatusUniqProcessSpecialHiAttack() {}
ftLucasStatusUniqProcessSpecialHiAttack g_ftLucasStatusUniqProcessSpecialHiAttack;

void ftLucasStatusUniqProcessSpecialHiAttack::execFixPosCounter(soModuleAccesser* a) {
    soLinkModule& link = a->getLinkModule();
    if (link.getParent(6) == 0) return;
    soWorkManageModule& work = a->getWorkManageModule();
    soSituationModule& situation = a->getSituationModule();
    soKineticModule& kinetic = a->getKineticModule();
    soStatusModule& status = a->getStatusModule();
    soGroundModule& ground = a->getGroundModule();
    soPostureModule& posture = a->getPostureModule();
    soKineticEnergyNormal& flight = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(3));

    u8* data = reinterpret_cast<u8*>(g_ftCommonDataAccesser.getData(Fighter_Lucas));
    u8* param = *reinterpret_cast<u8**>(data + 0x84);
    float maxAngle = *reinterpret_cast<float*>(param + 0x28);
    float turnLimit = (maxAngle + 90.0f) * 0.017453292f;

    Vec2f velocity = flight.getSpeed();
    float speedSq = velocity.m_x * velocity.m_x + velocity.m_y * velocity.m_y;
    float speed = speedSq > 1.0e-4f ? sqrtf(speedSq) : 0.0f;
    Vec2f direction = velocity;
    if (speed != 0.0f) {
        direction.m_x /= speed;
        direction.m_y /= speed;
    }

    if (situation.isSituationChanged()) {
        if (situation.getKind() == Situation_Ground) {
            Vec2f normal = ground.getTouchNormal(static_cast<grCollStatus::TouchMask>(8), 0);
            float normalAngle = atan2f(normal.m_y, normal.m_x);
            float velocityAngle = atan2f(direction.m_y, direction.m_x);
            float difference = fabsf(atan2f(
                sinf(velocityAngle - normalAngle), cosf(velocityAngle - normalAngle)));
            if (difference > turnLimit) {
                status.changeStatusRequest(0x4a, a);
                return;
            }
            ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(1), 0);
            kinetic.changeKinetic(0x67, a);
        } else {
            if (ground.isTouch(static_cast<grCollStatus::TouchMask>(4), 0) ||
                ground.isTouch(static_cast<grCollStatus::TouchMask>(2), 0)) {
                status.changeStatusRequest(0x11b, a);
                return;
            }
            ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(5), 0);
            kinetic.changeKinetic(0x68, a);
        }
    }

    if (situation.getKind() == Situation_Ground) {
        int touchMask = 0;
        if (ground.isTouch(static_cast<grCollStatus::TouchMask>(1), 0)) touchMask = 1;
        else if (ground.isTouch(static_cast<grCollStatus::TouchMask>(4), 0)) touchMask = 4;
        else if (ground.isTouch(static_cast<grCollStatus::TouchMask>(2), 0)) touchMask = 2;
        if (touchMask != 0) {
            status.changeStatusRequest(0x4a, a);
        } else {
            Vec2f normal = ground.getTouchNormal(static_cast<grCollStatus::TouchMask>(8), 0);
            float baseAngle = atan2f(normal.m_y, normal.m_x) - 1.57079637f;
            Vec2f adjusted = direction;
            adjusted.rot(&adjusted, baseAngle);
            flight.m_speed = Vec2f(speed * adjusted.m_x, speed * adjusted.m_y);
        }
    } else {
        int touchMask = 0;
        if (ground.isTouch(static_cast<grCollStatus::TouchMask>(1), 0)) touchMask = 1;
        else if (ground.isTouch(static_cast<grCollStatus::TouchMask>(4), 0)) touchMask = 4;
        else if (ground.isTouch(static_cast<grCollStatus::TouchMask>(2), 0)) touchMask = 2;
        if (touchMask != 0) {
            Vec2f normal = ground.getTouchNormal(
                static_cast<grCollStatus::TouchMask>(touchMask), 0);
            float normalLength = sqrtf(normal.m_x * normal.m_x + normal.m_y * normal.m_y);
            if (normalLength > 0.0001f) {
                normal.m_x /= normalLength;
                normal.m_y /= normalLength;
            }
            float dot = direction.m_x * normal.m_x + direction.m_y * normal.m_y;
            if (dot > 1.0f) dot = 1.0f;
            if (dot < -1.0f) dot = -1.0f;
            float difference = acosf(dot);
            if (difference > turnLimit) {
                Vec2f reflected = direction;
                float projection = 2.0f * dot;
                reflected.m_x -= projection * normal.m_x;
                reflected.m_y -= projection * normal.m_y;
                flight.m_speed = Vec2f(reflected.m_x * speed, reflected.m_y * speed);
                status.changeStatusRequest(0x11d, a);
            } else if (touchMask == 4 || touchMask == 2) {
                float angle = atan2f(normal.m_y, normal.m_x);
                float currentAngle = work.getFloat(0x21000004);
                while (angle < 0.0f) angle += 6.28318548f;
                while (angle > 6.28318548f) angle -= 6.28318548f;
                while (currentAngle < 0.0f) currentAngle += 6.28318548f;
                while (currentAngle > 6.28318548f) currentAngle -= 6.28318548f;
                if (touchMask == 4) {
                    float oppositeAngle = currentAngle + 3.14159274f;
                    while (oppositeAngle < 0.0f) oppositeAngle += 6.28318548f;
                    while (oppositeAngle > 6.28318548f) oppositeAngle -= 6.28318548f;
                    angle += oppositeAngle - angle >= 0.0f ? -1.57079637f : 1.57079637f;
                } else {
                    float oppositeAngle = angle + 3.14159274f;
                    while (oppositeAngle < 0.0f) oppositeAngle += 6.28318548f;
                    while (oppositeAngle > 6.28318548f) oppositeAngle -= 6.28318548f;
                    angle += currentAngle - oppositeAngle >= 0.0f ? -1.57079637f : 1.57079637f;
                }
                Vec2f adjusted = direction;
                adjusted.rot(&adjusted, angle - currentAngle);
                flight.m_speed = Vec2f(adjusted.m_x * speed, adjusted.m_y * speed);
                work.setFloat(currentAngle, 0x21000004);
                kinetic.changeKinetic(0x68, a);
            }
        }
    }

    if (status.isCollisionAttackOccer()) {
        velocity = flight.getSpeed();
        speedSq = velocity.m_x * velocity.m_x + velocity.m_y * velocity.m_y;
        speed = speedSq > 1.1754944e-38f ? sqrtf(speedSq) : 0.0f;
        float adjustedSpeed = speed - *reinterpret_cast<float*>(param + 0x20);
        if (adjustedSpeed < 1.0e-4f) adjustedSpeed = 1.0e-4f;
        float lr = posture.getLr();
        float angle = atan2f(velocity.m_y, velocity.m_x * lr);
        flight.m_speed = Vec2f(adjustedSpeed * cosf(angle) * lr, adjustedSpeed * sinf(angle));
    }

}
