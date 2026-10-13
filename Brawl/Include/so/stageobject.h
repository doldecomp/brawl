#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <memory.h>
#include <so/so_activate.h>
#include <so/so_array.h>
#include <so/so_kind.h>
#include <so/so_module_accesser.h>
#include <so/event/so_gimmick_event_presenter.h>
#include <so/link/so_link_event_presenter.h>
#include <so/so_null.h>
#include <types.h>

class StageObject : public gfTask, private soActivatable, public soAnimCmdEventObserver, public soLinkEventObserver {
public:

    struct Link {
        enum No {
            No_Capture = 0x0,
        };

        enum EventKind {
            Event_Deactivate_Parent = 0,
            Event_Dead = 2,
            Event_Deactivate_Node = 4,

            Event_Yoshi_Special_N_Catch = 29,
            Event_Yoshi_Special_N_Swallow = 30,

            Event_Disconnect_Parent = 60,
            Event_Disconnect_Node = 61,
            Event_Touch_Item = 62,
        };
    };

    struct AnimCmd {
        enum Type {
            Type_Update_Node_SRT = 0x1,
            Type_Set_Inactive = 0x2,
            Type_Set_Active = 0x3,
            Type_Set_Air = 0x4,
        };
    };

    soModuleAccesser* m_moduleAccesser;
    StageObject(const char* name, int unk1, int unk2, int unk3, int unk4, soModuleAccesser* moduleAccesser);
    virtual void processAnim();
    virtual void processUpdate();
    virtual void processPreMapCorrection();
    virtual void processMapCorrection();
    virtual void processFixPosition();
    virtual void processPreCollision();
    virtual void processCollision();
    virtual void processCatch();
    virtual void processHit();
    virtual void processFixCamera();
    virtual void processGameProc();
    virtual void processEnd();
    virtual void renderPre();
    virtual void processDebug();
    virtual void renderDebug();
    virtual ~StageObject();

    // TODO: Verify params?
    virtual void updatePosture(bool);
    virtual void processFixPositionPreAnimCmd();
    virtual Input* getInput();
    virtual float getCollisionLr(soModuleAccesser*);
    virtual soKind soGetKind();
    virtual int soGetSubKind();
    virtual bool isActive();
    virtual bool checkTransitionStatus(u32);
    virtual void updateNodeSRT();
    virtual void adjustParentGroundCollision(int unk1, float* unk2);
    virtual bool isTreadPassive();
    virtual void notifyLostGround(soModuleAccesser*);

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventLink(soLinkEventArgs *eventInfo, soModuleAccesser* moduleAccesser, StageObject*, int unk4);

    virtual void notifyArticleEventRemove(int unk1, int* unk2);
    virtual void notifyArticleEventEject(int unk1, int unk2, int* unk3, int* unk4);
    virtual void updateRoughPos();

    void activate(Vec3f* pos, float lr, float, bool);
};
static_assert(sizeof(StageObject) == 0x64, "Class is wrong size!");

class BaseItem;
struct soLinkTouchItemEventArgs : public soLinkEventArgs {
    BaseItem* m_item;
    Vec3f m_pos;
    float m_0x18;
    bool m_0x1C;

    inline soLinkTouchItemEventArgs(BaseItem* item, Vec3f& pos, float arg3, bool arg4) : soLinkEventArgs(StageObject::Link::Event_Touch_Item), m_item(item), m_pos(pos), m_0x18(arg3), m_0x1C(arg4) {}
};
static_assert(sizeof(soLinkTouchItemEventArgs) == 0x20, "Class is wrong size!");

struct UnkLinkEvent : public soLinkEventArgs {

    u32 unk8;

    inline UnkLinkEvent(u32 p1, u32 p3) : soLinkEventArgs(p1), unk8(p3) { }
};
