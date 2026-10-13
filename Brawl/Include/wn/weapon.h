#pragma once

#include <StaticAssert.h>
#include <so/article/so_article.h>
#include <so/event/so_event_presenter.h>
#include <so/stageobject.h>
#include <so/status/so_status_event_presenter.h>
#include <types.h>

class Weapon : public StageObject, public soStatusEventObserver, public soCollisionAttackEventObserver, public soCollisionHitEventObserver, public soArticle {

    char unk9C[0x34];

public:
    struct Instance {
        struct Work {
            enum Int {
                Int_Activate_Founder_Id = 0x10000000,

                Int_Init_Life = 0x10000003,
                Int_Life = 0x10000004,
            };
            enum Float {
                Float_Active_Global_Frame = 0x11000000,
            };
            enum Flag {
            };
        };
    };

    virtual void processUpdate();
    virtual void processFixPosition();
    virtual void processHit();
    virtual void processFixCamera();
    virtual ~Weapon();

    virtual void updatePosture(bool);
    virtual soKind soGetKind();
    virtual int soGetSubKind();
    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventLink(soLinkEventArgs *eventInfo, soModuleAccesser* moduleAccesser, StageObject*, int unk4);

    virtual void remove();
    virtual void changeMotion(int motionKind, bool);
    virtual void setFrame(float);
    virtual void setRate(float);
    virtual void changeStatus(int statusKind);
    virtual void setVisibilityWhole(u8);
    virtual void setVisibility(int, u8);
    virtual void set2nd(u8);
    virtual void setSituationKind(SituationKind);
    virtual bool isConstraint();
    virtual void have(int, int, int);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual int getArticleId();
    virtual int getArticleEventManageId();
    virtual int getTaskId();
    virtual int getFounderTaskId();
    virtual void linkOwner(int, int);
    virtual void unlinkOwner(int);
    virtual bool isActiveArticle();
    virtual void deactivateArticle();
    virtual float getActiveGlobalFrame();
    virtual bool isSyncOwnerStatus();
    virtual void setSyncOwnerStatus(bool);
    virtual void notifyEventCollisionAttack(float power, soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionAttackCheck(u32 flags);
    virtual void notifyEventCollisionHit(float power, soCollisionAttackData*, u32 index, int, soModuleAccesser* moduleAccesser, soCollisionLog*);
    virtual void notifyEventCollisionHit2nd(float posX, float collisionLr, soCollisionAttackModule*, soCollisionLog*, u32 groupIndex, soModuleAccesser* moduleAccesser, bool);
    virtual int getOwnerDeactiveTreatType();
    virtual void initialize();
    virtual void onDeactivate();
    virtual bool reflect();
    virtual bool hop();
    virtual void reflectSettingTeam();
    virtual void deactivate(bool);
    virtual void setLogAttackInfo(soLogAttackInfo* logAttackInfo);
    virtual soLogAttackInfo getLogAttackInfo();
    virtual void updateLogAttackInfo();
    virtual void setAttackPowerMulPattern(float);
    virtual void setPosForce(Vec3f*);
    virtual bool isCanInhaled();
    virtual bool isInhaled();
    virtual Vec3f startInhaled();
    virtual void updateInhaled();
    virtual void endInhaled();
    virtual Vec3f* getInhaledStartPos();
    virtual int getInhaledCount();
    virtual bool isCanEat();
};
static_assert(sizeof(Weapon) == 0xD0, "Class is wrong size!");
