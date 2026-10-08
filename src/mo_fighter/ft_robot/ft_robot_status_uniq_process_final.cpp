#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/robot/ft_robot_status_uniq_process_final.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>

// Work variables (HYPOTHESIS names, from how ftRobot::updateFinal uses them):
//   flag 0x12000042 / 0x12000043  Final Smash phases that updateFinal watches (cleared together when it ends)
//   int  0x10000042               frames left in the Final Smash, counted down by updateFinal while 0x12000043 is set
//   int  0x10000043               startup countdown, ticked by updateFinal once 0x12000045 is set
void ftRobotStatusUniqProcessFinal::initStatus(soModuleAccesser* moduleAccesser) {
    moduleAccesser->getWorkManageModule().onFlag(0x12000042);
    moduleAccesser->getWorkManageModule().setInt(soValueAccesser::getConstantInt(moduleAccesser, 0x5dcc, 0), 0x10000043);
}

// Nothing to do per frame: ftRobot::updateFinal runs the Final Smash countdown.
void ftRobotStatusUniqProcessFinal::execStatus(soModuleAccesser* moduleAccesser) { }

// Leaving the Final status for Wait (0) or Fall (0xE) arms the Final Smash timer: the constant is in seconds.
// HYPOTHESIS: 0 and 0xE are the grounded/aerial end states.
void ftRobotStatusUniqProcessFinal::exitStatus(soModuleAccesser* moduleAccesser, int nextStatus) {
    switch (nextStatus) {
    case 0xE:
    case 0:
        moduleAccesser->getWorkManageModule().onFlag(0x12000043);
        moduleAccesser->getWorkManageModule().setInt(soValueAccesser::getConstantInt(moduleAccesser, 0x5dc9, 0) * 60, 0x10000042);
        break;
    }
}

ftRobotStatusUniqProcessFinal g_ftRobotStatusUniqProcessFinal;
