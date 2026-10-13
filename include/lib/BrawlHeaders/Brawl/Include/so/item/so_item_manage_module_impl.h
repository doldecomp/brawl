#pragma once

#include <StaticAssert.h>
#include <so/item/so_item_manage_event_presenter.h>
#include <so/link/so_link_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/item/so_item_pick_transactor_impl.h>
#include <so/so_null.h>
#include <so/so_array.h>
#include <types.h>

class soModuleAccesser;
class BaseItem;

struct soItemNodeData {
    struct AttachData {
        itKind m_itKind;
        u32 m_nodeIndex;
        char m_8[0x8];
    };
    static_assert(sizeof(AttachData) == 0x10, "Class is wrong size!");

    u32 m_haveNNodeIndex;
    u32 m_haveNNodeIndex_;
    u32 m_throwNNodeIndex;
    u32 m_numAttachNodes;
    AttachData* m_attachNodesData;
    char _0x14[4];
};
static_assert(sizeof(soItemNodeData) == 0x18, "Class is wrong size!");

class soItemManageModule : public soNullable {
public:
    virtual ~soItemManageModule();
    virtual void activate();
    virtual void deactivate();
    virtual void begin();
    virtual void check();
    virtual bool haveItem(itKind kind, u32 variation, u32 index, bool);
    virtual bool createThrowItem(itKind kind, u32 variation, u32 nodeIndex, float angle, float speed, float power);
    virtual bool haveItem(BaseItem* item, u32 index, bool, bool);
    virtual bool haveItem(u32 nodeIndex, BaseItem* item, u32 index, bool, bool);
    virtual bool useItem(BaseItem* item);
    virtual bool attachItem(BaseItem* item, bool);
    virtual bool pickupItem(u8, u32, u32, u32 index);
    virtual bool isSuccessPickupItem();
    virtual bool isHaveItem(u32 index);
    virtual itParam::SizeKind getHaveItemSize(u32 index);
    virtual itKind getHaveItemKind(u32 index);
    virtual itParam::TraitFlag getHaveItemTrait(u32 index);
    virtual itParam::HaveKind getHaveItemHoldKind(u32 index);
    virtual int getHaveItemParamInt(u32, u32 index);
    virtual float getHaveItemParamFloat(u32, u32 index);
    virtual void getHaveItemInfo(soItemInfo*, u32 index);
    virtual itParam::SizeKind getPickableItemSize();
    virtual itKind getPickableItemKind();
    virtual itParam::TraitFlag getPickableItemTrait();
    virtual void getPickableItemInfo(soItemInfo*);
    virtual bool removeItem(BaseItem*);
    virtual void removeItem(u32 index);
    virtual void removeAll();
    virtual void throwItem(float angle, float speed, float power, u32 index);
    virtual void throwItem(float angle, float speed, float power, Vec2f* pos, u32 index);
    virtual void dropItem(float, float, u32 index);
    virtual void useItem(u32 index);
    virtual void warpItem(Vec3f* pos, u32 index);
    virtual void bornItem(u32 index);
    virtual void shootItemBullet(u32, float, u32 index);
    virtual void shootItemBulletBlanks(u32, u32 index);
    virtual u32 getShootItemBullet(u32 index);
    virtual void updateHaveItemActionInfo(u32 index);
    virtual void setHaveItemScaleAnim(float, u32, u32 index);
    virtual void setHaveItemAction(u32, float, u32 index);
    virtual void setHaveItemVisibility(u8, int index);
    virtual void setHaveItemHoldAnim(bool, u32 index);
    virtual void setHaveItemConstraintNode(u32, u32 index);
    virtual void resetHaveItemConstraintNode(u32 index);
    virtual bool attachItem(itKind, u32 variation, bool);
    virtual bool isAttachItem(itKind);
    virtual u32 getAttachItemCount();
    virtual void getAttachItemInfo(soItemInfo*, u32 index);
    virtual void setAttachItemVisibility(u8, itParam::AttachGroup);
    virtual u8 getAttachItemVisibility();
    virtual void ejectHaveItem(u32 index, bool, bool);
    virtual void ejectAttachItem(u32 index, bool, bool);
    virtual void eject(int taskId);
    virtual void ejectAttach(itKind, bool, bool);
    virtual void dropAttach(itKind, float, float);
    virtual void dropAttachGroup(itParam::AttachGroup, float, float);
    virtual void scaleAttach(itKind, float);
    virtual void scaleItem(BaseItem*, float);
    virtual void setHaveItemTeam(int, u32 index);
};

