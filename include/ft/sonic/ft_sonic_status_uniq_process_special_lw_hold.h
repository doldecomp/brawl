#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// Sonic's down-special charge process; original class name and vtable identify this phase.
class ftSonicStatusUniqProcessSpecialLwHold : public soStatusUniqProcess {
public:
    virtual ~ftSonicStatusUniqProcessSpecialLwHold() {}
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
    static void limitRotSpeed(soModuleAccesser* moduleAccesser);
    static void syncMotionRate(soModuleAccesser* moduleAccesser);
};

extern ftSonicStatusUniqProcessSpecialLwHold g_ftSonicStatusUniqProcessSpecialLwHold;
