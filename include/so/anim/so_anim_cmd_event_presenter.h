#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <ac/ac_anim_cmd_impl.h>

class soModuleAccesser;

#ifdef FT_MODULE_BUILDER
// MATCH-ONLY: the destructor of this base is an out-of-line function in sora_melee (fighter RELs call it), so the
// class is specialized with the destructor declared only.
class soAnimCmdEventObserver;
template <>
class soEventObserver<soAnimCmdEventObserver> {
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
    void initialize(s16 param1, s8 param2) { addObserver(param1, param2); }
};
#endif

class soAnimCmdEventObserver : public soEventObserver<soAnimCmdEventObserver> {
public:
    soAnimCmdEventObserver(short unitID) : soEventObserver<soAnimCmdEventObserver>(unitID) {};
    soAnimCmdEventObserver();
    // NOTE: shadows the BrawlHeaders copy; (manageId, p2) constructor added by agent/damage
    soAnimCmdEventObserver(short manageId, s8 p2) : soEventObserver<soAnimCmdEventObserver>(0x5) { initialize(manageId, p2); }
    // HYPOTHESIS: constructor that also registers with the given manager (seen in soControllerModuleImpl ctor).
    soAnimCmdEventObserver(s16 unitID, s16 manageID) : soEventObserver<soAnimCmdEventObserver>(unitID) { addObserver(manageID, -1); }

    virtual void addObserver(short param1, s8 param2);
    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, s32 unk3);
};
static_assert(sizeof(soAnimCmdEventObserver) == 12, "Class is wrong size!");
