#pragma once

#include <StaticAssert.h>
#include <so/status/so_status_module_impl.h>
#include <so/so_module_accesser.h>

// Yoshi's Egg status process. The override set and order are recovered from the
// native vtable at sora_melee.data+0x31320.
class ftStatusUniqProcessYoshiEgg : public soStatusUniqProcess {
public:
    virtual ~ftStatusUniqProcessYoshiEgg() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatusKind);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPosCounter(soModuleAccesser* moduleAccesser);
    virtual bool checkDamage(soModuleAccesser* moduleAccesser, void* collisionLog);
};
static_assert(sizeof(ftStatusUniqProcessYoshiEgg) == 4, "Class is the wrong size!");

extern ftStatusUniqProcessYoshiEgg g_ftStatusUniqProcessYoshiEgg;
