#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

class ftYoshiStatusUniqProcessSpecialLw : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialLw() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
};

class ftYoshiStatusUniqProcessSpecialAirLw : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialAirLw() { }
    virtual void execStatus(soModuleAccesser* moduleAccesser);
};

extern ftYoshiStatusUniqProcessSpecialLw g_ftYoshiStatusUniqProcessSpecialLw;
extern ftYoshiStatusUniqProcessSpecialAirLw g_ftYoshiStatusUniqProcessSpecialAirLw;

class ftYoshiStatusUniqProcessSpecialHi : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialHi() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
};
extern ftYoshiStatusUniqProcessSpecialHi g_ftYoshiStatusUniqProcessSpecialHi;

#include <ft/ft_status_uniq_process_guard.h>
class ftYoshiStatusUniqProcessGuardFunc : public ftStatusUniqProcessGuardFunc {
public:
    virtual ~ftYoshiStatusUniqProcessGuardFunc() {}
    virtual void updateShield(soModuleAccesser*);
    virtual void setShieldScale(soModuleAccesser*);
    static ftYoshiStatusUniqProcessGuardFunc* getInstance();
};
class ftYoshiStatusUniqProcessGuardOn : public ftStatusUniqProcessGuardOn {
public:
    virtual ~ftYoshiStatusUniqProcessGuardOn() {}
    ftYoshiStatusUniqProcessGuardOn(ftStatusUniqProcessGuardFunc* helper) : ftStatusUniqProcessGuardOn(helper) {}
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftYoshiStatusUniqProcessGuard : public ftStatusUniqProcessGuard {
public:
    ftYoshiStatusUniqProcessGuard(ftStatusUniqProcessGuardFunc* helper) : ftStatusUniqProcessGuard(helper) {}
    virtual ~ftYoshiStatusUniqProcessGuard() {}
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftYoshiStatusUniqProcessGuardDamage : public ftStatusUniqProcessGuardDamage {
public:
    ftYoshiStatusUniqProcessGuardDamage(ftStatusUniqProcessGuardFunc* helper) : ftStatusUniqProcessGuardDamage(helper) {}
    virtual ~ftYoshiStatusUniqProcessGuardDamage() {}
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftYoshiStatusUniqProcessEscapeFB : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessEscapeFB() {}
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftYoshiStatusUniqProcessJumpAerial : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessJumpAerial() {}
    virtual void execStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};

extern ftYoshiStatusUniqProcessGuardFunc g_ftYoshiStatusUniqProcessGuardFunc;
inline ftYoshiStatusUniqProcessGuardFunc* ftYoshiStatusUniqProcessGuardFunc::getInstance() {
    return &g_ftYoshiStatusUniqProcessGuardFunc;
}

#include <ft/ft_status_uniq_process_catch_pull.h>
class ftYoshiStatusUniqProcessCatchPull : public ftStatusUniqProcessCatchPull {
public:
    virtual ~ftYoshiStatusUniqProcessCatchPull() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};

// Egg Roll's shared behavior is also called by its hit callbacks.
class ftYoshiStatusUniqProcessSpecialSUtility {
public:
    static bool checkLife(soModuleAccesser*);
    static bool checkCancel(soModuleAccesser*);
    static void setBodyChange(soModuleAccesser*);
    static void setBodyScale(soModuleAccesser*);
    static void resetYoshiSpecialS(soModuleAccesser*);
    static void resetYoshiSpecialS2(soModuleAccesser*);
    static void audioDash(soModuleAccesser*);
    static void procHit(soModuleAccesser*);
    static void procHitWall(soModuleAccesser*, int);
    static bool getFlick(soModuleAccesser*);
    static void setRot(soModuleAccesser*);
    static void setAttack(soModuleAccesser*);
    static void setPower(soModuleAccesser*);
};
class ftYoshiStatusUniqProcessSpecialSStart : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialSStart() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPosCounter(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftYoshiStatusUniqProcessSpecialSLoop : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialSLoop() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPosCounter(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftYoshiStatusUniqProcessSpecialSEnd : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialSEnd() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPosCounter(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftYoshiStatusUniqProcessSpecialAirSJump : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialAirSJump() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPosCounter(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftYoshiStatusUniqProcessSpecialSTurn : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialSTurn() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPosCounter(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};
