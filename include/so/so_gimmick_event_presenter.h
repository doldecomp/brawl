#pragma once

#include <so/event/so_gimmick_event_presenter.h>

class soModuleAccesser;

// Constructor and presentEventGimmick both store/load the full sender word at
// +0xC; the observer list and its two short IDs belong to the canonical base.
class soGimmickEventPresenter : public soEventPresenter<soGimmickEventObserver> {
public:
    soGimmickEventPresenter(int manageID, int sendID);
    virtual ~soGimmickEventPresenter();
    void presentEventGimmick(soGimmickEventArgs*, soModuleAccesser*, int observerID);
    int m_sendID;
};
static_assert(sizeof(soGimmickEventPresenter) == 0x10, "Gimmick presenter size");
