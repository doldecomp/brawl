#pragma once

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>

class soShadowModule {
public:
    virtual ~soShadowModule();
    virtual void activate();
    virtual void deactivate();
    virtual void setActive(bool);
    virtual void setActiveStatus(int status);
    virtual void update();
    virtual void setSize(int);
    virtual void setNode(void*);
    virtual void setSizeMinMax(float, float);
    virtual void setYOffset(float);
    virtual void setGroundRef(int);
    virtual void setSizeMul(float);
    virtual void setGroundPokemon(int);
    virtual int getMode(); // maybe static? unsure.
    virtual void setIgnoreMode(int);
    virtual bool isDispProjection();
};

class soShadowModuleImpl: public soShadowModule, public soStatusEventObserver, public soAnimCmdEventObserver, public soModelEventObserver {
public:
    virtual ~soShadowModuleImpl();
    virtual void activate();
    virtual void deactivate();
    virtual void setActive(bool);
    virtual void setActiveStatus(int status);
    virtual void update();
    virtual void setSize(int);
    virtual void setNode(void*);
    virtual void setSizeMinMax(float, float);
    virtual void setYOffset(float);
    virtual void setGroundRef(int);
    virtual void setSizeMul(float);
    virtual void setGroundPokemon(int);
    virtual int getMode(); // maybe static? unsure.
    virtual void setIgnoreMode(int);
    virtual bool isDispProjection();

    // statusEventObserver
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);

    // animCmdEventObserver
    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);

    // modelEventObserver
    virtual void notifyEventDestructInstance(soModuleAccesser* moduleAccesser);

    soModuleAccesser* m_moduleAccesser; // 0x28
    float _0x2C;
    float _0x30;
    float _0x34;
    float _0x38;
    float _0x3C;
    int _0x40;
    char _0x44; // looks like a bitfield of some kind.
};
// Class is actually 0x45, but the extra space is padded out in Brawl anyway.
static_assert(sizeof(soShadowModuleImpl) == 0x48, "Class is wrong size!");

class soShadowModuleNull : soShadowModule {
public:
    virtual ~soShadowModuleNull();
    virtual void activate();
    virtual void deactivate();
    virtual void setActive(bool);
    virtual void setActiveStatus(int status);
    virtual void update();
    virtual void setSize(int);
    virtual void setNode(void*);
    virtual void setSizeMinMax(float, float);
    virtual void setYOffset(float);
    virtual void setGroundRef(int);
    virtual void setSizeMul(float);
    virtual void setGroundPokemon(int);
    virtual int getMode(); // maybe static? unsure.
    virtual void setIgnoreMode(int);
    virtual bool isDispProjection();
};