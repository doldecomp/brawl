#pragma once

#include <StaticAssert.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/situation/so_situation_event_presenter.h>
#include <so/so_common_data_accesser.h>
#include <so/so_null.h>
#include <so/status/so_status_event_presenter.h>
#include <types.h>

class soModuleAccesser;

class ftCancelModule : public soNullable {
public:
    ftCancelModule(bool isNull) : soNullable(isNull) { }
    virtual void postInitialize(soModuleAccesser* moduleAccesser) = 0;
    virtual bool isEnableCancel() const = 0;
    virtual void processFixPosition() = 0;
    virtual void unableCancelStatus() = 0;
};
static_assert(sizeof(ftCancelModule) == 0x8, "Class is the wrong size!");

class ftCancelModuleImpl :
    public ftCancelModule,
    public soStatusEventObserver,
    public soAnimCmdEventObserver,
    public soSituationEventObserver {

    void enableCancelTransitionGroup(SituationKind kind);
public:
    ftCancelModuleImpl(soModuleAccesser* accsr);
    // UBFIX should have been virtual
    ~ftCancelModuleImpl() { }
    virtual void postInitialize(soModuleAccesser* moduleAccesser);
    virtual bool isEnableCancel() const;
    virtual void processFixPosition();
    virtual void unableCancelStatus();
    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, s32 unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void notifyEventChangeSituation(SituationKind kind, SituationKind prevKind, soModuleAccesser* moduleAccesser);
};
// TODO size assertion

class ftCancelModuleNull : public ftCancelModule {
public:
    ftCancelModuleNull() : ftCancelModule(true) { }
    virtual void postInitialize(soModuleAccesser* moduleAccesser) { }
    virtual bool isEnableCancel() const { return false; }
    virtual void processFixPosition() { }
    virtual void unableCancelStatus() { }
};
static_assert(sizeof(ftCancelModuleNull) == 0x8, "Class is the wrong size!");