class soItemManageModuleImpl : public soItemManageModule, public soLinkEventObserver, public soStatusEventObserver, public soAnimCmdEventObserver, public soEventPresenter<soItemManageEventObserver> {
    soArray<soItemInfo>* m_haveItemInfoArray;
    soItemNodeData* m_itemNodeData;
    soArray<soItemInfo>* m_attachItemInfoArray;
    soItemSearch* m_itemSearch;
    soItemPickTransactor* m_itemPickTransactor;
    soItemInfo m_pickableItemInfo;
    bool m_isSuccessPickupItem;
    char _0x61[3];
    u8 m_attachItemVisibility;
    char _0x65[3];
    soModuleAccesser* m_moduleAccesser;

public:
    virtual ~soItemManageModuleImpl();
    virtual void activate();
    virtual void deactivate();
    virtual void begin();
    virtual void check();
    virtual bool haveItem(itKind kind, u32 variation, u32 index, bool);
    virtual bool createThrowItem(itKind kind, u32 variation, u32 nodeIndex, float angle, float speed, float power);
    virtual bool haveItem(BaseItem* item, u32 index, bool, bool);
    virtual bool haveItem(u32 nodeIndex, BaseItem* item, u32 index, bool, bool);
    virtual bool useItem(BaseItem* item);
    virtual bool attachItem(BaseItem* item, bool);
    virtual bool pickupItem(u8, u32, u32, u32 index);
    virtual bool isSuccessPickupItem();
    virtual bool isHaveItem(u32 index);
    virtual itParam::SizeKind getHaveItemSize(u32 index);
    virtual itKind getHaveItemKind(u32 index);
    virtual itParam::TraitFlag getHaveItemTrait(u32 index);
    virtual itParam::HaveKind getHaveItemHoldKind(u32 index);
    virtual int getHaveItemParamInt(u32, u32 index);
    virtual float getHaveItemParamFloat(u32, u32 index);
    virtual void getHaveItemInfo(soItemInfo*, u32 index);
    virtual itParam::SizeKind getPickableItemSize();
    virtual itKind getPickableItemKind();
    virtual itParam::TraitFlag getPickableItemTrait();
    virtual void getPickableItemInfo(soItemInfo*);
    virtual bool removeItem(BaseItem*);
    virtual void removeItem(u32 index);
    virtual void removeAll();
    virtual void throwItem(float angle, float speed, float power, u32 index);
    virtual void throwItem(float angle, float speed, float power, Vec2f* pos, u32 index);
    virtual void dropItem(float, float, u32 index);
    virtual void useItem(u32 index);
    virtual void warpItem(Vec3f* pos, u32 index);
    virtual void bornItem(u32 index);
    virtual void shootItemBullet(u32, float, u32 index);
    virtual void shootItemBulletBlanks(u32, u32 index);
    virtual u32 getShootItemBullet(u32 index);
    virtual void updateHaveItemActionInfo(u32 index);
    virtual void setHaveItemScaleAnim(float, u32, u32 index);
    virtual void setHaveItemAction(u32, float, u32 index);
    virtual void setHaveItemVisibility(u8, int index);
    virtual void setHaveItemHoldAnim(bool, u32 index);
    virtual void setHaveItemConstraintNode(u32, u32 index);
    virtual void resetHaveItemConstraintNode(u32 index);
    virtual bool attachItem(itKind, u32 variation, bool);
    virtual bool isAttachItem(itKind);
    virtual u32 getAttachItemCount();
    virtual void getAttachItemInfo(soItemInfo*, u32 index);
    virtual void setAttachItemVisibility(u8, itParam::AttachGroup);
    virtual u8 getAttachItemVisibility();
    virtual void ejectHaveItem(u32 index, bool, bool);
    virtual void ejectAttachItem(u32 index, bool, bool);
    virtual void eject(int taskId);
    virtual void ejectAttach(itKind, bool, bool);
    virtual void dropAttach(itKind, float, float);
    virtual void dropAttachGroup(itParam::AttachGroup, float, float);
    virtual void scaleAttach(itKind, float);
    virtual void scaleItem(BaseItem*, float);
    virtual void setHaveItemTeam(int, u32 index);

    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual bool isObserv(char unk1);
    virtual void notifyEventLink(soLinkEventArgs *eventInfo, soModuleAccesser* moduleAccesser, StageObject*, int unk4);
};
static_assert(sizeof(soItemManageModuleImpl) == 0x6c, "Class is wrong size!");

