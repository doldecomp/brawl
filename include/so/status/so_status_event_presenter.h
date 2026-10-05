#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>
#include <so/so_common_data_accesser.h>

class soModuleAccesser;

class soStatusEventObserver : public soEventObserver<soStatusEventObserver> {
public:
    soStatusEventObserver() : soEventObserver<soStatusEventObserver>(0x4) {};
    soStatusEventObserver(short unitID) : soEventObserver<soStatusEventObserver>(unitID) {};
    // NOTE: shadows the BrawlHeaders copy; (manageId, p2) constructor added by agent/damage
    soStatusEventObserver(short manageId, s8 p2) : soEventObserver<soStatusEventObserver>(0x4) { initialize(manageId, p2); }

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soStatusEventObserver) == 12, "Class is wrong size!");
