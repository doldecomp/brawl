#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <so/damage/so_damage.h>
#include <types.h>

class soModuleAccesser;

// Interface implemented by the per-StageObject-kind damage transactors
// (ftDamageTransactorImpl, itDamageTransactorImpl, soDamageTransactorNull ...).
// The vtable order below was recovered from the itDamageTransactorImpl vtable
// and the call sites in soDamageTransactorActor.
// HYPOTHESIS: parameter lists of the slots that soDamageTransactorActor does not
// call itself are guesses; only the slot order is confirmed.
class soDamageTransactor {
public:
    virtual ~soDamageTransactor() { }
    virtual int getDamageValueParam(soModuleAccesser* moduleAccesser) = 0;
    virtual bool onDamageChangeStatusRequest(int statusKind, soModuleAccesser* moduleAccesser, soDamageLog* damageLog) = 0;
    virtual int getDamageStatusKind(soModuleAccesser* moduleAccesser) = 0;
    virtual bool isUseTurnDamage(soModuleAccesser* moduleAccesser) = 0;
    virtual bool isUseTurn(soModuleAccesser* moduleAccesser) = 0;
    virtual bool isApplyTurnDamage(soModuleAccesser* moduleAccesser) = 0;
    virtual int getDamageHeight(soModuleAccesser* moduleAccesser, u8 damageIndex) = 0;
    virtual float getHitStopMul(soModuleAccesser* moduleAccesser) = 0;
    virtual bool isSlip(soModuleAccesser* moduleAccesser, float slipChance) = 0;
    virtual bool isSleepStatus(soModuleAccesser* moduleAccesser) = 0;
    virtual bool isParalyzeDamage(soModuleAccesser* moduleAccesser) = 0;
    virtual void addSleepTime(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) = 0;
    virtual void onFlowerDamage(soModuleAccesser* moduleAccesser, soDamage* damage) = 0;
    virtual void onParalyzeDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) = 0;
    virtual void setFlagDownDamage3(soModuleAccesser* moduleAccesser, bool flag) = 0;
    virtual bool isCheckGroundDamage(soModuleAccesser* moduleAccesser) = 0;
    virtual void onGroundDamageAfter(soModuleAccesser* moduleAccesser) = 0;
    virtual bool onCompositionDamageSpeed(soModuleAccesser* moduleAccesser, soDamage* damage, Vec2f* speed, int level) = 0;
    virtual bool preProcessCheckDamage(soModuleAccesser* moduleAccesser, soDamage* damage) { return false; }
    virtual bool onDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) = 0;
    virtual void setupDamageStatusNormal(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog, int unk) = 0;
    virtual void setupDamageStatusTurn(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) = 0;
    virtual void setupSpeedDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) = 0;
    virtual void setupDamageStatusNoReaction(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) = 0;
    virtual void setupDamageFlyRollStatus(float angle, float speed, soModuleAccesser* moduleAccesser, soDamageLog* damageLog) = 0;
    virtual float getReactionSub(soModuleAccesser* moduleAccesser) = 0;
    virtual float getReactionMul(soModuleAccesser* moduleAccesser) = 0;
    virtual float getWeightReactionMul(soModuleAccesser* moduleAccesser) { return 1.0f; }
    virtual float getDamageMul(soModuleAccesser* moduleAccesser) = 0;
    virtual void checkCheer(float reaction, float angle, soModuleAccesser* moduleAccesser, soDamageLog* damageLog) = 0;
    virtual float getDamageForReaction(float damage, soModuleAccesser* moduleAccesser) = 0;
    virtual bool checkNoReaction(soModuleAccesser* moduleAccesser, soDamage* damage) = 0;
    virtual int checkDownDamage(float reaction, float speed, soModuleAccesser* moduleAccesser) = 0;
    virtual bool isBindStatus(soModuleAccesser* moduleAccesser) = 0;
    virtual bool isBuryStatus(soModuleAccesser* moduleAccesser) = 0;
    virtual bool isSpeedDamage(soModuleAccesser* moduleAccesser) = 0;
};
static_assert(sizeof(soDamageTransactor) == 4, "Class is wrong size!");

class soDamageTransactorActor : public soDamageTransactor {
public:
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
    virtual bool onDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog);
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
    virtual bool checkNoReaction(soModuleAccesser* moduleAccesser, soDamage* damage);
    virtual int checkDownDamage(float reaction, float speed, soModuleAccesser* moduleAccesser);
    virtual bool isBindStatus(soModuleAccesser* moduleAccesser);
    virtual bool isBuryStatus(soModuleAccesser* moduleAccesser);

    bool onDamageSub(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog, bool* isNotFlinch);
};
