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

#ifdef FT_MODULE_BUILDER
    virtual void addObserver(short param1, s8 param2) { addObserverSub(param1, this, param2); } // MATCH-ONLY: inline in the REL
#else
    virtual void addObserver(short param1, s8 param2);
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventCollisionHit(float power, soCollisionAttackData*, u32 index, int, soModuleAccesser* moduleAccesser, soCollisionLog*) { }
#else
    virtual void notifyEventCollisionHit(float power, soCollisionAttackData*, u32 index, int, soModuleAccesser* moduleAccesser, soCollisionLog*);
#endif
    virtual void notifyEventCollisionHit2nd(float posX, float collisionLr, soCollisionAttackModule*, soCollisionLog*, u32 groupIndex, soModuleAccesser* moduleAccesser, bool) { }
    virtual void notifyEventChangeCollisionHit(int index, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soCollisionHitEventObserver) == 12, "Class is wrong size!");
