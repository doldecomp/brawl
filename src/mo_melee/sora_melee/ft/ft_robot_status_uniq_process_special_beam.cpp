#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/robot/ft_robot_status_uniq_process_special_beam.h>
#include <ft/fighter.h>
#include <so/so_module_accesser.h>
#include <math.h>
#include <types.h>

// Work variables (HYPOTHESIS names, from how the status uses them):
//   float 0x21000004  head tilt angle; follows the stick while aiming and eases back to 0 afterwards
//   flag  0x22000011  the stick may still tilt the head
//   flag  0x22000012  the head is being returned to rest
//   flag  0x22000013  cleared on entry

ftRobotStatusUniqProcessSpecialBeam g_ftRobotStatusUniqProcessSpecialBeam;

void ftRobotStatusUniqProcessSpecialBeam::initStatus(soModuleAccesser* moduleAccesser) {
    moduleAccesser->getWorkManageModule().onFlag(0x22000011);
    moduleAccesser->getWorkManageModule().offFlag(0x22000012);
    moduleAccesser->getWorkManageModule().offFlag(0x22000013);
}

void ftRobotStatusUniqProcessSpecialBeam::execStatus(soModuleAccesser* moduleAccesser) {
    float stick = -moduleAccesser->getControllerModule().getStickY();
    float zero = 0.0f;
    float tilt = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
    int stickRest = 0;
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000011)) {
        if (fabs(stick) > zero) {
            float step = stick * moduleAccesser->getConstantFloatKirby(0xfa2);
            float limit;
            if (stick > zero) {
                limit = moduleAccesser->getConstantFloatKirby(4000);
            } else {
                limit = -moduleAccesser->getConstantFloatKirby(0xfa1);
            }
            float next = tilt + step;
            tilt = next;
            if (fabs(next) > fabs(limit)) {
                tilt = limit;
            }
        } else {
            stickRest = 1;
        }
    }
    float result = tilt;
    if (stickRest || moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
        float decay = moduleAccesser->getConstantFloatKirby(0xfa3);
        if (tilt < 0.0f) {
            result = tilt + decay;
            if (result > 0.0f) {
                result = 0.0f;
            }
        } else {
            result = tilt;
            if (tilt > 0.0f) {
                result = tilt - decay;
                if (result < 0.0f) {
                    result = 0.0f;
                }
            }
        }
    }
    int node;
    if (moduleAccesser->getStageObject().soGetSubKind() == 5) {
        // Kirby wears R.O.B.'s head, so his node has to be mapped to the real one.
        soModelModule& model = moduleAccesser->getModelModule();
        node = model.getRealNodeId(model.getNodeId("ThrowN"));
    } else {
        node = moduleAccesser->getModelModule().getNodeId("NeckN");
    }
    Vec3f rot = moduleAccesser->getModelModule().getNodeRotate(node);
    rot.m_x = result;
    moduleAccesser->getModelModule().setNodeRotate(node, &rot);
    moduleAccesser->getWorkManageModule().setFloat(result, 0x21000004);
}

void ftRobotStatusUniqProcessSpecialBeam::exitStatus(soModuleAccesser*, int) { }
