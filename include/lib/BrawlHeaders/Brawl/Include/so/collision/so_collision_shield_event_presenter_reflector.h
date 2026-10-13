#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <so/collision/so_collision_log.h>

class soModuleAccesser;
class soCollisionAttackModule;
class soCollisionSearchModule;

class soCollisionReflectorEventObserver : public soEventObserver<soCollisionReflectorEventObserver> {
public:
    soCollisionReflectorEventObserver() : soEventObserver<soCollisionReflectorEventObserver>(0xf) {};
    soCollisionReflectorEventObserver(short unitID) : soEventObserver<soCollisionReflectorEventObserver>(unitID) {};
    soCollisionReflectorEventObserver(short, s8);

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventCollisionReflector(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual void notifyEventCollisionReflectorSearch(soCollisionSearchModule* searchModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionReflectorCheck();
};
static_assert(sizeof(soCollisionReflectorEventObserver) == 12, "Class is wrong size!");

