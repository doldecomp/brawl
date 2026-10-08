#pragma once

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <so/so_null.h>
#include <so/so_module_accesser.h>
#include <types.h>

class soArticleEventObserver : public soEventObserver<soArticleEventObserver> {
public:
    virtual void addObserver(short param1, s8 param2);
    char _spacer1[2];
};
static_assert(sizeof(soArticleEventObserver) == 12, "Class is wrong size!");

// Local copy of BrawlHeaders' so/article/so_article.h that shadows it (-I include comes first): the original
// declares soLogAttackInfo as a bare aggregate, but the REL has an out-of-line default constructor for it
// (ftLogPatternModule builds arrays of these through __construct_array).
struct soLogAttackInfo {
    int _0;
    int _4;
    int _8;
    soLogAttackInfo(); // defined out of line in ft_log_pattern_module.cpp
    ~soLogAttackInfo() { } // non-trivial: makes array construction go through __construct_array
};

class soArticle : public soNullable, public soEventPresenter<soArticleEventObserver> {
public:
    // TODO
    virtual ~soArticle();
    virtual void remove() = 0;
    virtual int getArticleId() = 0;
    virtual int getArticleEventManageId() = 0;
    virtual int getTaskId() = 0;
    virtual void changeMotion(int motionKind, bool);
    virtual void setFrame(float frame);
    virtual void setRate(float rate);
    virtual void changeStatus(int statusKind);
    virtual void setVisibilityWhole(u8);
    virtual void setVisibility(int, u8);
    virtual void set2nd(u8);
    virtual void action(int);
    virtual void setSituationKind(SituationKind);
    virtual bool isConstraint();
    virtual void deactivateDescendantForce();
    virtual bool isActiveArticle() = 0;
    virtual void deactivateArticle() = 0;
    virtual int getOwnerDeactiveTreatType();
    virtual int getFounderTaskId();
    virtual void have(int, int, int) = 0;
    virtual void linkOwner(int, int) = 0;
    virtual void unlinkOwner(int) = 0;
    virtual bool isSyncOwnerStatus() = 0;
    virtual void setSyncOwnerStatus(bool) = 0;
    virtual void setLogAttackInfo(soLogAttackInfo* logAttackInfo);
    virtual soLogAttackInfo getLogAttackInfo();
    virtual void updateLogAttackInfo();
    virtual void intrudeLogAttackInfo();
    virtual float getActiveGlobalFrame();
    virtual void setAttackPowerMulPattern(float);
};
static_assert(sizeof(soArticle) == 20, "Class is wrong size!");
