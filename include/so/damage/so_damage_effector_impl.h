#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <so/collision/so_collision_attack_part.h>
#include <mt/mt_vector.h>
#include <types.h>

class soModuleAccesser;

// Vtable order recovered from the soDamageEffectorImpl vtable and the call sites in
// soDamageTransactorActor. Parameter lists are inferred from the call sites.
// HYPOTHESIS: names of the slots follow the map (reqShake/reqCommonEffect/...) but the
// mapping slot -> name for the overridden (non-stub) ones is a guess.
class soDamageEffector : public soNull, public soNullable {
public:
    virtual ~soDamageEffector() { }
    virtual void reqShake();
    virtual void reqCommonEffect();
    virtual void reqUniqEffect(soModuleAccesser* moduleAccesser, int level, Vec2f* speed, soCollisionAttackData* attackData, int hitStopFrame);
    virtual void reqInvincibleEffect();
    virtual void reqCommonEffectParam(soModuleAccesser* moduleAccesser, int level, soCollisionAttackData* attackData);
    virtual void reqDamageGroundBeatDownEffect();
    virtual void reqQuake(float damage, float reaction, soModuleAccesser* moduleAccesser, soCollisionAttackData* attackData);
    virtual void reqStop();
    virtual void reqTipEffect(float reaction, soModuleAccesser* moduleAccesser, int level);
};
