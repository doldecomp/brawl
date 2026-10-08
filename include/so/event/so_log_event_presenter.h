#pragma once

// Local shadow of BrawlHeaders' so/event/so_log_event_presenter.h: the original plus the constructor of
// soLogEventObserver (registers with the log event manager through the virtual addObserver) and the declaration of
// that manager's static instance.

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <so/event/so_event_manage_module_impl.h>
#include <types.h>

// HYPOTHESIS: name of the static event manager of sologeventmanager.cpp (entity, then an soEventManageModuleImpl at 0x28)
class soLogEventManagerStatic {
public:
    char _0[0x28];
    soEventManageModuleImpl m_module;
    char _3c[0x38];
};
static_assert(sizeof(soLogEventManagerStatic) == 0x74, "Class is wrong size!");
extern soLogEventManagerStatic g_soLogEventManager;

class soLogEventObserver : public soEventObserver<soDisposeInstanceEventObserver> {
public:
    soLogEventObserver() : soEventObserver<soDisposeInstanceEventObserver>(0) {
        initialize(g_soLogEventManager.m_module.getManageId(), -1);
    }

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyLogEventCollisionHit(float, int taskId1, int taskId2, int);
    virtual void notifyLogEventGroundDamage(); // TODO
    virtual void notifyLogEventDead(int entryId1, int entryId2, int, int);
    char _spacer1[2];
};
static_assert(sizeof(soLogEventObserver) == 12, "Class is wrong size!");
