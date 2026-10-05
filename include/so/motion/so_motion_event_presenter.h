#pragma once
// SHADOW of BrawlHeaders/so/motion/so_motion_event_presenter.h: addObserver is inline in the fighter RELs (FT_MODULE_BUILDER)

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>

class StageObject;
class soModuleAccesser;

class soMotionEventObserver : public soEventObserver<soMotionEventObserver> {
public:
    soMotionEventObserver(short unitID) : soEventObserver<soMotionEventObserver>(unitID) {};

#ifdef FT_MODULE_BUILDER
    virtual void addObserver(short param1, s8 param2) { addObserverSub(param1, this, param2); } // MATCH-ONLY: inline in the REL
#else
    virtual void addObserver(short param1, s8 param2);
#endif
    virtual void notifyEventChangeMotion(int, int, void*, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soMotionEventObserver) == 12, "Class is wrong size!");
