#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// The opening of R.O.B.'s Robo Burner: converts whatever speed the fighter had into the thrust energies and starts
// the flame effects. The thrust itself runs in ftRobotStatusUniqProcessSpecialBurner.
class ftRobotStatusUniqProcessSpecialBurnerStart : public soStatusUniqProcess {
public:
    virtual ~ftRobotStatusUniqProcessSpecialBurnerStart() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
};

extern ftRobotStatusUniqProcessSpecialBurnerStart g_ftRobotStatusUniqProcessSpecialBurnerStart;
