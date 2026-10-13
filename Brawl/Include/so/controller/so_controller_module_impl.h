#pragma once

#include <StaticAssert.h>
#include <so/controller/so_controller_impl.h>
#include <so/event/so_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <types.h>

class soControllerModule {
public:
    virtual ~soControllerModule();
    virtual void activate();
    virtual void deactivate();
    virtual void resetButton();
    virtual void resetTrigger();
    virtual void resetMainStickX();
    virtual void setMainStickX(float);
    virtual void resetMainStickY();
    virtual void setMainStickY(float);
    virtual void resetMainStick();
    virtual void resetSubStickX();
    virtual void resetSubStickY();
    virtual void resetSubStick();
    virtual void update(Input*, bool);
    virtual void resetFlickX();
    virtual void resetFlickY();
    virtual float getStickX();
    virtual float getStickPrevX();
    virtual float getStickY();
    virtual float getStickPrevY();
    virtual float getStickAngle();
    virtual float getStickDir();
    virtual bool isStickSide();
    virtual u8 getFlickX();
    virtual s8 getFlickXDir();
    virtual u8 getFlickY();
    virtual s8 getFlickYDir();
    virtual u8 getFlickNoResetX();
    virtual u8 getFlickNoResetY();
    virtual u8 getFlickAfterX();
    virtual s8 getFlickAfterXDir();
    virtual u8 getFlickAfterY();
    virtual float getSubStickX();
    virtual float getSubStickPrevX();
    virtual float getSubStickY();
    virtual float getSubStickPrevY();
    virtual float getSubStickDir();
    virtual bool isSubStickSide();
    virtual ipPadButton getTrigger();
    virtual u8 getTriggerCount(u8 index);
    virtual u8 getTriggerCountPrev(u8 index);
    virtual ipPadButton getButton();
    virtual ipPadButton getRelease();
    virtual void setOff(bool);
    virtual void setPrev(s32);
    virtual void clearLog();
    virtual s32 getLogNum();
    virtual void setLogActive(bool);
    virtual void startClatter(float, float, float, u8, u8, u32 index, bool);
    virtual void setClatterTime(float clatterTime, u32 index);
    virtual void addClatterTime(float clatterTime, u32 index);
    virtual float getClatterTime(u32 index);
    virtual void endClatter(u32 index);
    virtual float getClatterThreshold();
    virtual soController* getController();
    virtual void setRumble(s32, s32, bool, s32);
    virtual void stopRumbleKind(s32, s32);
    virtual void stopRumble(bool);
    virtual void setRumbleAll(s32, s32, s32);
    virtual void stopRumbleAll(s32, s32);
    virtual void setReverseXFrame(s32, bool);
    virtual float getLr();
    virtual u8 getFlickBonus();
    virtual u8 getFlickBonusLr();
    virtual void resetFlickBonus();
    virtual void resetFlickBonusLr();
};
static_assert(sizeof(soControllerModule) == 4, "Class is wrong size!");

class soControllerModuleImpl : public soControllerModule, public soAnimCmdEventObserver {
    char _16[4];

public:
    virtual ~soControllerModuleImpl();
    virtual void activate();
    virtual void deactivate();

    virtual float getStickAngle();
    virtual float getStickDir();
    virtual bool isStickSide();

    virtual float getSubStickDir();
    virtual bool isSubStickSide();

    virtual void startClatter(float, float, float, u8, u8, u32 index, bool);
    virtual void setClatterTime(float clatterTime, u32 index);
    virtual void addClatterTime(float clatterTime, u32 index);
    virtual float getClatterTime(u32 index);
    virtual void endClatter(u32 index);

    virtual void setRumble(s32, s32, bool, s32);
    virtual void stopRumbleKind(s32, s32);
    virtual void stopRumble(bool);
    virtual void setRumbleAll(s32, s32, s32);
    virtual void stopRumbleAll(s32, s32);
    virtual void setReverseXFrame(s32, bool);
    virtual float getLr();
    virtual u8 getFlickBonus();
    virtual u8 getFlickBonusLr();
    virtual void resetFlickBonus();
    virtual void resetFlickBonusLr();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, s32 unk3);

    void updateClatter(soController* linkController);
};
static_assert(sizeof(soControllerModuleImpl) == 20, "Class is wrong size!");
