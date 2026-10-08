#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// R.O.B.'s Robo Burner (up special): a thrust that burns fuel while the special button (or up on the stick) is held.
// The shared thrust logic lives here; ftRobotStatusUniqProcessSpecialBurnerStart/Attack call it too.
class ftRobotStatusUniqProcessSpecialBurner : public soStatusUniqProcess {
public:
    virtual ~ftRobotStatusUniqProcessSpecialBurner() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);

    static void specialButtonPushCheck(soModuleAccesser* moduleAccesser);
    static void controlBurner(soModuleAccesser* moduleAccesser, bool consumeFuel);
    static void controlEffect(soModuleAccesser* moduleAccesser);
    static void controlRumble(soModuleAccesser* moduleAccesser);
};

extern ftRobotStatusUniqProcessSpecialBurner g_ftRobotStatusUniqProcessSpecialBurner;
