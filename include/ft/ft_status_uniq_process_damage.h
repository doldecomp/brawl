#pragma once

#include <StaticAssert.h>
#include <so/status/so_status_module_impl.h>
#include <so/so_module_accesser.h>
#include <types.h>

// Hitstun / knockback status process shared by the "damage" statuses of a fighter.
// Slot order recovered from the ftStatusUniqProcessDamage vtable.
class ftStatusUniqProcessDamage : public soStatusUniqProcess {
public:
    ftStatusUniqProcessDamage() { }
    virtual ~ftStatusUniqProcessDamage() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatusKind);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
    virtual void leaveStop(soModuleAccesser* moduleAccesser, int unk, bool isHitStopEnd);
    virtual bool checkTransitionPrecede(soModuleAccesser* moduleAccesser, int* statusKind);

    virtual void initNormalDamage(soModuleAccesser* moduleAccesser);
    virtual void execNormalDamage(soModuleAccesser* moduleAccesser);
    virtual void initNormalDamageCommon(soModuleAccesser* moduleAccesser);
    virtual void execNormalDamageCommon(soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(ftStatusUniqProcessDamage) == 4, "Class is wrong size!");

extern ftStatusUniqProcessDamage g_ftStatusUniqProcessDamage;
