#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <so/collision/so_collision_attack_part.h>
#include <mt/mt_vector.h>
#include <types.h>

class soModuleAccesser;

// Vtable order recovered from the soDamageEffectorImpl vtable (slot -> map name) and the
// call sites in soDamageTransactorActor (argument lists).
// HYPOTHESIS: the parameter lists are inferred from the call sites; the slot at +0x28 is
// pure virtual in soDamageEffectorImpl and its name here is a guess.
class soDamageEffector : public soNull, public soNullable {
public:
    virtual ~soDamageEffector() { }
    virtual void reqShake(soModuleAccesser* moduleAccesser, int situation, Vec2f* normal, soCollisionAttackData* attackData, int hitStopFrame);
    virtual void reqCommonEffect();
    virtual void reqUniqEffect(soModuleAccesser* moduleAccesser, int level, soCollisionAttackData* attackData);
    virtual void reqInvincibleEffect();
    virtual void reqDamageEffectParam(float damageAdd, float reaction, soModuleAccesser* moduleAccesser, soCollisionAttackData* attackData);
    virtual void reqDamageGroundBeatDownEffect(soModuleAccesser* moduleAccesser, Vec2f* normal);
    virtual void reqQuake(float frameReaction, soModuleAccesser* moduleAccesser, int level);
    virtual void reqStop();
    virtual void reqTipEffect();
};
