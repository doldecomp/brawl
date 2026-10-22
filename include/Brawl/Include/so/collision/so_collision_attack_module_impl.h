#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <mt/mt_vector.h>
#include <so/collision/so_collision_attack_part.h>
#include <so/collision/so_collision.h>
#include <so/collision/so_collision_log.h>
#include <so/situation/so_situation_module_impl.h>
#include <so/event/so_event_presenter.h>
#include <so/collision/so_collision_attack_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/so_array.h>

class soModuleAccesser;
class StageObject;

class soCollisionAttackModule {
public:
    // TODO: Verify parameters
    virtual ~soCollisionAttackModule();
    virtual void activate(float, float lr, int taskId, Vec2f* pos, u32 index, bool);
    virtual void deactivate();
    virtual void begin();
    virtual void clearAll();
    virtual void clear(u32 index);
    virtual void sleep(bool);
    virtual void set(u32 index, u32 groupIndex, soCollisionAttackData* attackData);
    virtual void set(u32 index, u32 groupIndex);
    virtual void setAbsolute(u32 index, u32 groupIndex, soCollisionAttackAbsoluteData* attackData);
    virtual void hitAbsolute(u32 index, Vec3f* nodeGlobalPos, void*, short, u8);
    virtual void hitAbsolute(u32 index, int nodeId, void*, short, u8);
    virtual void hitAbsolute(u32 index, const char* nodeName, void*, short, u8);
    virtual void setWhole(u32 index, bool);
    virtual bool isAttack(u32 index, bool);
    virtual bool isInvalidInvincible(u32 index, bool);
    virtual bool isInvalidXlu(u32 index, bool);
    virtual void setPower(u32 index, int power, bool);
    virtual void setVector(u32 index, int vector);
    virtual float getSize(u32 index);
    virtual void setSize(u32 index, float size);
    virtual void setTargetCategory(u32 index, soCollision::CategoryMask categoryMask);
    virtual bool setOffset(u32 index, Vec3f* offsetPos);
    virtual bool setOffsetFromNode(u32 index, int node);
    virtual void setNode(u32 index, int node);
    virtual float getBasePower(u32 index, bool);
    virtual float getPower(u32 index, bool);
    virtual u32 getGroup(u32 index);
    virtual int getReactionEffect(u32 index, bool);
    virtual void setReactionEffect(u32 index, int reactionEffect, bool);
    virtual int getReactionFix(u32 index, bool);
    virtual void setReactionFix(u32 index, int reactionFix, bool);
    virtual int getReactionAdd(u32 index, bool);
    virtual void setReactionAdd(u32 index, int reactionAdd, bool);
    virtual float getReactionMul();
    virtual void setPosX(u32 index, float posX);
    virtual float getPosX(u32 index, bool);
    virtual float getPosX();
    virtual Vec3f getCenterPos(u32 index, bool);
    virtual float getSpeedX();
    virtual Vec2f getSpeed();
    virtual void setSpeed(Vec2f* speed);
    virtual soCollisionAttackData* getData(u32 index, bool);
    virtual void setPowerMulStatus(float powerMulStatus);
    virtual float getPowerMulStatus();
    virtual void setPowerAddStatus(float powerAddStatus);
    virtual float getPowerSpeedStatus();
    virtual void setPowerSpeedStatus(float powerSpeedStatus);
    virtual void setPowerMul(float powerMul);
    virtual float getPowerMul();
    virtual void setPowerMul2nd(float powerMul2nd);
    virtual float getPowerMul2nd();
    virtual void setReactionMul(float reactionMul);
    virtual float getLr();
    virtual u32 getPartSize();
    virtual void update(Vec2f* pos, float scale, float lr, SituationKind kind, Vec2f* speed);
    virtual void checkLog();
    virtual bool check();
    virtual void refLogGroup(u32 groupIndex, u32 logGroupIndex);
    virtual void unRefLogGroup(u32 groupIndex);
    virtual int isInflict();
    virtual int isInflictStatus();
    virtual void setIndirectInfo(int indirectTaskId, int teamNo);
    virtual int getIndirectTaskId();
    virtual int getIndirectTeamNo();
    virtual soCollision* getCollision();
    virtual void addPastLog(void*, u32, u32 groupIndex);
    virtual void invalidLog(soCollisionLog* collisionLog, u32 groupIndex);
    virtual bool checkRebound(float, soModuleAccesser* moduleAccesser, StageObject*, soCollisionLog* collisionLog, float* out1, float* out2);
    virtual void setRestrict(bool isRestrict);
    virtual void renderDebug();
};
static_assert(sizeof(soCollisionAttackModule) == 4, "Class is wrong size!");

