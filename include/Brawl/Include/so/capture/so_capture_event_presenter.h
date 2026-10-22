#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>

class soModuleAccesser;

class soCaptureEventObserver : public soEventObserver<soCaptureEventObserver> {
public:
    soCaptureEventObserver(short unitID) : soEventObserver<soCaptureEventObserver>(unitID) {};

    virtual void addObserver(short param1, s8 param2);
    virtual bool notifyEventCaptureStatus(soModuleAccesser* moduleAccesser, int taskId, int, int);
};
static_assert(sizeof(soCaptureEventObserver) == 12, "Class is wrong size!");