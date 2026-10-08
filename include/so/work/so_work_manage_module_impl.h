// SHADOW of BrawlHeaders/so/work/so_work_manage_module_impl.h: identical except for the FT_MODULE_BUILDER-guarded declarations
// (constructors/destructors of sora_melee classes that fighter module builders call). Built only for fighter RELs.
#pragma once

#include <StaticAssert.h>
#include <so/so_lock.h>
#include <so/so_null.h>
#include <so/work/so_general_work_simple.h>
#include <so/event/so_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <types.h>

class soWorkManageModule : public soNullable {
public:
    virtual ~soWorkManageModule();
    virtual void activate();
    virtual void setWork(u32 index, soGeneralWorkAbstract* generalWork);
    virtual int getInt(u32 index);
    virtual void setInt(int value, u32 index);
    virtual void rndInt(int minValue, int maxValue, u32 index);
    virtual void incInt(u32 index);
    virtual void decInt(u32 index);
    virtual void addInt(int addValue, u32 index);
    virtual void subInt(int subtractValue, u32 index);
    virtual u32 countDownInt(u32 index, int threshold);
    virtual float getFloat(u32 index);
    virtual void setFloat(float value, u32 index);
    virtual void rndFloat(float minValue, float maxValue, u32 index);
    virtual void addFloat(float addValue, u32 index);
    virtual void subFloat(float subtractValue, u32 index);
    virtual bool isFlag(u32 index);
    virtual void onFlag(u32 index);
    virtual void offFlag(u32 index);
    virtual void setFlag(bool on, u32 index);
    virtual u32 turnOffFlag(u32 index);
    virtual void clearAll(u32 index);
    virtual void* getParamAccesser();
};
static_assert(sizeof(soWorkManageModule) == 8, "Class is wrong size!");

class soWorkManageModuleImpl : public soWorkManageModule, public soLockable, public soAnimCmdEventObserver {
#ifdef FT_MODULE_BUILDER
public:
    soWorkManageModuleImpl(soModuleAccesser* acc, void* paramAccesser);
private:
#endif

public:
    // The module owns three general works selected by the top nibble of a work variable ID (0x1... = LA, 0x2... = RA in
    // the BrawlRE variable lists), followed by the param accesser handed out by getParamAccesser(). (The BrawlHeaders
    // original models two work slots between spacers, which cannot hold the third work.)
    soGeneralWorkAbstract* m_generalWorks[3]; // 0x1c
    void* m_paramAccesser; // 0x28
    u32 m_unk2C; // 0x2c

    virtual ~soWorkManageModuleImpl();
    virtual void activate();
    virtual void setWork(u32 index, soGeneralWorkAbstract* generalWork);
    virtual int getInt(u32 index);
    virtual void setInt(int value, u32 index);
    virtual void rndInt(int minValue, int maxValue, u32 index);
    virtual void incInt(u32 index);
    virtual void decInt(u32 index);
    virtual void addInt(int addValue, u32 index);
    virtual void subInt(int subtractValue, u32 index);
    virtual u32 countDownInt(u32 index, int threshold);
    virtual float getFloat(u32 index);
    virtual void setFloat(float value, u32 index);
    virtual void rndFloat(float minValue, float maxValue, u32 index);
    virtual void addFloat(float addValue, u32 index);
    virtual void subFloat(float subtractValue, u32 index);
    virtual bool isFlag(u32 index);
    virtual void onFlag(u32 index);
    virtual void offFlag(u32 index);
    virtual void setFlag(bool on, u32 index);
    virtual u32 turnOffFlag(u32 index);
    virtual void clearAll(u32 index);
    virtual void* getParamAccesser();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);

#ifdef FT_MODULE_BUILDER
    char m_unkPad[4]; // HYPOTHESIS: sizeof(soWorkManageModuleImpl) is 0x34 in the REL builder
#endif
};
#ifdef FT_MODULE_BUILDER
static_assert(sizeof(soWorkManageModuleImpl) == 52, "Class is wrong size!");
#else
static_assert(sizeof(soWorkManageModuleImpl) == 48, "Class is wrong size!");
#endif
