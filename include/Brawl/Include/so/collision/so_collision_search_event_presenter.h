#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <so/collision/so_collision_log.h>

class soModuleAccesser;

class soCollisionSearchEventObserver : public soEventObserver<soCollisionSearchEventObserver> {
public:
    soCollisionSearchEventObserver() : soEventObserver<soCollisionSearchEventObserver>(0x11) {};
    soCollisionSearchEventObserver(short unitID) : soEventObserver<soCollisionSearchEventObserver>(unitID) {};
    soCollisionSearchEventObserver(short, s8);

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventCollisionSearch(soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionSearchCheck();
};
static_assert(sizeof(soCollisionSearchEventObserver) == 12, "Class is wrong size!");
