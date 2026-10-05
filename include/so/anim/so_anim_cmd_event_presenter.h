#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <ac/ac_anim_cmd_impl.h>

class soModuleAccesser;

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
