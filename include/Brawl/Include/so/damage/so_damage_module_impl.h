#pragma once

#include <StaticAssert.h>
#include <so/collision/so_collision_attack_part.h>
#include <so/damage/so_damage.h>
#include <so/damage/so_damage_attacker_info.h>
#include <so/damage/so_damage_effector_impl.h>
#include <so/damage/so_damage_no_reaction_module.h>
#include <so/damage/so_damage_transactor_actor.h>
#include <so/so_array.h>
#include <so/event/so_event_presenter.h>
#include <so/damage/so_damage_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/collision/so_collision_hit_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/so_null.h>
#include <types.h>

class StageObject;
class soModuleAccesser;

class soDamageModule : public soNull, public soNullable {
public:
    virtual ~soDamageModule();
    virtual void activate(float damage);
    virtual void deactivate();
    virtual void sleep(bool);
    virtual void update();
    virtual void initDamage(float damage);
    virtual void initInfo();
    virtual void setInfo();
    virtual void storeDamage(float addedDamage, soDamage* damage);
    virtual bool check(bool);
    virtual float getDamageLr(float, float, void*, void*, int, int);
    virtual bool setForceDamage(StageObject* stageObject, Vec3f* pos, u32 collisionIndex, u32 damageIndex, bool getAbsolute, bool initInfo);
    virtual bool setForceDamage(StageObject* stageObject, int nodeId, u32 collisionIndex, u32 damageIndex, bool getAbsolute, bool initInfo);
    virtual bool setForceDamage(StageObject* stageObject, const char* nodeName, u32 collisionIndex, u32 damageIndex, bool getAbsolute, bool initInfo);
    virtual void addDamage(float damage, u32 damageIndex);
    virtual float getDamage(u32 damageIndex);
    virtual float getReaction(u32 damageIndex);
    virtual float getPowerMax(u32 damageIndex);
    virtual bool checkNoReaction(void*);
    virtual void setNoReactionModeStatus(float, float, int mode);
    virtual void setNoReactionMode2nd(float, float, int mode);
    virtual void resetNoReactionModeStatus();
    virtual void setNoReactionMode(int mode);
    virtual void resetNoReactionMode();
    virtual void setNoReactionModeAlways(bool);
    virtual void setNoReactionModePerfect(bool);
    virtual bool isNoReactionModePerfect();
    virtual void toTurnDamage();
    virtual void leaveTurnDamage();
    virtual soDamageLog* getDamageLog();
    virtual void clearDamageLog();
    virtual void getAttackerInfo(soDamageAttackerInfo* attackerInfo);
    virtual soDamageAttackerInfo* getAttackerInfo();
    virtual void restoreAttackerInfo(soDamageAttackerInfo* attackerInfo);
    virtual void clearAttackerInfo();
    virtual soDamageEffector* getEffector();
    virtual soDamageTransactor* getTransactor();
    virtual bool isReaction();
    virtual bool isCatchCut();
    virtual float getCaptureDamage();
    virtual bool isCaptureCut();
    virtual bool isCaptureCut(void*);
    virtual void setDamageMul(float damageMul);
    virtual void setReactionMul(float reactionMul);
    virtual void setReactionMul2nd(float reactionMul2nd);
    virtual void setDamageLock(bool);
    virtual bool isDamageLock();
    virtual void heal(float healAmount, u32 damageIndex);
    virtual void updateAttackerInfo();
};
static_assert(sizeof(soDamageModule) == 12, "Class is wrong size!");

class soDamageModuleImpl : public soDamageModule, public soCollisionHitEventObserver, public soStatusEventObserver, public soEventPresenter<soDamageEventObserver>, public soAnimCmdEventObserver {

public:
    soModuleAccesser* m_moduleAccesser;
    soArray<soDamage>* m_damageArray;
    soDamageNoReactionModule m_noReactionModule;
    soDamageAttackerInfo m_attackerInfo;
    soDamageEffector* m_effector;
    soDamageTransactor* m_transactor;
    float m_damageMul;
    float m_reactionMul;
    float m_reactionMul2nd;
    char _160[8];
    bool m_isDamageLock;
    u8 m_sleep;
    char _pad[2];

    virtual ~soDamageModuleImpl();
    virtual void activate(float damage);
    virtual void deactivate();
    virtual void sleep(bool);
    virtual void update();
    virtual void initDamage(float damage);
    virtual void initInfo();
    virtual void setInfo();
    virtual void storeDamage(float addedDamage, soDamage* damage);
    virtual bool check(bool);
    virtual float getDamageLr(float, float, void*, void*, int, int);
    virtual bool setForceDamage(StageObject* stageObject, Vec3f* pos, u32 collisionIndex, u32 damageIndex, bool getAbsolute, bool initInfo);
    virtual bool setForceDamage(StageObject* stageObject, int nodeId, u32 collisionIndex, u32 damageIndex, bool getAbsolute, bool initInfo);
    virtual bool setForceDamage(StageObject* stageObject, const char* nodeName, u32 collisionIndex, u32 damageIndex, bool getAbsolute, bool initInfo);
    virtual void addDamage(float damage, u32 damageIndex);
    virtual float getDamage(u32 damageIndex);
    virtual float getReaction(u32 damageIndex);
    virtual float getPowerMax(u32 damageIndex);
    virtual bool checkNoReaction(void*);
    virtual void setNoReactionModeStatus(float, float, int mode);
    virtual void setNoReactionMode2nd(float, float, int mode);
    virtual void resetNoReactionModeStatus();
    virtual void setNoReactionMode(int mode);
    virtual void resetNoReactionMode();
    virtual void setNoReactionModeAlways(bool);
    virtual void setNoReactionModePerfect(bool);
    virtual bool isNoReactionModePerfect();
    virtual void toTurnDamage();
    virtual void leaveTurnDamage();
    virtual soDamageLog* getDamageLog();
    virtual void clearDamageLog();
    virtual void getAttackerInfo(soDamageAttackerInfo* attackerInfo);
    virtual soDamageAttackerInfo* getAttackerInfo();
    virtual void restoreAttackerInfo(soDamageAttackerInfo* attackerInfo);
    virtual void clearAttackerInfo();
    virtual soDamageEffector* getEffector();
    virtual soDamageTransactor* getTransactor();
    virtual bool isReaction();
    virtual bool isCatchCut();
    virtual float getCaptureDamage();
    virtual bool isCaptureCut();
    virtual bool isCaptureCut(void*);
    virtual void setDamageMul(float damageMul);
    virtual void setReactionMul(float reactionMul);
    virtual void setReactionMul2nd(float reactionMul2nd);
    virtual void setDamageLock(bool);
    virtual bool isDamageLock();
    virtual void heal(float healAmount, u32 damageIndex);
    virtual void updateAttackerInfo();

    // TODO: Check parameters
    virtual void reqDamageShake();
    virtual bool preProcessCheckDamage();
    virtual bool onDamage(u32 damageIndex);
    virtual bool isCheckGroundDamage();
    virtual bool onGroundDamage();
    virtual float getReactionSub();
    virtual float getReactionMul();
    virtual float getWeightReactionMul();
    virtual float getDamageMul();
    virtual void reqDamageEffect();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventCollisionHit(float power, soCollisionAttackData*, u32 index, int, soModuleAccesser* moduleAccesser, soCollisionLog*);
    virtual void notifyEventCollisionHit2nd(float posX, float collisionLr, soCollisionAttackModule*, soCollisionLog*, u32 groupIndex, soModuleAccesser* moduleAccesser, bool);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soDamageModuleImpl) == 172, "Class is wrong size!");