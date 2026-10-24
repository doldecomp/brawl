#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <so/event/so_event_manage_module_impl.h>
#include <sr/sr_common.h>
#include <types.h>

class soCollisionManager : public gfTask {
    u8 unk40[0x894];
    soEventManageModuleImpl unk8D4;
    u8 unk8E8[0xC20];
public:
    soCollisionManager();

    soEventManageModule& getEventManageModule() { return unk8D4; }

    static soCollisionManager* get() {
        if (!g_soCollisionManager)
            g_soCollisionManager = new (Heaps::System) soCollisionManager;
        return g_soCollisionManager;
    }

    static soCollisionManager* g_soCollisionManager;
};
static_assert(sizeof(soCollisionManager) == 0x1508, "Class is the wrong size!");
