#pragma once
// SHADOW of BrawlHeaders/so/item/so_item_manage_event_presenter.h: addObserver is inline in the fighter RELs (FT_MODULE_BUILDER)

#include <StaticAssert.h>
#include <types.h>
#include <it/it_archive.h>
#include <so/event/so_event_presenter.h>

class soModuleAccesser;
class BaseItem;

class soItemManageEventObserver : public soEventObserver<soItemManageEventObserver> {
public:
    soItemManageEventObserver(short unitID) : soEventObserver<soItemManageEventObserver>(unitID) {};

#ifdef FT_MODULE_BUILDER
    virtual void addObserver(short param1, s8 param2) { addObserverSub(param1, this, param2); } // MATCH-ONLY: inline in the REL
#else
    virtual void addObserver(short param1, s8 param2);
#endif
    virtual bool notifyHaveItemPreCheck(BaseItem* item, bool*);
    virtual void notifyHaveItem(itParam::SizeKind, BaseItem* item, u32 nodeIndex, u32 index, bool);
    virtual void notifyAttachItem(BaseItem* item, u32 nodeIndex, u32 attachNodeIndex, bool, bool);
    virtual void notifyUseItem(BaseItem* item, u32 nodeIndex, int*);
    virtual void notifyThrowItem(BaseItem* item, u32 nodeIndex, int*);
    virtual void notifyDropItem(BaseItem*);
    virtual void notifyShootBulletItem(BaseItem* item);
    virtual void notifyEjectItem(BaseItem* item, u32 index, bool);
    virtual void notifyEjectAttachItem(BaseItem* item, u32 index, bool);
    virtual void notifyVisibilityItem(BaseItem* item, int, bool, u8);
};
static_assert(sizeof(soItemManageEventObserver) == 12, "Class is wrong size!");