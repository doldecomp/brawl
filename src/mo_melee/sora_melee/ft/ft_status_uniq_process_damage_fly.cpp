#include <ft/ft_status_uniq_process_damage_fly.h>
#include <ft/ft_kinetic_energy.h>
#include <gf/gf_task.h>
#include <gf/gf_task_scheduler.h>
#include <mt/mt_prng.h>
#include <so/so_external_value_accesser.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/stageobject.h>
#include <types.h>

// HYPOTHESIS: names taken from the map (ftUtil::setCloudThroughCheck / checkCloudThroughOut)
class ftUtil {
public:
    static void setCloudThroughCheck(soModuleAccesser* moduleAccesser);
    static bool checkCloudThroughOut(soModuleAccesser* moduleAccesser);
};

// HYPOTHESIS: the original uses its own inline length helper (float FLT_MIN compare and
// inline fabs) instead of Vec2f::length from the shared header.
static inline float calcLength(float lengthSq) {
    float length;
    if ((float)__fabs(lengthSq) <= 1.17549435e-38f) {
        length = 0.0f;
    } else {
        length = rsqrtf(lengthSq) * lengthSq;
    }
    return length;
}

static inline float calcLength(const Vec2f& v) {
    return calcLength(v.m_x * v.m_x + v.m_y * v.m_y);
}

ftStatusUniqProcessDamageFly g_ftStatusUniqProcessDamageFly;

void ftStatusUniqProcessDamageFly::setDamageCamera(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getStatusModule().getPrevStatusKind(0) != 0xc1) {
        moduleAccesser->getCameraModule().setDamageFly(0);
    }
}

void ftStatusUniqProcessDamageFly::initNormalDamageCommon(soModuleAccesser* moduleAccesser) {
    ftStatusUniqProcessDamage::initNormalDamageCommon(moduleAccesser);
    float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xcd1, 0);
    int effectHandle;
    if (calcLength(moduleAccesser->getKineticModule().getEnergy(4)->getSpeed()) < threshold) {
        effectHandle = -1;
    } else {
        soEffectModule& effect = moduleAccesser->getEffectModule();
        float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xcd2, 0);
        effectHandle = effect.reqContinual((EfID)0xc, c, soValueAccesser::getConstantInt(moduleAccesser, 0x59e0, 0), true, -1);
    }
    moduleAccesser->getWorkManageModule().setInt(effectHandle, 0x20000000);
    moduleAccesser->getGroundModule().selectCliffHangData(1, 0);
}

void ftStatusUniqProcessDamageFly::initNormalDamage(soModuleAccesser* moduleAccesser) {
    soDamageLog* damageLog = moduleAccesser->getDamageModule().getDamageLog();
    int motionKind;
    if (damageLog->m_angle > soValueAccesser::getConstantFloat(moduleAccesser, 0x7df, 0)
        && damageLog->m_angle < soValueAccesser::getConstantFloat(moduleAccesser, 0x7e0, 0)) {
        motionKind = 0xa7;
    } else {
        int motionKinds[3] = { 0xA6, 0xA5, 0xA4 };
        int height = damageLog->m_height;
        if (motionKinds[height] == moduleAccesser->getMotionModule().getKind()) {
            height = randi(2) + height + 1;
            if (height >= 3) {
                height -= 3;
            }
        }
        motionKind = motionKinds[height];
    }
    soMotionChangeParam param;
    param.m_kind = motionKind;
    param.m_frame = 0.0f;
    param.m_rate = 1.0f;
    param._12 = 0;
    param._13 = 0;
    param._14 = 0;
    param._15 = 0;
    moduleAccesser->getMotionModule().changeMotionRequest(&param);
    initNormalDamageCommon(moduleAccesser);
    setDamageCamera(moduleAccesser);
}

void ftStatusUniqProcessDamageFly::execNormalDamageCommon(soModuleAccesser* moduleAccesser) {
    ftStatusUniqProcessDamage::execNormalDamageCommon(moduleAccesser);
    int effectHandle = moduleAccesser->getWorkManageModule().getInt(0x20000000);
    if (effectHandle != -1) {
        float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xcd1, 0);
        if (calcLength( moduleAccesser->getKineticModule().getEnergy(4)->getSpeed()) < threshold) {
            moduleAccesser->getEffectModule().removeContinual((int)effectHandle);
            moduleAccesser->getWorkManageModule().setInt(-1, 0x20000000);
        }
    }
    ftUtil::setCloudThroughCheck(moduleAccesser);
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000017) == 0) {
        moduleAccesser->getWorkManageModule().onFlag(0x22000017);
        if (moduleAccesser->getSituationModule().getKind() == 2) {
            if (moduleAccesser->getStatusModule().getPrevStatusKind(0) != 0xc1) {
                correctDamageVector(moduleAccesser);
            }
        }
    }
}


