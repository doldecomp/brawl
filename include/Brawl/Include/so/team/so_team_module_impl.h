#pragma once

#include <StaticAssert.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/event/so_event_presenter.h>
#include <so/so_null.h>
#include <types.h>

class soTeamEventObserver : public soEventObserver<soTeamEventObserver> {
public:
    soTeamEventObserver(s16 unitID) : soEventObserver(unitID) {
        addObserver(-1,  -1);
    }
    virtual void addObserver(s16 manageId, s8 p2);
    virtual void notifyEventChangeTeam(s32 newTeam, s32 prevTeam, u32 taskId) { }
};
static_assert(sizeof(soTeamEventObserver) == 0xC, "Class is the wrong size!");

class soTeamEventPresenter : public soEventPresenter<soTeamEventObserver> {
public:
    bool m_enableOwnerEvent;

    soTeamEventPresenter(s16 manageId) : soEventPresenter(manageId) {
        m_enableOwnerEvent = true;
    }

    virtual ~soTeamEventPresenter() { }
};
static_assert(sizeof(soTeamEventPresenter) == 0x10, "Class is the wrong size!");

class soTeam : public soNullable {
public:
    virtual ~soTeam() = 0;
    virtual s32 getNo() const = 0;
    virtual void setNo(s32 num) = 0;
    virtual s32 getIndirectNo() const = 0;
    virtual void setIndirectNo(s32 num) = 0;
    virtual s32 get2nd() const = 0;
    virtual void set2nd(s32 second) = 0;
    virtual void reset() = 0;
};
static_assert(sizeof(soTeam) == 8, "Class is the wrong size!");

class soTeamNull : public soTeam {
public:
    virtual ~soTeamNull() { }
    virtual s32 getNo() const { return -1; }
    virtual void setNo(s32 _num) { }
    virtual s32 getIndirectNo() const { return -1; }
    virtual void setIndirectNo(s32 _num) { }
    virtual s32 get2nd() const { return -1; }
    virtual void set2nd(s32 _second) { }
    virtual void reset() { }
};
static_assert(sizeof(soTeamNull) == 8, "Class is the wrong size!");

extern soTeamNull g_soTeamNull;

class soTeamImpl : public soTeam {
    s32 m_teamNo;
    s32 m_2nd;
public:
    soTeamImpl(s32 teamNo) : m_teamNo(teamNo), m_2nd(-1) { }
    virtual ~soTeamImpl() { }
    virtual s32 getNo() const { return m_teamNo; }
    virtual void setNo(s32 num) { m_teamNo = num; }
    virtual s32 getIndirectNo() const { return m_teamNo; }
    virtual void setIndirectNo(s32 _num) { }
    virtual s32 get2nd() const { return m_2nd; }
    virtual void set2nd(s32 second) { m_2nd = second; }
    virtual void reset() { }
};
static_assert(sizeof(soTeamImpl) == 0x10, "Class is the wrong size!");

class ftTeam : public soTeam {
public:
    virtual ~ftTeam();
    virtual s32 getNo() const;
    virtual void setNo(s32 num);
    virtual s32 getIndirectNo() const;
    virtual void setIndirectNo(s32 num);
    virtual s32 get2nd() const;
    virtual void set2nd(s32 p1);
    virtual void reset();
};
// TODO size assertion

class ftTeamIndirect : public ftTeam {
public:
    virtual ~ftTeamIndirect();
    virtual s32 getNo() const;
    virtual s32 getIndirectNo() const;
    virtual void setIndirectNo(s32 num);
};
// TODO size assertion

class soTeamModule : public soNullable {
public:
    soTeamModule() { }
    virtual ~soTeamModule() { }
    virtual soTeam* getTeam() = 0;
    virtual void setTeam(s32 team, bool notify) = 0;
    virtual soTeam* getHitTeam() = 0;
    virtual soTeam* getIndirectTeam() = 0;
    virtual void setHitTeam(s32 team) = 0;
    virtual void setTeamOwnerId(s32 taskId) = 0;
    virtual s32 getTeamOwnerId() = 0;
    virtual void set2nd(s32 secnd) = 0;
    virtual void setHit2nd(s32 p1) = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void reset() = 0;
    virtual void setEnableOwnerEvent(bool enable) = 0;
};
static_assert(sizeof(soTeamModule) == 8, "Class is the wrong size!");

class soTeamModuleNull : public soTeamModule {
public:
    virtual ~soTeamModuleNull() { }
    virtual soTeam* getTeam() { return &g_soTeamNull; }
    virtual void setTeam(s32 team, bool notify) { }
    virtual soTeam* getHitTeam() { return &g_soTeamNull; }
    virtual soTeam* getIndirectTeam() { return &g_soTeamNull; }
    virtual void setHitTeam(s32 team) { }
    virtual void setTeamOwnerId(s32 taskId) { }
    virtual s32 getTeamOwnerId() { return -1; }
    virtual void set2nd(s32 p1) { }
    virtual void setHit2nd(s32 p1) { }
    virtual void activate() { }
    virtual void deactivate() { }
    virtual void reset() { }
    virtual void setEnableOwnerEvent(bool enable) { }
};
static_assert(sizeof(soTeamModuleNull) == 8, "Class is the wrong size!");

class soTeamModuleImpl : public soTeamModule, public soTeamEventObserver, public soAnimCmdEventObserver {
    soModuleAccesser* m_moduleAccsr;
    soTeam* m_team;
    soTeam* m_hitTeam;
    soTeam* m_indirectTeam;
    s32 m_teamOwnerId;
    soTeamEventPresenter m_eventPresenter;
public:
    soTeamModuleImpl(soTeam* team,
                     soTeam* hitTeam,
                     soTeam* indirectTeam,
                     soModuleAccesser* accsr,
                     soEventObserverRegistrationDesc* desc);
    virtual ~soTeamModuleImpl();
    virtual soTeam* getTeam();
    virtual void setTeam(s32 team, bool notify);
    virtual soTeam* getHitTeam();
    virtual soTeam* getIndirectTeam();
    virtual void setHitTeam(s32 team);
    virtual void setTeamOwnerId(s32 taskId);
    virtual s32 getTeamOwnerId();
    virtual void set2nd(s32 p1);
    virtual void setHit2nd(s32 p1);
    virtual void activate();
    virtual void deactivate();
    virtual void reset();
    virtual void setEnableOwnerEvent(bool enable);
    virtual void notifyEventChangeTeam(s32 newTeam, s32 prevTeam, u32 taskId);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, s32 unk3);
    virtual bool isObserv(char unk1);
};
static_assert(sizeof(soTeamModuleImpl) == 0x44, "Class is the wrong size!");
