#pragma once
// SHADOW of BrawlHeaders/so/capture/so_capture_event_presenter.h: addObserver is inline in the fighter RELs (FT_MODULE_BUILDER)

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>

class soModuleAccesser;

class soCaptureEventObserver : public soEventObserver<soCaptureEventObserver> {
public:
    soCaptureEventObserver(short unitID) : soEventObserver<soCaptureEventObserver>(unitID) {};

#ifdef FT_MODULE_BUILDER
    virtual void addObserver(short param1, s8 param2) { addObserverSub(param1, this, param2); } // MATCH-ONLY: inline in the REL
#else
    virtual void addObserver(short param1, s8 param2);
#endif
    virtual bool notifyEventCaptureStatus(soModuleAccesser* moduleAccesser, int taskId, int, int);
};
static_assert(sizeof(soCaptureEventObserver) == 12, "Class is wrong size!");