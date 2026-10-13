#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <so/collision/so_collision_log.h>

class soModuleAccesser;
class soCollisionAttackModule;
class soCollisionSearchModule;

class soCollisionAbsorberEventObserver : public soEventObserver<soCollisionAbsorberEventObserver> {
public:
    soCollisionAbsorberEventObserver(short unitID) : soEventObserver<soCollisionAbsorberEventObserver>(unitID) {};

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventCollisionAbsorber(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual bool notifyEventCollisionAbsorberCheck();
};
static_assert(sizeof(soCollisionAbsorberEventObserver) == 12, "Class is wrong size!");
