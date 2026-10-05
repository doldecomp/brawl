#pragma once

// NOTE: shadows the BrawlHeaders copy to name the soStatusModuleImpl members (offsets from the
// constructor / accessors in so_status_module_impl.o).

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/collision/so_collision_attack_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/transition/so_transition_module_impl.h>
#include <so/collision/so_collision_log.h>
#include <so/so_array.h>
#include <so/so_null.h>
#include <so/work/so_general_work_abstract.h>
#include <types.h>

class soModuleAccesser;

// HYPOTHESIS: layout of the last collision-attack log kept by the status module (copied from the
// soCollisionLog passed to notifyEventCollisionAttack; field types inferred from the copy code).
struct soStatusCollisionLogCopy {
    struct { u32 a; u32 b; } m_unk00;
    u32 m_unk08;
    u32 m_taskId;
    u32 m_pos[3];
    u16 m_life;
    u16 m_unk1e;
    u8 m_unk20;
    u8 m_unk21;
    u8 m_taskCategory;
    u8 m_unk23;
    u8 m_unk24;
    u8 m_unk25;
    u8 m_unk26;
    u8 m_unk27;
    u8 m_unk28;
    u8 m_unk29;
    u8 m_unk2a;
};
static_assert(sizeof(soStatusCollisionLogCopy) == 0x2C, "Class is wrong size!");


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
    // HYPOTHESIS: (accesser, last transition info, target status); the BrawlHeaders copy has (accesser, int*).
    virtual bool checkTransitionPrecede(soModuleAccesser* moduleAccesser, void* transitionInfo, int target) {
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
    virtual void addRangeUniqProc(soStatusUniqProcess** uniqProcs, u32 numUniqProcs);
    virtual char* getStatusName();
    virtual char* getStatusName(int);
    virtual u32 getStatusGroundCorrect(int);
    virtual int getPrevStatusKind(u32);
    virtual void connectStatusDataList(void*);
    virtual void changeStatusForce(int status, soModuleAccesser* moduleAccesser);
    virtual void unableTransitionTerm(int, int);
    virtual void setUniqProc(u32 index, soStatusUniqProcess* uniqProc);
    virtual ~soStatusModule() { }
    virtual void changeStatus(int status, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soStatusModule) == 8, "Class is wrong size!");

class soStatusModuleImpl : public soStatusModule, public soEventPresenter<soStatusEventObserver>, public soAnimCmdEventObserver, public soCollisionAttackEventObserver {

public:
    soTransitionModule* m_transitionModule;                // +0x2c
    soArray<soStatusUniqProcess*>* m_statusUniqProcessArr; // +0x30
    int m_statusKind;                                      // +0x34
    int m_nextStatusKind;                                  // +0x38
    soGeneralWorkAbstract* m_generalWork;                  // +0x3c
    soArrayContractibleTable<const soStatusData>* m_statusDataArr; // +0x40 (HYPOTHESIS: table of const soStatusData)
    void** m_preCheckAnimCmdArr;                           // +0x44
    int m_preCheckAnimCmdNum;                              // +0x48
    soArrayVector<s32, 8> m_changeRequestQueue;            // +0x4c
    soArray<s32>** m_statusHistory;                        // +0x78 (HYPOTHESIS)
    bool m_unk7c;                                          // +0x7c
    bool m_unk7d;                                          // +0x7d
    bool m_isChanged;                                      // +0x7e
    bool m_isCollisionAttackOccer;                         // +0x7f
    soStatusCollisionLogCopy m_collisionLog;               // +0x80
    void succeedStatusWork(const soStatusData* statusData);

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
    virtual void addRangeUniqProc(soStatusUniqProcess** uniqProcs, u32 numUniqProcs);
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

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, s32 unk3);
    virtual void notifyEventCollisionAttack(float power, soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);;
};
static_assert(sizeof(soStatusModuleImpl) == 0xAC, "Class is wrong size!");

extern soStatusUniqProcessNull g_soStatusUniqProcessNull;