class soCollisionAttackModuleImpl : public soCollisionAttackModule, public soStatusEventObserver, public soAnimCmdEventObserver, public soEventPresenter<soCollisionAttackEventObserver> {
public:
    soModuleAccesser* m_moduleAccesser;
    void* m_indirectTeam;
    void* m_collisionAttackPart;
    void* m_collisionAttackAbsoluteArray;
    Vec2f m_pos;
    Vec2f m_speed;
    float m_powerMulStatus;
    float m_powerAdd;
    float m_powerSpeedStatus;
    float m_powerMul;
    float m_powerMul2nd;
    float m_reactionMul;
    float m_0x60;
    void* m_collisionGroupArray;
    soCollision m_collision;
    char _128[8];
    soCollision::Situation m_situation;
    float m_lr;
    int m_isInflict;
    int m_isInflictStatus;
    int m_indirectTaskId;
    char _156[4];

    // TODO: Verify parameters
    virtual ~soCollisionAttackModuleImpl();
    virtual void activate(float, float lr, int taskId, Vec2f* pos, u32 index, bool);
    virtual void deactivate();
    virtual void begin();
    virtual void clearAll();
    virtual void clear(u32 index);
    virtual void sleep(bool);
    virtual void set(u32 index, u32 groupIndex, soCollisionAttackData* attackData);
    virtual void set(u32 index, u32 groupIndex);
    virtual void setAbsolute(u32 index, u32 groupIndex, soCollisionAttackAbsoluteData* attackData);
    virtual void hitAbsolute(u32 index, Vec3f* nodeGlobalPos, void*, short, u8);
    virtual void hitAbsolute(u32 index, int nodeId, void*, short, u8);
    virtual void hitAbsolute(u32 index, const char* nodeName, void*, short, u8);
    virtual void setWhole(u32 index, bool);
    virtual bool isAttack(u32 index, bool);
    virtual bool isInvalidInvincible(u32 index, bool);
    virtual bool isInvalidXlu(u32 index, bool);
    virtual void setPower(u32 index, int power, bool);
    virtual void setVector(u32 index, int vector);
    virtual float getSize(u32 index);
    virtual void setSize(u32 index, float size);
    virtual void setTargetCategory(u32 index, soCollision::CategoryMask categoryMask);
    virtual bool setOffset(u32 index, Vec3f* offsetPos);
    virtual bool setOffsetFromNode(u32 index, int node);
    virtual void setNode(u32 index, int node);
    virtual float getBasePower(u32 index, bool);
    virtual float getPower(u32 index, bool);
    virtual u32 getGroup(u32 index);
    virtual int getReactionEffect(u32 index, bool);
    virtual void setReactionEffect(u32 index, int reactionEffect, bool);
    virtual int getReactionFix(u32 index, bool);
    virtual void setReactionFix(u32 index, int reactionFix, bool);
    virtual int getReactionAdd(u32 index, bool);
    virtual void setReactionAdd(u32 index, int reactionAdd, bool);
    virtual float getReactionMul();
    virtual void setPosX(u32 index, float posX);
    virtual float getPosX(u32 index, bool);
    virtual float getPosX();
    virtual Vec3f getCenterPos(u32 index, bool);
    virtual float getSpeedX();
    virtual Vec2f getSpeed();
    virtual void setSpeed(Vec2f* speed);
    virtual soCollisionAttackData* getData(u32 index, bool);
    virtual void setPowerMulStatus(float powerMulStatus);
    virtual float getPowerMulStatus();
    virtual void setPowerAddStatus(float powerAddStatus);
    virtual float getPowerSpeedStatus();
    virtual void setPowerSpeedStatus(float powerSpeedStatus);
    virtual void setPowerMul(float powerMul);
    virtual float getPowerMul();
    virtual void setPowerMul2nd(float powerMul2nd);
    virtual float getPowerMul2nd();
    virtual void setReactionMul(float reactionMul);
    virtual float getLr();
    virtual u32 getPartSize();
    virtual void update(Vec2f* pos, float scale, float lr, SituationKind kind, Vec2f* speed);
    virtual void checkLog();
    virtual bool check();
    virtual void refLogGroup(u32 groupIndex, u32 logGroupIndex);
    virtual void unRefLogGroup(u32 groupIndex);
    virtual int isInflict();
    virtual int isInflictStatus();
    virtual void setIndirectInfo(int indirectTaskId, int teamNo);
    virtual int getIndirectTaskId();
    virtual int getIndirectTeamNo();
    virtual soCollision* getCollision();
    virtual void addPastLog(void*, u32, u32 groupIndex);
    virtual void invalidLog(soCollisionLog* collisionLog, u32 groupIndex);
    virtual bool checkRebound(float, soModuleAccesser* moduleAccesser, StageObject*, soCollisionLog* collisionLog, float* out1, float* out2);
    virtual void setRestrict(bool isRestrict);
    virtual void renderDebug();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);

    soCollisionAttackModuleImpl(soModuleAccesser* moduleAccesser, int taskId, gfTask::Category taskCategory,
                                soArray<soCollisionAttackPart>*, soArray<soCollisionGroup>*,
                                        soArray<soCollisionAttackAbsolute>*, soEventObserverRegistrationDesc*, bool);
};
static_assert(sizeof(soCollisionAttackModuleImpl) == 160, "Class is wrong size!");

