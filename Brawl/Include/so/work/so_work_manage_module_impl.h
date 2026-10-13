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
    virtual bool turnOffFlag(u32 index);
    virtual void clearAll(u32 index);
    virtual void* getParamAccesser();
};
static_assert(sizeof(soWorkManageModule) == 8, "Class is wrong size!");

class soWorkManageModuleImpl : public soWorkManageModule, public soLockable, public soAnimCmdEventObserver {

public:
    char _spacer[4];
    soGeneralWorkAbstract* m_generalWorks[2];
    char _spacer2[8];

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
    virtual bool turnOffFlag(u32 index);
    virtual void clearAll(u32 index);
    virtual void* getParamAccesser();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
};
static_assert(sizeof(soWorkManageModuleImpl) == 48, "Class is wrong size!");
