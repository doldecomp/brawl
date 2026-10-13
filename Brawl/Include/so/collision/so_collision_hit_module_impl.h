#pragma once

#include <StaticAssert.h>
#include <so/collision/so_collision.h>
#include <so/collision/so_collision_hit_group.h>
#include <so/so_array.h>
#include <so/event/so_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/collision/so_collision_hit_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/so_null.h>
#include <types.h>

class soModuleAccesser;

class soCollisionHitModule : public soNullable {
public:
    virtual ~soCollisionHitModule();
    virtual void activate(float, float, float, u32 collisionIndex, u32 collisionHitGroupIndex);
    virtual void activate(float, float, float, int taskId, u32 collisionIndex);
    virtual void reset(float, float, float, u32 collisionIndex, u32 collisionHitGroupIndex);
    virtual void deactivate();
    virtual void begin();
    virtual void clean();
    virtual void sleep(bool);
    virtual void add(soSet<soCollisionHitData>*, u32 collisionHitGroupIndex);
    virtual void add(soSet<soCollisionHitData::Simple>*, u32 collisionHitGroupIndex);
    virtual void resetStatusAll(u32 collisionHitGroupIndex);
    virtual void set(u32 collisionHitPartIndex, soCollisionHitData* hitData, u32 collisionHitGroupIndex);
    virtual void set(soSet<soCollisionHitData>*, u32 collisionHitGroupIndex);
    virtual void set(soSet<soCollisionHitData::Simple>*, u32 collisionHitGroupIndex);
    virtual void setStatus(u32 collisionHitPartIndex, int status, u32 collisionHitGroupIndex);
    virtual void setStatusNode(int, int status, u32 collisionHitGroupIndex);
    virtual void setStatusNodeDefault(int, int status, u32 collisionHitGroupIndex);
    virtual void setStatusAll(int status, u32 collisionHitGroupIndex);
    virtual void setWhole(int, u32 collisionHitGroupIndex);
    virtual int getWhole(u32 collisionHitGroupIndex);
    virtual void setCheckCatch(bool, u32 collisionHitGroupIndex);
    virtual void update(float posX, float scale, float lr, SituationKind, u32 collisionHitGroupIndex);
    virtual void update(float posX, float scale, float lr, SituationKind);
    virtual void resetStatusGlobal(u32 collisionHitGroupIndex);
    virtual void setXluGlobal(u32 collisionHitGroupIndex);
    virtual void cancelXluGlobal(u32 collisionHitGroupIndex);
    virtual void setXluFrameGlobal(int xluFrameGlobal, u32 collisionHitGroupIndex);
    virtual void setInvincibleGlobal(u32 collisionHitGroupIndex);
    virtual void cancelInvincibleGlobal(u32 collisionHitGroupIndex);
    virtual void setInvincibleFrameGlobal(int invincibleFrameGlobal, bool override, u32 collisionHitGroupIndex);
    virtual int getInvincibleFrameGlobal(u32 collisionHitGroupIndex);
    virtual int getGlobal(u32 collisionHitGroupIndex);
    virtual int getStatus(u32 collisionHitPartIndex, u32 collisionHitGroupIndex);
    virtual int getTotalStatus(u32 collisionHitGroupIndex);
    virtual float getDurabilityMulFromAttackData();
    virtual int getPartSize(u32 collisionHitGroupIndex);
    virtual u32 getPartHeight(u32 collisionHitPartIndex, u32 collisionHitGroupIndex);
    virtual void setNoTeam(bool);
    virtual void setGlobalOffset(u8, u32 collisionHitGroupIndex);
    virtual void setMultiSituation(SituationKind situationKind, u32 collisionHitGroupIndex);
    virtual void initMultiSituation(u32 collisionHitGroupIndex);
    virtual void setOpponentCategory(u32 categoryMask, bool, u32 collisionHitGroupIndex);
    virtual void setSelfCategory(soCollision::Category, u32 collisionHitGroupIndex);
    virtual void checkLog();
    virtual u32 getGroupNum();
    virtual bool isReactionFrame();
    virtual short getReactionFrame();
    virtual void setReactionFrame(short reactionFrame);
    virtual void setPosX(float posX, u32 collisionGroupIndex);
    virtual float getPosX(u32 collisionGroupIndex);
    virtual Vec3f getCenterPos(u16 index, u32 collisionHitGroupIndex);
    virtual void renderDebug();
};
static_assert(sizeof(soCollisionHitModule) == 8, "Class is wrong size!");

class soCollisionHitModuleImpl : public soCollisionHitModule, public soStatusEventObserver, public soAnimCmdEventObserver, public soEventPresenter<soCollisionHitEventObserver> {

public:
    soModuleAccesser* m_moduleAccesser;
    char _48[8];
    soCollision m_collision;
    char _80[8];
    soArray<soCollisionHitGroup>* m_collisionHitGroupArray;
    char _92[8];
    short m_reactionFrame;
    char _102[2];

