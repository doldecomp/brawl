#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <so/so_common_data_accesser.h>

class soModuleAccesser;

class soCollisionCatchEventObserver : public soEventObserver<soCollisionCatchEventObserver> {
public:
    soCollisionCatchEventObserver(s16 unitID) :
        soEventObserver<soCollisionCatchEventObserver>(unitID) { }

    virtual void addObserver(s16 param1, s8 param2);
    virtual void notifyEventTurn(float, float, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soCollisionCatchEventObserver) == 0xC, "Class is wrong size!");
