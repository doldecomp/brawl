#pragma once

#include <so/damage/so_damage_transactor_actor.h>

class wnWarioBikeDamageTransactorImpl : public soDamageTransactorActor {
public:
    virtual ~wnWarioBikeDamageTransactorImpl();

    virtual int getDamageValueParam(soModuleAccesser* moduleAccesser);
    virtual bool onDamageChangeStatusRequest(int statusKind, soModuleAccesser* moduleAccesser, soDamageLog* damageLog);
    virtual int getDamageStatusKind(soModuleAccesser* moduleAccesser);
    virtual bool isUseTurnDamage(soModuleAccesser* moduleAccesser);
    virtual bool isUseTurn(soModuleAccesser* moduleAccesser);
    virtual bool isApplyTurnDamage(soModuleAccesser* moduleAccesser);
    virtual int getDamageHeight(soModuleAccesser* moduleAccesser, u8 damageIndex);
    virtual float getHitStopMul(soModuleAccesser* moduleAccesser);
    virtual bool isSlip(soModuleAccesser* moduleAccesser, float slipChance);
    virtual bool isSleepStatus(soModuleAccesser* moduleAccesser);
    virtual bool isParalyzeDamage(soModuleAccesser* moduleAccesser);
    virtual void addSleepTime(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog);
    virtual void onFlowerDamage(soModuleAccesser* moduleAccesser, soDamage* damage);
    virtual void onParalyzeDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog);
    virtual void setFlagDownDamage3(soModuleAccesser* moduleAccesser, bool flag);
    virtual bool isCheckGroundDamage(soModuleAccesser* moduleAccesser);
    virtual void onGroundDamageAfter(soModuleAccesser* moduleAccesser);
    virtual bool onCompositionDamageSpeed(soModuleAccesser* moduleAccesser, soDamage* damage, Vec2f* speed, int level);
    virtual void setupDamageStatusNormal(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog, int unk);
    virtual void setupDamageStatusTurn(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog);
    virtual void setupSpeedDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog);
    virtual void setupDamageStatusNoReaction(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog);
    virtual void setupDamageFlyRollStatus(float angle, float speed, soModuleAccesser* moduleAccesser, soDamageLog* damageLog);
    virtual float getReactionSub(soModuleAccesser* moduleAccesser);
    virtual float getReactionMul(soModuleAccesser* moduleAccesser);
    virtual float getDamageMul(soModuleAccesser* moduleAccesser);
    virtual void checkCheer(float reaction, float angle, soModuleAccesser* moduleAccesser, soDamageLog* damageLog);
    virtual float getDamageForReaction(float damage, soModuleAccesser* moduleAccesser);
    virtual bool isSpeedDamage(soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(wnWarioBikeDamageTransactorImpl) == 4, "Class is wrong size!");