    virtual ~soCollisionHitModuleImpl();
    virtual void activate(float, float, float, u32 collisionIndex, u32 collisionHitGroupIndex);
    virtual void activate(float, float, float, int taskId, u32 collisionIndex);
    virtual void reset(float, float, float, u32 collisionIndex, u32 collisionHitGroupIndex);
    virtual void deactivate();
    virtual void begin();
    virtual void clean();
    virtual void sleep(bool);
    virtual void add(soSet<soCollisionHitData>*, u32 collisionHitGroupIndex);
    virtual void add(soSet<soCollisionHitData::Simple>*, u32 collisionHitGroupIndex);
    virtual void resetStatusAll(u32 collisionHitGroupIndex);
    virtual void set(u32 collisionHitPartIndex, soCollisionHitData* hitData, u32 collisionHitGroupIndex);
    virtual void set(soSet<soCollisionHitData>*, u32 collisionHitGroupIndex);
    virtual void set(soSet<soCollisionHitData::Simple>*, u32 collisionHitGroupIndex);
    virtual void setStatus(u32 collisionHitPartIndex, int status, u32 collisionHitGroupIndex);
    virtual void setStatusNode(int, int status, u32 collisionHitGroupIndex);
    virtual void setStatusNodeDefault(int, int status, u32 collisionHitGroupIndex);
    virtual void setStatusAll(int status, u32 collisionHitGroupIndex);
    virtual void setWhole(int, u32 collisionHitGroupIndex);
    virtual int getWhole(u32 collisionHitGroupIndex);
    virtual void setCheckCatch(bool, u32 collisionHitGroupIndex);
    virtual void update(float posX, float scale, float lr, SituationKind, u32 collisionHitGroupIndex);
    virtual void update(float posX, float scale, float lr, SituationKind);
    virtual void resetStatusGlobal(u32 collisionHitGroupIndex);
    virtual void setXluGlobal(u32 collisionHitGroupIndex);
    virtual void cancelXluGlobal(u32 collisionHitGroupIndex);
    virtual void setXluFrameGlobal(int xluFrameGlobal, u32 collisionHitGroupIndex);
    virtual void setInvincibleGlobal(u32 collisionHitGroupIndex);
    virtual void cancelInvincibleGlobal(u32 collisionHitGroupIndex);
    virtual void setInvincibleFrameGlobal(int invincibleFrameGlobal, bool override, u32 collisionHitGroupIndex);
    virtual int getInvincibleFrameGlobal(u32 collisionHitGroupIndex);
    virtual int getGlobal(u32 collisionHitGroupIndex);
    virtual int getStatus(u32 collisionHitPartIndex, u32 collisionHitGroupIndex);
    virtual int getTotalStatus(u32 collisionHitGroupIndex);
    virtual float getDurabilityMulFromAttackData();
    virtual int getPartSize(u32 collisionHitGroupIndex);
    virtual u32 getPartHeight(u32 collisionHitPartIndex, u32 collisionHitGroupIndex);
    virtual void setNoTeam(bool);
    virtual void setGlobalOffset(u8, u32 collisionHitGroupIndex);
    virtual void setMultiSituation(SituationKind situationKind, u32 collisionHitGroupIndex);
    virtual void initMultiSituation(u32 collisionHitGroupIndex);
    virtual void setOpponentCategory(u32 categoryMask, bool, u32 collisionHitGroupIndex);
    virtual void setSelfCategory(soCollision::Category, u32 collisionHitGroupIndex);
    virtual void checkLog();
    virtual u32 getGroupNum();
    virtual bool isReactionFrame();
    virtual short getReactionFrame();
    virtual void setReactionFrame(short reactionFrame);
    virtual void setPosX(float posX, u32 collisionGroupIndex);
    virtual float getPosX(u32 collisionGroupIndex);
    virtual Vec3f getCenterPos(u16 index, u32 collisionHitGroupIndex);
    virtual void renderDebug();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);

    soCollisionHitModuleImpl(soModuleAccesser*, int taskId, gfTask::Category taskCategory, soArray<soCollisionHitPart>*,
            soArray<soCollisionGroup>*, soArray<soCollisionHitGroup>*, soEventObserverRegistrationDesc*, bool);
};
static_assert(sizeof(soCollisionHitModuleImpl) == 104, "Class is wrong size!");

template <soCollision::Category TSelfCategory, u32 TNumParts, u32 TNumGroups, class TCollisionHitModule, u32 TOpponentCategoryMask, bool TBool1>
class soCollisionHitModuleBuildConfig {
    soArrayVector<soCollisionHitPart, TNumParts> m_hitPartArrayVector;
    soArrayVector<soCollisionGroup, TNumGroups> m_collisionGroupArrayVector;
    soArrayVector<soCollisionHitGroup, TNumGroups> m_hitGroupArrayVector;
    TCollisionHitModule m_hitModule;
public:
    soCollisionHitModuleBuildConfig(soModuleAccesser* moduleAccesser,
                                    int taskId,
                                    gfTask::Category taskCategory,
                                    soEventObserverRegistrationDesc* registrationDesc) :
                                    m_hitPartArrayVector(TNumParts, soCollisionHitPart(TSelfCategory, TOpponentCategoryMask), 0),
                                    m_collisionGroupArrayVector(TNumGroups, 0),
                                    m_hitGroupArrayVector(TNumGroups, 0),
                                    m_hitModule(moduleAccesser, taskId, taskCategory, &m_hitPartArrayVector, &m_collisionGroupArrayVector, &m_hitGroupArrayVector, registrationDesc, TBool1) {};
};

template <class TCollisionHitBuildConfig>
class soCollisionHitModuleBuilder {
    TCollisionHitBuildConfig m_buildConfig;
public:

    soCollisionHitModule* getModule() {
        return &m_buildConfig.m_hitModule;
    };

    soCollisionHitModuleBuilder(soModuleAccesser* moduleAccesser,
                                   int taskId,
                                   gfTask::Category taskCategory,
                                   soEventObserverRegistrationDesc* registrationDesc) :
                                   m_buildConfig(moduleAccesser, taskId, taskCategory, registrationDesc) { } ;
};