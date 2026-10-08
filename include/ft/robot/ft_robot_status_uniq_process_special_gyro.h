#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// R.O.B.'s Gyro (down special): the same process serves the three statuses of the move (0x11b charge, 0x11c hold,
// 0x11d throw), the last one drops the gyro item on the stage.
class ftRobotStatusUniqProcessSpecialGyro : public soStatusUniqProcess {
public:
    virtual ~ftRobotStatusUniqProcessSpecialGyro() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
};

extern ftRobotStatusUniqProcessSpecialGyro g_ftRobotStatusUniqProcessSpecialGyro;
