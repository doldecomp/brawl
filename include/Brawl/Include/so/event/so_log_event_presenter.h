#pragma once

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <types.h>

class soLogEventObserver : public soEventObserver<soDisposeInstanceEventObserver> {
public:
    virtual void addObserver(short param1, s8 param2);
    virtual void notifyLogEventCollisionHit(float, int taskId1, int taskId2, int);
    virtual void notifyLogEventGroundDamage(); // TODO
    virtual void notifyLogEventDead(int entryId1, int entryId2, int, int);
    char _spacer1[2];
};
static_assert(sizeof(soLogEventObserver) == 12, "Class is wrong size!");
