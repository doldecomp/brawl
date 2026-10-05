#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <so/so_common_data_accesser.h>

class soModuleAccesser;

#ifdef FT_MODULE_BUILDER
// MATCH-ONLY: the destructor of this base is an out-of-line function in sora_melee (fighter RELs call it), so the
// class is specialized with the destructor declared only.
class soStatusEventObserver;
template <>
class soEventObserver<soStatusEventObserver> {
public:
    virtual void addObserver(s16 param1, s8 param2) { }
    s16 m_manageID;
    s16 m_unitID;
    s16 m_sendID;
    s32 getObserverId() const { return m_sendID; }
    soEventObserver(s16 unitID) {
        m_manageID = -1;
        m_unitID = unitID;
        m_sendID = -1;
    }
    ~soEventObserver();
    void addObserverSub(s32 manageId, soStatusEventObserver* obsvr, s8 p3); // sora_melee
    void initialize(s16 param1, s8 param2) { addObserver(param1, param2); }
};
#endif

class soStatusEventObserver : public soEventObserver<soStatusEventObserver> {
public:
    soStatusEventObserver() : soEventObserver<soStatusEventObserver>(0x4) {};
    soStatusEventObserver(short unitID) : soEventObserver<soStatusEventObserver>(unitID) {};
    // NOTE: shadows the BrawlHeaders copy; (manageId, p2) constructor added by agent/damage
    soStatusEventObserver(short manageId, s8 p2) : soEventObserver<soStatusEventObserver>(0x4) { initialize(manageId, p2); }

#ifdef FT_MODULE_BUILDER
    virtual void addObserver(short param1, s8 param2) { addObserverSub(param1, this, param2); } // MATCH-ONLY: inline in the REL
#else
    virtual void addObserver(short param1, s8 param2);
#endif
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soStatusEventObserver) == 12, "Class is wrong size!");
