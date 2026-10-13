#pragma once

#include <StaticAssert.h>
#include <ip/input.h>
#include <so/so_module_accesser.h>
#include <so/controller/so_controller_module_impl.h>
#include <so/controller/so_controller_impl.h>
#include <types.h>

class soControllerModuleLinkRef : public soControllerModuleImpl {
    soModuleAccesser* m_moAccessor;
    soController* m_lkController;
public:
    virtual ~soControllerModuleLinkRef();
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
    virtual float getClatterThreshold();
    virtual soController* getController();
    virtual void setRumble(s32, s32, bool, s32);
    virtual void stopRumbleKind(s32, s32);
    virtual void stopRumble(bool);
    virtual void setRumbleAll(s32, s32, s32);
    virtual void stopRumbleAll(s32, s32);
    virtual float getLr();
    virtual u8 getFlickBonus();
    virtual u8 getFlickBonusLr();
    virtual void resetFlickBonus();
    virtual void resetFlickBonusLr();
};
static_assert(sizeof(soControllerModuleLinkRef) == 0x1C, "Class is wrong size!");
