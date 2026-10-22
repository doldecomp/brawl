#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>

class soModuleAccesser;

class soTurnEventObserver : public soEventObserver<soTurnEventObserver> {
public:
    soTurnEventObserver(short unitID) : soEventObserver<soTurnEventObserver>(unitID) {};

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventTurn(float, float, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soTurnEventObserver) == 12, "Class is wrong size!");