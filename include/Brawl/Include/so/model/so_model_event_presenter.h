#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>

class soModuleAccesser;

class soModelEventObserver : public soEventObserver<soModelEventObserver> {
public:
    soModelEventObserver(short unitID) : soEventObserver<soModelEventObserver>(unitID) {};

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventConstructInstance(bool, soModuleAccesser* moduleAccesser);
    virtual void notifyEventDestructInstance(soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soModelEventObserver) == 12, "Class is wrong size!");
