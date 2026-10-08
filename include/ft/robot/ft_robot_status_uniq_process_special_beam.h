#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// R.O.B.'s Robo Beam (neutral special) aiming process. Kirby's copy of the move uses the same process,
// which is why the move constants are read through the "Kirby" accessors.
class ftRobotStatusUniqProcessSpecialBeam : public soStatusUniqProcess {
public:
    virtual ~ftRobotStatusUniqProcessSpecialBeam() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
};

extern ftRobotStatusUniqProcessSpecialBeam g_ftRobotStatusUniqProcessSpecialBeam;
