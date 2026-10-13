#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_system.h>

class soEventManageModule : public soNullable, public soEventManager {
public:
    virtual s16 addUnit(soEventUnit*);
    virtual void eraseUnit(u32);
    virtual bool isNullUnit(u32);
    virtual void eraseObserver(u32, int);
    virtual u32 getObserverCapacity(u32 index);
    virtual u32 getObserverSize(u32 index);
    virtual bool isExist(short);
    virtual s16 getManageId();
    virtual soEventUnit* getEventUnit(short);
};
static_assert(sizeof(soEventManageModule) == 12, "Class is wrong size!");

class soEventManageModuleImpl : public soEventManageModule {
public:
    void* m_12;
    short m_manageId;
    short _pad;

    virtual s16 addUnit(soEventUnit*);
    virtual void eraseUnit(u32);
    virtual bool isNullUnit(u32);
    virtual void eraseObserver(u32, int);
    virtual u32 getObserverCapacity(u32 index);
    virtual u32 getObserverSize(u32 index);
    virtual bool isExist(short);
    virtual s16 getManageId();
    virtual soEventUnit* getEventUnit(short);

    soEventManageModuleImpl(void* p1); // TODO p1 type

    // UBFIX this should have been virtual
    ~soEventManageModuleImpl();
};
static_assert(sizeof(soEventManageModuleImpl) == 20, "Class is wrong size!");
