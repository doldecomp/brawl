#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <so/collision/so_collision_log.h>
#include <so/collision/so_collision_attack_part.h>

class soModuleAccesser;
class soCollisionAttackModule;

class soCollisionHitEventObserver : public soEventObserver<soCollisionHitEventObserver> {
public:
    soCollisionHitEventObserver(short unitID) : soEventObserver<soCollisionHitEventObserver>(unitID) {};
    // (manageId, p2) constructor added by agent/damage
    soCollisionHitEventObserver(short manageId, s8 p2) : soEventObserver<soCollisionHitEventObserver>(0x0) { initialize(manageId, p2); }

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventCollisionHit(float power, soCollisionAttackData*, u32 index, int, soModuleAccesser* moduleAccesser, soCollisionLog*);
    virtual void notifyEventCollisionHit2nd(float posX, float collisionLr, soCollisionAttackModule*, soCollisionLog*, u32 groupIndex, soModuleAccesser* moduleAccesser, bool) { }
    virtual void notifyEventChangeCollisionHit(int index, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soCollisionHitEventObserver) == 12, "Class is wrong size!");