void ftStatusUniqProcessDamageFly::correctDamageVector(soModuleAccesser* moduleAccesser) {
    float stickX = moduleAccesser->getControllerModule().getStickX();
    float stickY = moduleAccesser->getControllerModule().getStickY();
    if (0.0f == stickX && 0.0f == stickY) {
        return;
    }
    soKineticEnergy* energy = moduleAccesser->getKineticModule().getEnergy(4);
    if (!energy->isEnable()) {
        return;
    }
    soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(*energy);
    const Vec2f& speed = normal.getSpeed();
    Vec3f velocity(speed.m_x, speed.m_y, 0.0f);
    float length = calcLength(velocity.m_z * velocity.m_z + (velocity.m_x * velocity.m_x + velocity.m_y * velocity.m_y));
    if (length < 0.00001f) {
        return;
    }
    soDamageLog* damageLog = moduleAccesser->getDamageModule().getDamageLog();
    float limit = soValueAccesser::getConstantFloat(moduleAccesser, 0xcda, 0);
    if ((float)atan2((float)__fabs(velocity.m_y), (float)__fabs(velocity.m_x)) <= limit) {
        return;
    }
    float angle = atan2(velocity.m_y, velocity.m_x);
    Vec3f stick(stickX, stickY, 0.0f);
    Vec3f cross;
    cross.m_x = velocity.m_y * stick.m_z - velocity.m_z * stick.m_y;
    cross.m_y = velocity.m_z * stick.m_x - velocity.m_x * stick.m_z;
    cross.m_z = velocity.m_x * stick.m_y - velocity.m_y * stick.m_x;
    float perpendicular = (float)__fabs(cross.m_z) / length;
    if (cross.m_z < 0.0f) {
        perpendicular = -perpendicular;
    }
    angle = angle + limit * perpendicular;
    Vec2f result;
    result.m_y = length * (float)sin(angle);
    result.m_x = length * (float)cos(angle);
    normal.m_speed.m_x = result.m_x;
    normal.m_speed.m_y = result.m_y;
}

void ftStatusUniqProcessDamageFly::execNormalDamage(soModuleAccesser* moduleAccesser) {
    execNormalDamageCommon(moduleAccesser);
}

void ftStatusUniqProcessDamageFly::execFixPosCounter(soModuleAccesser* moduleAccesser) {
    if (ftUtil::checkCloudThroughOut(moduleAccesser) == 1) {
        int frame = moduleAccesser->getWorkManageModule().getInt(0x10000038);
        float mul = soValueAccesser::getConstantFloat(moduleAccesser, 0xcdc, 0);
        int newFrame = (int)((float)frame * mul);
        moduleAccesser->getWorkManageModule().setInt(newFrame, 0x10000038);
    }
}

void ftStatusUniqProcessDamageFly::execFixPos(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getCollisionAttackModule().isAttack(0, false) == 1) {
        if (0.0f == moduleAccesser->getWorkManageModule().getFloat(0x21000007)) {
            moduleAccesser->getWorkManageModule().setFloat(moduleAccesser->getCollisionAttackModule().getPower(0, false), 0x21000007);
            soCollisionAttackModule* attackModule = &moduleAccesser->getCollisionAttackModule();
            attackModule->setSize(soValueAccesser::getConstantFloat(moduleAccesser, 0xbe8, 0), 0);
        }
        moduleAccesser->getDamageModule().getDamageLog();
        soKineticEnergyNormal* normal = &dynamic_cast<soKineticEnergyNormal&>(*moduleAccesser->getKineticModule().getEnergy(4));
        float max = soValueAccesser::getConstantFloat(moduleAccesser, 0xcec, 0);
        float min = soValueAccesser::getConstantFloat(moduleAccesser, 0xced, 0);
        Vec2f speed = normal->getSpeed();
        float length = calcLength(speed);
        if (length < min || max < min) {
            moduleAccesser->getCollisionAttackModule().clear(0);
        } else {
            float power = moduleAccesser->getWorkManageModule().getFloat(0x21000007);
            float scaled = power * ((length - min) / (max - min));
            if (scaled > power) {
                scaled = power;
            }
            moduleAccesser->getCollisionAttackModule().setPower(0, (int)scaled, false);
            float lr = moduleAccesser->getPostureModule().getLr();
            int angle = (int)(57.29578f * (float)atan2(speed.m_y, speed.m_x * -lr));
            if (angle < 0) {
                angle += 360;
            }
            moduleAccesser->getCollisionAttackModule().setVector(0, angle);
        }
    }
}

void ftStatusUniqProcessDamageFly::checkAttack(soModuleAccesser* moduleAccesser, void* collisionLog, float unk) {
    soCollisionLog* log = (soCollisionLog*)collisionLog;
    if (log->m_taskCategory == 10) {
        soKineticEnergyNormal* normal = &dynamic_cast<soKineticEnergyNormal&>(*moduleAccesser->getKineticModule().getEnergy(4));
        Vec2f speed = normal->getSpeed();
        Vec2f own = speed * soValueAccesser::getConstantFloat(moduleAccesser, 0xcee, 0);
        StageObject* other = &dynamic_cast<StageObject&>(*gfTaskScheduler::getInstance()->getTaskById(log->m_taskCategory, log->m_taskId));
        float myWeight = soValueAccesser::getConstantFloat(moduleAccesser, 0xbe1, 0);
        float ratio = myWeight / (myWeight + soExternalValueAccesser::getConstantFloat(other, 0xbe1));
        float t = 0.5f + (ratio - 0.5f) * soValueAccesser::getConstantFloat(moduleAccesser, 0xcef, 0);
        Vec2f share = own * t;
        Vec3f share3(share.m_x, share.m_y, 0.0f);
        soExternalValueAccesser::getKineticModule(other)->addSpeedOutside(soKineticEnergy::Outside_Damage_Reserved, &share3);
        Vec2f remain = own * (1.0f - t);
        Vec2f result = speed - remain;
        normal->m_speed.m_x = result.m_x;
        normal->m_speed.m_y = result.m_y;
    }
}

void ftStatusUniqProcessDamageFly::exitStatus(soModuleAccesser* moduleAccesser, int nextStatusKind) {
    moduleAccesser->getCameraModule().exitDamageFly(0);
    ftStatusUniqProcessDamage::exitStatus(moduleAccesser, nextStatusKind);
}
