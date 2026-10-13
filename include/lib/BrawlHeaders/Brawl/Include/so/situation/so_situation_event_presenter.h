#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>

class soModuleAccesser;

enum SituationKind {
    Situation_None = -0x1,
    Situation_Ground = 0x0,
    Situation_Cliff = 0x1,
    Situation_Air = 0x2,
    Situation_Water = 0x3,
    Situation_Restraint = 0x4,
    Situation_Outfield = 0x5,
    Situation_Ladder = 0x6,
    Situation_ODD = 0x7
};

class soSituationEventObserver : public soEventObserver<soSituationEventObserver> {
public:
    soSituationEventObserver(short unitID) : soEventObserver<soSituationEventObserver>(unitID) {};

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventChangeSituation(SituationKind kind, SituationKind prevKind, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soSituationEventObserver) == 12, "Class is wrong size!");
