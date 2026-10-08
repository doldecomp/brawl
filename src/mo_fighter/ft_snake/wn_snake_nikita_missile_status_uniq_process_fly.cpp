// MATCH-ONLY: retain the native Fly energy-vector assignment calls.
#define MT_VEC2F_ASSIGN_NOINLINE
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/snake/wn_snake_nikita_missile_status_uniq_process_fly.h>
#include <wn/snake/so_kinetic_energy_local_normal.h>
#include <so/so_module_accesser.h>
#include <snd/snd_id.h>
#include <so/so_kinetic_energy_rot_normal.h>
#include <math.h>

wnSnakeNikitaMissileStatusUniqProcessFly g_wnSnakeNikitaMissileStatusUniqProcessFly;

void soKineticEnergyRotNormal::setStableSpeed(Vec3f* speed) {
    m_speedTarget.m_x = speed->m_x;
    m_speedTarget.m_y = speed->m_y;
    m_speedTarget.m_z = speed->m_z;
}

wnSnakeNikitaMissileStatusUniqProcessFly::wnSnakeNikitaMissileStatusUniqProcessFly() {}

wnSnakeNikitaMissileStatusUniqProcessFly::~wnSnakeNikitaMissileStatusUniqProcessFly() {}

void wnSnakeNikitaMissileStatusUniqProcessFly::initStatus(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    work.setInt(0, 0x20000003);
}

void wnSnakeNikitaMissileStatusUniqProcessFly::processSoundEffect(
    soModuleAccesser* moduleAccesser,
    float turnDelta
) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    if (work.getInt(0x20000003) > 0) {
        work.decInt(0x20000003);
        return;
    }

    // HYPOTHESIS: the five-degree threshold gates the missile's turn sound.
    if (static_cast<float>(fabs(turnDelta)) <= 5.0f) {
        return;
    }

    moduleAccesser->getSoundModule().playSE(snd_se_snake_019, false, 0, 0);
    moduleAccesser->getWorkManageModule().setInt(10, 0x20000003);
}

void wnSnakeNikitaMissileStatusUniqProcessFly::execStatus(soModuleAccesser* moduleAccesser) {
    soKineticEnergy* localBase = moduleAccesser->getKineticModule().getEnergy(2);
    soKineticEnergyLocalNormal* localEnergy =
        dynamic_cast<soKineticEnergyLocalNormal*>(localBase);
    soKineticEnergy* rotationBase = moduleAccesser->getKineticModule().getEnergy(1);
    soKineticEnergyRotNormal* rotationEnergy =
        dynamic_cast<soKineticEnergyRotNormal*>(rotationBase);
    if (localEnergy == 0 || rotationEnergy == 0) {
        return;
    }

    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    soControllerModule& controller = moduleAccesser->getControllerModule();
    float oldScalar = localEnergy->unk34;

    if (work.getInt(0x10000006) >= 0) {
        work.decInt(0x10000006);
        localEnergy->unk34 += work.getFloat(0x11000001);
        work.setFloat(oldScalar, 0x21000002);

        Vec3f target(-localEnergy->unk34, 90.0f, 0.0f);
        rotationEnergy->setStableSpeed(&target);
    } else if (controller.getStickPrevX() != 0.0f ||
               controller.getStickPrevY() != 0.0f) {
        float turnDelta = controller.getStickDir() * 57.29578f - localEnergy->unk34;
        if (turnDelta != 0.0f) {
            if (turnDelta < -180.0f) {
                turnDelta += 360.0f;
            } else if (turnDelta > 180.0f) {
                turnDelta -= 360.0f;
            }

            float maxTurn = work.getFloat(0x21000004);
            float turn = 0.0f;
            if (!(fabsf(turnDelta) <= maxTurn)) {
                turn = turnDelta < 0.0f ? -maxTurn : maxTurn;
            }
            if (fabsf(turnDelta) < work.getFloat(0x21000001)) {
                turn *= 0.5f;
            }

            float nextScalar = localEnergy->unk34 + turn;
            if (static_cast<float>(fabs(nextScalar)) >= 360.0f) {
                nextScalar += nextScalar < 0.0f ? 360.0f : -360.0f;
            }
            localEnergy->unk34 = nextScalar;

            Vec3f target(-(turn + nextScalar), 90.0f, 0.0f);
            rotationEnergy->setStableSpeed(&target);
        }
        processSoundEffect(moduleAccesser, turnDelta);
    }

    float lowerLimit = work.getFloat(0x21000004);
    float upperLimit = work.getFloat(0x21000003);
    if (oldScalar != localEnergy->unk34) {
        Vec2f target(lowerLimit, 0.0f);
        localEnergy->m_speedTarget = target;

        if (!work.isFlag(0x22000000)) {
            float lowSpeed = work.getFloat(0x11000002);
            float highSpeed = work.getFloat(0x11000003);
            Vec2f speed = localEnergy->getSpeed();
            float speedTarget;
            if (speed.m_x <= lowerLimit) {
                speedTarget = highSpeed;
            } else if (speed.m_x >= upperLimit) {
                speedTarget = lowSpeed;
            } else {
                Vec3f rotation = rotationEnergy->getRotation();
                float blend = (rotation.m_y - lowerLimit) / (upperLimit - lowerLimit);
                speedTarget = lowSpeed * blend + highSpeed * (1.0f - blend);
            }

            Vec3f stableSpeed(0.0f, 0.0f, speedTarget);
            rotationEnergy->setStableSpeed(&stableSpeed);
        }
    } else {
        Vec2f target(upperLimit, 0.0f);
        localEnergy->m_speedTarget = target;
        if (!work.isFlag(0x22000000)) {
            Vec3f stableSpeed(0.0f, 0.0f, work.getFloat(0x11000002));
            rotationEnergy->setStableSpeed(&stableSpeed);
        }
    }

    if (work.getInt(0x20000000) == 0) {
        Vec2f zero(0.0f, 0.0f);
        localEnergy->m_accel = zero;
        localEnergy->m_speedTarget = zero;
        work.decInt(0x20000000);
        Vec3f stableSpeed(0.0f, 0.0f, work.getFloat(0x11000002));
        rotationEnergy->setStableSpeed(&stableSpeed);
        work.onFlag(0x22000000);
    }
}