template <soCollision::Category TCategory, u32 TNumParts, u32 TNumAbsolutes, class TCollisionAttackModule, u32 TNumGroups, bool TBool1, bool TBool2>
class soCollisionAttackModuleBuildConfig {
    soArrayVector<soCollisionAttackPart, TNumParts> m_attackPartArrayVector;
    soArrayVector<soCollisionGroup, TNumGroups> m_collisionGroupArrayVector;
    soArrayVector<soCollisionAttackAbsolute, TNumAbsolutes> m_attackAbsoluteArrayVector;
    TCollisionAttackModule m_attackModule;
public:
    soCollisionAttackModuleBuildConfig(soModuleAccesser* moduleAccesser,
                                       int taskId,
                                       gfTask::Category taskCategory,
                                       soEventObserverRegistrationDesc* registrationDesc) :
                                       m_attackPartArrayVector(TNumParts, soCollisionAttackPart(TCategory, TBool1), 0),
                                       m_collisionGroupArrayVector(TNumGroups, 0),
                                       m_attackAbsoluteArrayVector(TNumAbsolutes, 0),
                                       m_attackModule(moduleAccesser, taskId, taskCategory, &m_attackPartArrayVector, &m_collisionGroupArrayVector, &m_attackAbsoluteArrayVector, registrationDesc, TBool2) {};

};

template <class TCollisionAttackBuildConfig>
class soCollisionAttackModuleBuilder {
    TCollisionAttackBuildConfig m_buildConfig;
public:

    soCollisionAttackModule* getModule() {
        return &m_buildConfig.m_attackModule;
    };

    soCollisionAttackModuleBuilder(soModuleAccesser* moduleAccesser,
                                   int taskId,
                                   gfTask::Category taskCategory,
                                   soEventObserverRegistrationDesc* registrationDesc) :
                                   m_buildConfig(moduleAccesser, taskId, taskCategory, registrationDesc) { } ;
};