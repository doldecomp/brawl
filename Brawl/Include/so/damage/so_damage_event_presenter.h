#pragma once

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

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventOnDamage(soDamage* damage, bool, soModuleAccesser* moduleAccesser);
    virtual void notifyEventAddDamage(soDamage* damage, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soDamageEventObserver) == 12, "Class is wrong size!");
