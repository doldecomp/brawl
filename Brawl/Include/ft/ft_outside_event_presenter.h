#pragma once

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <types.h>

class ftOutsideEventPresenter : public soEventPresenter<ftOutsideEventPresenter> {
    int m_entryId;

public:
    virtual ~ftOutsideEventPresenter();

    void notifyOutsideEventKnockout();
};
static_assert(sizeof(ftOutsideEventPresenter) == 16, "Class is wrong size!");