#pragma once

// Local shadow of BrawlHeaders' ft/ft_outside_event_presenter.h. The presenter that sends the fighter manager's
// "outside" events (deaths, KOs, final smash, ...) to the observers of ftOutsideEventObserver. The BrawlHeaders copy
// derives from soEventPresenter<ftOutsideEventPresenter>; the observer list type is ftOutsideEventObserver
// (the REL names soEventPresenter<ftOutsideEventObserver> and its event unit wrapper).
// The constructor is defined in ft/ft_manager.h, once ftOutsideEventObserver is complete.

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <types.h>

class ftOutsideEventObserver;

class ftOutsideEventPresenter : public soEventPresenter<ftOutsideEventObserver> {
    int m_entryId;

public:
    inline ftOutsideEventPresenter(s16 manageId, int entryId);
    virtual ~ftOutsideEventPresenter() { }

    void notifyOutsideEventKnockout();
    void notifyOutsideEventOnInput();
    void notifyOutsideEventSuicide(int entryId);
    void notifyOutsideEventBeat(int winningEntryId, int losingEntryId);
    void notifyOutsideEventDead(int entryId, int deadCount, int deadReason, int respawnFrames);
};
static_assert(sizeof(ftOutsideEventPresenter) == 16, "Class is wrong size!");
