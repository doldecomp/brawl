#pragma once

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/collision/so_collision_attack_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/transition/so_transition_module_impl.h>
#include <so/so_null.h>
#include <types.h>

class soModuleAccesser;

class soStatusUniqProcess {
public:
    virtual ~soStatusUniqProcess() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser) { }
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int) { }
    virtual void execStatus(soModuleAccesser* moduleAccesser) { }
    virtual void execStop(soModuleAccesser* moduleAccesser) { }
    virtual void execMapCorrection(soModuleAccesser* moduleAccesser) { }
    virtual void execFixPosCounter(soModuleAccesser* moduleAccesser) { }
    virtual void execFixPos(soModuleAccesser* moduleAccesser) { }
    virtual void execFixCamera(soModuleAccesser* moduleAccesser) { }
    virtual bool checkDamage(soModuleAccesser* moduleAccesser, void*) {
        return false;
    }
    virtual void checkAttack(soModuleAccesser* moduleAccesser, void*, float) { }
    virtual bool onChangeLr(soModuleAccesser* moduleAccesser, float, float) {
        return false;
    }
    virtual void leaveStop(soModuleAccesser* moduleAccesser, int, bool) { }
    virtual bool checkTransitionPrecede(soModuleAccesser* moduleAccesser, int*) {
        return true;
    }
};
static_assert(sizeof(soStatusUniqProcess) == 4, "Class is the wrong size!");

class soStatusUniqProcessNull : public soStatusUniqProcess {
public:
    virtual ~soStatusUniqProcessNull() { }
};
static_assert(sizeof(soStatusUniqProcessNull) == 4, "Class is the wrong size!");

class soStatusModule : public soNullable {
public:
    virtual void activate(soModuleAccesser* moduleAccesser);
    virtual void deactivate(soModuleAccesser* moduleAccesser);
    virtual bool changeStatusRequest(int status, soModuleAccesser* moduleAccesser);
    virtual void processFixPosition(soModuleAccesser* moduleAccesser, bool);
    virtual void begin();
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
    virtual void execMapCorrection(soModuleAccesser* moduleAccesser);
    virtual void execFixPosCounter(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual void execFixCamera(soModuleAccesser* moduleAccesser);
    virtual bool checkDamage(soModuleAccesser* moduleAccesser, void*);
    virtual void checkAttack(soModuleAccesser* moduleAccesser, void*, float);
    virtual bool onChangeLr(soModuleAccesser* moduleAccesser, float, float);
    virtual void leaveStop(soModuleAccesser* moduleAccesser, int, bool);
    virtual int getStatusKind();
    virtual bool isCollisionAttackOccer();
    virtual bool isCollisionAttackTarget(u32* collisionAttackCategory);
    virtual void startWatchChange();
    virtual bool isChanged();
    virtual bool checkTransition(soModuleAccesser* moduleAccesser);
    virtual void enableTransitionTermGroup(int groupID);
    virtual void unableTransitionTermGroup(int groupID);
    virtual bool isEnableTransitionTermGroup(int groupID);
    virtual void enableTransitionTermAll(int);
    virtual void clearTransitionTermAll(int);
    virtual void* getLastStatusTransitionInfo();
    virtual void addRangeUniqProc(soStatusUniqProcess* uniqProcs, u32 numUniqProcs);
    virtual char* getStatusName();
    virtual char* getStatusName(int);
    virtual u32 getStatusGroundCorrect(int);
    virtual int getPrevStatusKind(u32);
    virtual void connectStatusDataList(void*);
    virtual void changeStatusForce(int status, soModuleAccesser* moduleAccesser);
    virtual void unableTransitionTerm(int, int);
    virtual void setUniqProc(u32 index, soStatusUniqProcess* uniqProc);
    virtual ~soStatusModule();
    virtual void changeStatus(int status, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soStatusModule) == 8, "Class is wrong size!");

class soStatusModuleImpl : public soStatusModule, public soEventPresenter<soStatusEventObserver>, public soAnimCmdEventObserver, public soCollisionAttackEventObserver {

public:
    soTransitionModule* m_transitionModule;
    soArray<soStatusUniqProcess>* m_statusUniqProcessArr;
    int m_statusKind;
    int m_nextStatusKind;
private:
    char _spacer[0x68];
public:
    virtual void activate(soModuleAccesser* moduleAccesser);
    virtual void deactivate(soModuleAccesser* moduleAccesser);
    virtual bool changeStatusRequest(int status, soModuleAccesser* moduleAccesser);
    virtual void processFixPosition(soModuleAccesser* moduleAccesser, bool);
    virtual void begin();
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
    virtual void execMapCorrection(soModuleAccesser* moduleAccesser);
    virtual void execFixPosCounter(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual void execFixCamera(soModuleAccesser* moduleAccesser);
    virtual bool checkDamage(soModuleAccesser* moduleAccesser, void*);
    virtual void checkAttack(soModuleAccesser* moduleAccesser, void*, float);
    virtual bool onChangeLr(soModuleAccesser* moduleAccesser, float, float);
    virtual void leaveStop(soModuleAccesser* moduleAccesser, int, bool);
    virtual int getStatusKind();
    virtual bool isCollisionAttackOccer();
    virtual bool isCollisionAttackTarget(u32* collisionAttackCategory);
    virtual void startWatchChange();
    virtual bool isChanged();
    virtual bool checkTransition(soModuleAccesser* moduleAccesser);
    virtual void enableTransitionTermGroup(int groupID);
    virtual void unableTransitionTermGroup(int groupID);
    virtual bool isEnableTransitionTermGroup(int groupID);
    virtual void enableTransitionTermAll(int);
    virtual void clearTransitionTermAll(int);
    virtual void* getLastStatusTransitionInfo();
    virtual void addRangeUniqProc(soStatusUniqProcess* uniqProcs, u32 numUniqProcs);
    virtual char* getStatusName();
    virtual char* getStatusName(int);
    virtual u32 getStatusGroundCorrect(int);
    virtual int getPrevStatusKind(u32);
    virtual void connectStatusDataList(void*);
    virtual void changeStatusForce(int status, soModuleAccesser* moduleAccesser);
    virtual void unableTransitionTerm(int, int);
    virtual void setUniqProc(u32 index, soStatusUniqProcess* uniqProc);
    virtual ~soStatusModuleImpl();
    virtual void changeStatus(int status, soModuleAccesser* moduleAccesser);

    virtual bool notifyEventCollisionAttackCheck(u32 flags);
    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventCollisionAttack(float power, soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);;
};
static_assert(sizeof(soStatusModuleImpl) == 0xA4, "Class is wrong size!");

extern soStatusUniqProcessNull g_soStatusUniqProcessNull;
