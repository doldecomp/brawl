#pragma once

#include <so/so_module_accesser.h>
#include <so/status/so_status_module_impl.h>
#include <types.h>

// Shield (guard) status processes. No header exists in BrawlHeaders; declared from the
// vtables / call sites in the sora_melee REL.

// Shared helper for the guard status processes (shield scaling / hit-stop delay handling).
// Single global instance (lbl_27_bss_4994), referenced by pointer from every guard process.
class ftStatusUniqProcessGuardFunc {
public:
    virtual ~ftStatusUniqProcessGuardFunc() { }
    virtual void updateShield(soModuleAccesser* moduleAccesser);
    virtual void setShieldScale(soModuleAccesser* moduleAccesser);
    virtual void checkHitStopDelay(soModuleAccesser* moduleAccesser);
    virtual void checkHitStopDelayFlick(soModuleAccesser* moduleAccesser);
};

extern ftStatusUniqProcessGuardFunc g_ftStatusUniqProcessGuardFunc;

// Status process for raising the shield (GuardOn); also the base of the other two.
class ftStatusUniqProcessGuardOn : public soStatusUniqProcess {
public:
    ftStatusUniqProcessGuardFunc* m_guardFunc;

    ftStatusUniqProcessGuardOn() : m_guardFunc(&g_ftStatusUniqProcessGuardFunc) { }
    ftStatusUniqProcessGuardOn(ftStatusUniqProcessGuardFunc* helper) : m_guardFunc(helper) {}
    virtual ~ftStatusUniqProcessGuardOn() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
    virtual void leaveStop(soModuleAccesser* moduleAccesser, int, bool);
};

// Status process while the shield is held (Guard).
class ftStatusUniqProcessGuard : public ftStatusUniqProcessGuardOn {
public:
    ftStatusUniqProcessGuard() {}
    ftStatusUniqProcessGuard(ftStatusUniqProcessGuardFunc* helper) : ftStatusUniqProcessGuardOn(helper) {}
    virtual ~ftStatusUniqProcessGuard() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
};

extern ftStatusUniqProcessGuard g_ftStatusUniqProcessGuard;

// Status process for the shield being hit (GuardDamage / shield stun).
class ftStatusUniqProcessGuardDamage : public ftStatusUniqProcessGuardOn {
public:
    ftStatusUniqProcessGuardDamage() {}
    ftStatusUniqProcessGuardDamage(ftStatusUniqProcessGuardFunc* helper) : ftStatusUniqProcessGuardOn(helper) {}
    virtual ~ftStatusUniqProcessGuardDamage() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
};

extern ftStatusUniqProcessGuardDamage g_ftStatusUniqProcessGuardDamage;
