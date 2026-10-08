#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// The Robo Burner status that runs while the fighter is already thrusting (the attack part of the up special).
// It shares the thrust logic of ftRobotStatusUniqProcessSpecialBurner but does not drive the rumble itself.
class ftRobotStatusUniqProcessSpecialBurnerAttack : public soStatusUniqProcess {
public:
    virtual ~ftRobotStatusUniqProcessSpecialBurnerAttack() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
};

extern ftRobotStatusUniqProcessSpecialBurnerAttack g_ftRobotStatusUniqProcessSpecialBurnerAttack;
