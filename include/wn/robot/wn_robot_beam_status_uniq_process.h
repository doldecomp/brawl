#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// The only status of R.O.B.'s Robo Beam projectile: it flies straight and keeps pointing along its velocity.
class wnRobotBeamStatusUniqProcess : public soStatusUniqProcess {
public:
    virtual ~wnRobotBeamStatusUniqProcess() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
};

extern wnRobotBeamStatusUniqProcess g_wnRobotBeamStatusUniqProcess;
