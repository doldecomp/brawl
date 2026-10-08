#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// R.O.B.'s Final Smash status. The status itself is a thin shell: it starts and stops the countdown work variables
// that ftRobot::updateFinal ticks every frame.
class ftRobotStatusUniqProcessFinal : public soStatusUniqProcess {
public:
    virtual ~ftRobotStatusUniqProcessFinal() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
};

extern ftRobotStatusUniqProcessFinal g_ftRobotStatusUniqProcessFinal;
