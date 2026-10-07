#pragma once

#include <StaticAssert.h>
#include <so/controller/so_controller_impl.h>
#include <so/event/so_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/so_array.h>
#include <types.h>

// HYPOTHESIS: layout/field meaning inferred from soControllerModuleImpl::startClatter and
// soControllerClatter::update. One entry per "clatter" (button mashing) slot.
#ifndef SO_CONTROLLER_CLATTER_DEFINED
#define SO_CONTROLLER_CLATTER_DEFINED
class soControllerClatter {
public:
    float m_time;       // 0x00
    float m_unk04;      // 0x04
    float m_unk08;      // 0x08
    u8 _0C;
    u8 m_unk0D;
    u8 m_unk0E;
    u8 m_unk0F;
    u8 m_unk10;
    u8 _11[3];

    void reset();
    void update(soController* controller, int pressed, float threshold);
    static int checkButton(soController* controller);
};
static_assert(sizeof(soControllerClatter) == 0x14, "Class is wrong size!");
#endif

class soControllerModule {
public:
    virtual ~soControllerModule() { }
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void resetButton() = 0;
    virtual void resetTrigger() = 0;
    virtual void resetMainStickX() = 0;
    virtual void setMainStickX(float) = 0;
    virtual void resetMainStickY() = 0;
    virtual void setMainStickY(float) = 0;
    virtual void resetMainStick() = 0;
    virtual void resetSubStickX() = 0;
    virtual void resetSubStickY() = 0;
    virtual void resetSubStick() = 0;
    virtual void update(Input*, bool) = 0;
    virtual void resetFlickX() = 0;
    virtual void resetFlickY() = 0;
    virtual float getStickX() = 0;
    virtual float getStickPrevX() = 0;
    virtual float getStickY() = 0;
    virtual float getStickPrevY() = 0;
    virtual float getStickAngle() = 0;
    virtual float getStickDir() = 0;
    virtual bool isStickSide() = 0;
    virtual u8 getFlickX() = 0;
    virtual s8 getFlickXDir() = 0;
    virtual u8 getFlickY() = 0;
    virtual s8 getFlickYDir() = 0;
    virtual u8 getFlickNoResetX() = 0;
    virtual u8 getFlickNoResetY() = 0;
    virtual u8 getFlickAfterX() = 0;
    virtual s8 getFlickAfterXDir() = 0;
    virtual u8 getFlickAfterY() = 0;
    virtual float getSubStickX() = 0;
    virtual float getSubStickPrevX() = 0;
    virtual float getSubStickY() = 0;
    virtual float getSubStickPrevY() = 0;
    virtual float getSubStickDir() = 0;
    virtual bool isSubStickSide() = 0;
    // Module implementations forward the controller's scalar trigger mask unchanged.
    virtual int getTrigger() = 0;
    virtual u8 getTriggerCount(u8 index) = 0;
    virtual u8 getTriggerCountPrev(u8 index) = 0;
    virtual ipPadButton getButton() = 0;
    virtual ipPadButton getRelease() = 0;
    virtual void setOff(bool) = 0;
    virtual void setPrev(s32) = 0;
    virtual void clearLog() = 0;
    virtual s32 getLogNum() = 0;
    virtual void setLogActive(bool) = 0;
    virtual void startClatter(float, float, float, u8, u8, u32 index, bool) = 0;
    virtual void setClatterTime(float clatterTime, u32 index) = 0;
    virtual void addClatterTime(float clatterTime, u32 index) = 0;
    virtual float getClatterTime(u32 index) = 0;
    virtual void endClatter(u32 index) = 0;
    virtual float getClatterThreshold(u32 index) = 0;
    virtual soController* getController() = 0;
    virtual void setRumble(s32, s32, bool, s32) = 0;
    virtual void stopRumbleKind(s32, s32) = 0;
    virtual void stopRumble(bool) = 0;
    virtual void setRumbleAll(s32, s32, s32) = 0;
    virtual void stopRumbleAll(s32, s32) = 0;
    virtual void setReverseXFrame(s32, bool) = 0;
    virtual float getLr() = 0;
    virtual u8 getFlickBonus() = 0;
    virtual u8 getFlickBonusLr() = 0;
    virtual void resetFlickBonus() = 0;
    virtual void resetFlickBonusLr() = 0;
};
static_assert(sizeof(soControllerModule) == 4, "Class is wrong size!");

class soControllerModuleImpl : public soControllerModule, public soAnimCmdEventObserver {
public:
    soArray<soControllerClatter>* m_clatters;

    soControllerModuleImpl(s16 manageID, int unk, soArray<soControllerClatter>* clatters);
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
