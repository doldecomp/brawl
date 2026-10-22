#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <so/collision/so_collision_log.h>

class soModuleAccesser;
class soCollisionAttackModule;
class soCollisionSearchModule;

class soCollisionShieldEventObserver : public soEventObserver<soCollisionShieldEventObserver> {
public:
    soCollisionShieldEventObserver() : soEventObserver<soCollisionShieldEventObserver>(0xe) {};
    soCollisionShieldEventObserver(short unitID) : soEventObserver<soCollisionShieldEventObserver>(unitID) {};
    soCollisionShieldEventObserver(short, s8);

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventCollisionShield(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual void notifyEventCollisionShieldSearch(soCollisionSearchModule* searchModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionShieldCheck();
};
static_assert(sizeof(soCollisionShieldEventObserver) == 12, "Class is wrong size!");

