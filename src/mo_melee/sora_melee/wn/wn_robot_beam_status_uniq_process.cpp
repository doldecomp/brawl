#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/robot/wn_robot_beam_status_uniq_process.h>
#include <so/so_module_accesser.h>
#include <math.h>
#include <types.h>

wnRobotBeamStatusUniqProcess g_wnRobotBeamStatusUniqProcess;

// Turns the beam model around X so that it points along the direction it is travelling in.
static inline void alignToVelocity(soModuleAccesser* moduleAccesser) {
    Vec3f rot = moduleAccesser->getPostureModule().getRot(0);
    Vec2f velocity;
    Vec2f::copy(velocity, moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
    velocity.normalize();
    float lr = moduleAccesser->getPostureModule().getLr();
    float vy = velocity.m_y;
    float forward = velocity.m_x * lr;
    float angle = (float)atan2(vy, forward);
    rot.m_x = -angle * 57.29578f;
    moduleAccesser->getPostureModule().setRot(&rot, 0);
}

void wnRobotBeamStatusUniqProcess::initStatus(soModuleAccesser* moduleAccesser) {
    // The beam stops when it touches the stage.
    moduleAccesser->getGroundModule().setTestCollStopStatus(true, 0);
}

void wnRobotBeamStatusUniqProcess::execStatus(soModuleAccesser* moduleAccesser) {
    alignToVelocity(moduleAccesser);
}

void wnRobotBeamStatusUniqProcess::execFixPos(soModuleAccesser*) { }

void wnRobotBeamStatusUniqProcess::execStop(soModuleAccesser* moduleAccesser) {
    alignToVelocity(moduleAccesser);
}
