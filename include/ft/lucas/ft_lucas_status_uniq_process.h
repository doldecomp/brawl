#pragma once

#include <ft/lucas/ft_lucas_status_uniq_process_special_hi.h>

class soModuleAccesser;

// PSI Magnet's initial air-kinetic setup and the hold phase's effect/shield lifetime.
class ftLucasStatusUniqProcessSpecialLw : public soStatusUniqProcess {
public:
    virtual ~ftLucasStatusUniqProcessSpecialLw();
    virtual void initStatus(soModuleAccesser* moduleAccesser);
};

class ftLucasStatusUniqProcessSpecialLwHold : public soStatusUniqProcess {
public:
    virtual ~ftLucasStatusUniqProcessSpecialLwHold();
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
};

// The other Lucas status objects remain in the fighter's native module.
extern soStatusUniqProcess g_ftLucasStatusUniqProcessSpecialS;
extern soStatusUniqProcess g_ftLucasStatusUniqProcessAttackS4;
extern soStatusUniqProcess g_ftLucasStatusUniqProcessAirLasso;
extern ftLucasStatusUniqProcessSpecialLw g_ftLucasStatusUniqProcessSpecialLw;
extern ftLucasStatusUniqProcessSpecialLwHold g_ftLucasStatusUniqProcessSpecialLwHold;
extern ftLucasStatusUniqProcessSpecialHi g_ftLucasStatusUniqProcessSpecialHi;
extern ftLucasStatusUniqProcessSpecialHiAttack g_ftLucasStatusUniqProcessSpecialHiAttack;
extern ftLucasStatusUniqProcessSpecialHiAttackEnd g_ftLucasStatusUniqProcessSpecialHiAttackEnd;
extern ftLucasStatusUniqProcessSpecialHiReflect g_ftLucasStatusUniqProcessSpecialHiReflect;

// These shared aerial transitions are identified by their native RTTI.
extern soStatusUniqProcess g_ftStatusUniqProcessAttackAirInheritJumpAerialMotion;
extern soStatusUniqProcess g_ftStatusUniqProcessEscapeAirInheritJumpAerialMotion;
