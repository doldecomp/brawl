#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// R.O.B.'s Arm Rotor (side special): the arms spin like a helicopter rotor, giving a short horizontal and vertical lift.
// The same process serves the ground status (0x113, windup) and the air/spin status (0x117).
class ftRobotStatusUniqProcessSpecialArmSpin : public soStatusUniqProcess {
public:
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);

    // HYPOTHESIS: called when the spinning arms connect with something; the spin loses some of its power.
    void setEventCollisionAttack(soModuleAccesser* moduleAccesser);
};

extern ftRobotStatusUniqProcessSpecialArmSpin g_ftRobotStatusUniqProcessSpecialArmSpin;
