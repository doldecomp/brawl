#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>

class StageObject;
class soModuleAccesser;

class soMotionEventObserver : public soEventObserver<soMotionEventObserver> {
public:
    soMotionEventObserver(short unitID) : soEventObserver<soMotionEventObserver>(unitID) {};

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventChangeMotion(int, int, void*, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soMotionEventObserver) == 12, "Class is wrong size!");
