#pragma once

// Local shadow of BrawlHeaders' so/so_dispose_instance_manager.h: the original plus a constructor for
// soDisposeInstanceEventObserver (the fighter manager constructs one as a base; the constructor registers
// through the virtual addObserver, as the fighter manager constructor shows).

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <types.h>

class soDisposeInstanceManager {
    u8 unk0[0xD0C];

public:
    virtual void notifyDrawDone();

    // Dynamically allocate and populate *g_soDisposeInstanceManager
    static void create();
};
static_assert(sizeof(soDisposeInstanceManager) == 0xD10, "Class is wrong size!");

class soDisposeInstanceEventObserver : public soEventObserver<soDisposeInstanceEventObserver> {
public:
    soDisposeInstanceEventObserver() : soEventObserver<soDisposeInstanceEventObserver>(0) {
        initialize(-1, -1);
    }

    virtual void addObserver(short param1, s8 param2);
    virtual bool isObserv(); // TODO
    virtual void notifyDisposeInstance(bool, int, int taskId);
    virtual void notifyDrawDone(); // TODO
    char _spacer1[2];
};
static_assert(sizeof(soDisposeInstanceEventObserver) == 12, "Class is wrong size!");

extern soDisposeInstanceManager* g_soDisposeInstanceManager;
