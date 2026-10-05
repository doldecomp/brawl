#pragma once
// SHADOW of BrawlHeaders/so/damage/so_damage_event_presenter.h: addObserver is inline in the fighter RELs (FT_MODULE_BUILDER)

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <so/damage/so_damage.h>

class StageObject;
class soModuleAccesser;

class soDamageEventObserver : public soEventObserver<soDamageEventObserver> {
public:
    soDamageEventObserver() : soEventObserver<soDamageEventObserver>(0x6) {};
    soDamageEventObserver(short unitID) : soEventObserver<soDamageEventObserver>(unitID) {};
    soDamageEventObserver(short param1, s8 param2) : soEventObserver<soDamageEventObserver>(0x6) {
        initialize(param1, param2);
    }

#ifdef FT_MODULE_BUILDER
    virtual void addObserver(short param1, s8 param2) { addObserverSub(param1, this, param2); } // MATCH-ONLY: inline in the REL
#else
    virtual void addObserver(short param1, s8 param2);
#endif
    virtual void notifyEventOnDamage(soDamage* damage, bool, soModuleAccesser* moduleAccesser);
    virtual void notifyEventAddDamage(soDamage* damage, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soDamageEventObserver) == 12, "Class is wrong size!");
