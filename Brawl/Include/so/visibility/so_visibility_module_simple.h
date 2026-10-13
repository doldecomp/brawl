#pragma once

#include <StaticAssert.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/so_common_data_accesser.h>
#include <types.h>

class soModuleAccesser;

class soVisibilityModule {
public:
    virtual void activate();
    virtual void setData(soVisibilityData*);
    virtual void set(u32, u8);
    virtual void setStatusDefault(u32, u8, bool);
    virtual void setDefaultAll();
    virtual void update();
    virtual void hideAll();
    virtual void setWhole(u8);
    virtual u8 getWhole();
    virtual bool isVisible();
    virtual int get(u32);
};

class soVisibilityModuleSimple : public soVisibilityModule, public soAnimCmdEventObserver {
    u8 m_whole;
    char _0xe[1];
    soModuleAccesser* m_moduleAccesser;

public:
    virtual void activate();
    virtual void setData(soVisibilityData*);
    virtual void set(u32, u8);
    virtual void setStatusDefault(u32, u8, bool);
    virtual void setDefaultAll();
    virtual void update();
    virtual void hideAll();
    virtual void setWhole(u8);
    virtual u8 getWhole();
    virtual bool isVisible();
    virtual int get(u32);

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
};
static_assert(sizeof(soVisibilityModuleSimple) == 0x14, "Class is wrong size!");
