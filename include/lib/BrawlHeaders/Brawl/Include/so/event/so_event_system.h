#pragma once

#include <StaticAssert.h>
#include <so/so_array.h>
#include <so/so_instance_manager.h>
#include <so/so_instance_unit.h>
#include <so/so_null.h>
#include <types.h>

class soEventUnit : public soNullableInterface {
public:
    virtual void eraseObserver(s16 id, s16 sendID) = 0;
    virtual s16 getEventId() = 0;
    virtual u32 getObserverCapacity(u32 index) = 0;
    virtual u32 getObserverSize(u32 index) = 0;
    virtual ~soEventUnit() { }
};

class soEventManager {
public:
    virtual s16 addUnit(soEventUnit*);
    virtual void eraseUnit(u32);
    virtual bool isNullUnit(u32);
    virtual void eraseObserver(s16 id, s16 sendID);
    virtual u32 getObserverCapacity(u32 index);
    virtual u32 getObserverSize(u32 index);
    virtual bool isExist(short);
    virtual s16 getManageId();
    virtual soEventUnit* getEventUnit(short);
};

class soEventSystem {
public:
    soInstanceManagerSimpleEntity<soEventManager*, soArrayVector<soInstanceUnit<soEventManager*>, 500 > > m_instanceManager;

    soEventManager* getManager(s32 manageID);
    static soEventSystem* getInstance();
    soInstanceManager<soEventManager*>& getInstanceManager() { return m_instanceManager; }

};
static_assert(sizeof(soEventSystem) == 4032, "Class is wrong size!");

template <typename T>
class soEventUnitWrapper : public soEventUnit {
public:
    virtual s16 getEventId() { return m_eventID; }
    virtual ~soEventUnitWrapper() {
        if (isValid())
            soEventSystem::getInstance()->getManager(m_managerID)->eraseUnit(m_eventID);
    }
    virtual s16 addObserverSub(T*, s8) = 0;
    virtual soInstanceManagerFullProperty<T*>* getObserverListSub() = 0;

    soEventUnitWrapper(s16 mgrId, s16 p2) : m_managerID(mgrId), m_eventID(p2) {
        if (mgrId != -1) {
            s16 eid = soEventSystem::getInstance()->getManager(m_managerID)->addUnit(this);
            if (eid > -1)
                m_eventID = eid;
        }
    }

    bool isValid() const { return m_managerID != -1; }

    s16 m_managerID;
    s16 m_eventID;
};

template <typename T>
class soEventUnitNull : public soEventUnitWrapper<T> {
public:
    virtual bool isNull() const {
        return true;
    }

    soEventUnitNull(s16 mgrId, s16 p2) : soEventUnitWrapper<T>(mgrId, p2) { }
};

template <typename T>
class soEventUnitImpl : public soEventUnitWrapper<T> {
public:
    soInstanceManagerFullProperty<T*>* m_observerListPtr; // 0x8

    virtual bool isNull() const {
        return false;
    }

    virtual void eraseObserver(s16 id, s16 sendID) {
        m_observerListPtr->erase(id);
    }

    // TODO: shouldn't need index
    virtual u32 getObserverCapacity(u32 index) {
        return m_observerListPtr->capacity();
    }

    // TODO: shouldn't need index
    virtual u32 getObserverSize(u32 index) {
        return m_observerListPtr->size();
    }

    virtual ~soEventUnitImpl() { }

    virtual s16 addObserverSub(T* obsvr, s8 p2) {
        return m_observerListPtr->add(obsvr, -1, soAttributeFlag(), p2);
    }

    virtual soInstanceManagerFullProperty<T*>* getObserverListSub() {
        return m_observerListPtr;
    }

    virtual u32 getObserverNum() const = 0;

    soEventUnitImpl(s16 mgrId, s16 p2) : soEventUnitWrapper<T>(mgrId, p2) {
        m_observerListPtr = reinterpret_cast<soInstanceManagerFullProperty<T*>*>(
                            reinterpret_cast<u8*>(this) +
                            sizeof(soEventUnitImpl<T>));
    }
};

template <typename T, s32 C>
class soEventUnitWithWorkArea : public soEventUnitImpl<T> {
    soInstanceManagerFullPropertyVector<T*, C> m_observerList; // 0xC
public:
    soEventUnitWithWorkArea(s16 mgrId, s16 p2) :
        soEventUnitImpl<T>(mgrId, p2) { }

    virtual ~soEventUnitWithWorkArea() { }
    virtual u32 getObserverNum() const {
        return m_observerList.size();
    }
};
