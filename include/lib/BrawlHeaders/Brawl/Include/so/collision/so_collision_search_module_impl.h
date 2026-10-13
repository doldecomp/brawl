#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <mt/mt_vector.h>
#include <so/collision/so_collision_search_part.h>
#include <so/collision/so_collision.h>
#include <so/collision/so_collision_log.h>
#include <so/collision/so_collision_group.h>
#include <so/event/so_event_presenter.h>
#include <so/collision/so_collision_search_event_presenter.h>
#include <so/so_array.h>

class soModuleAccesser;

class soCollisionSearchModule {
public:
    virtual ~soCollisionSearchModule();
    virtual void activate(float, int taskId);
    virtual void deactivate();
    virtual void begin();
    virtual void clearAll();
    virtual void clear(u32 partIndex);
    virtual void set(u32 partIndex, u32 groupIndex, soCollisionSearchData* collisionSearchData);
    virtual bool isSearch(u32 partIndex);
    virtual float getSize(u32 partIndex);
    virtual void setSize(u32 partIndex, float size);
    virtual void setPos(int nodeIndex, Vec3f* startOffsetPos, Vec3f* endOffsetPos);
    virtual soCollisionSearchData* getData(u32 partIndex);
    virtual void update(float posX, float scale);
    virtual void checkLog();
    virtual bool check();
    virtual int isInflict();
    virtual void invalidLog(soCollisionLog* collisionLog, u32 groupIndex);
    virtual void setCheckInterval(int);
    virtual void renderDebug();
};
static_assert(sizeof(soCollisionSearchModule) == 4, "Class is wrong size!");

class soCollisionSearchModuleImpl : public soCollisionSearchModule, public soStatusEventObserver, public soAnimCmdEventObserver, public soEventPresenter<soCollisionSearchEventObserver> {
public:
    soModuleAccesser* m_moduleAccesser;
    void* m_collisionSearchPartArray;
    float m_48;
    soArrayVector<soCollisionGroup,1> m_collisionGroupArrayVector;
    soCollision m_collision;
    char _208[12];
    Vec3f m_startOffsetPos;
    Vec3f m_endOffsetPos;
    int m_nodeIndex;
    int m_isInflict;
    char _252[12];

    virtual ~soCollisionSearchModuleImpl();
    virtual void activate(float, int taskId);
    virtual void deactivate();
    virtual void begin();
    virtual void clearAll();
    virtual void clear(u32 partIndex);
    virtual void set(u32 partIndex, u32 groupIndex, soCollisionSearchData* collisionSearchData);
    virtual bool isSearch(u32 partIndex);
    virtual float getSize(u32 partIndex);
    virtual void setSize(u32 partIndex, float size);
    virtual void setPos(int nodeIndex, Vec3f* startOffsetPos, Vec3f* endOffsetPos);
    virtual soCollisionSearchData* getData(u32 partIndex);
    virtual void update(float posX, float scale);
    virtual void checkLog();
    virtual bool check();
    virtual int isInflict();
    virtual void invalidLog(soCollisionLog* collisionLog, u32 groupIndex);
    virtual void setCheckInterval(int);
    virtual void renderDebug();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soCollisionSearchModuleImpl) == 264, "Class is wrong size!");

