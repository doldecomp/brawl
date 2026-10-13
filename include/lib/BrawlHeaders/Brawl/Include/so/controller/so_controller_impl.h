#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <ip/input.h>
#include <types.h>

class soController : public soNullable {
public:
    enum PadButton {
        Pad_Button_Attack = 0x0,
        Pad_Button_Special = 0x1,
        Pad_Button_Jump = 0x2,
        Pad_Button_Guard = 0x3,
        Pad_Button_Guard_2 = 0x4,
        Pad_Button_Smash = 0x5,
        Pad_Button_Appeal_Hi = 0x6,
        Pad_Button_Appeal_Lw = 0x7,
        Pad_Button_Appeal_S = 0x8,
        Pad_Button_Appeal_S_L = 0x9,
        Pad_Button_Appeal_S_R = 0xA,
        Pad_Button_Dir_L = 0xB,
        Pad_Button_Dir_Hi = 0xC,
        Pad_Button_Dir_R = 0xD,
        Pad_Button_Stock_Share = 0xE,
        Pad_Button_CStick = 0xF,
        Pad_Button_Flick_Jump = 0x10,
    };

    virtual void resetFlick();
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
    virtual void reset();
    virtual void update(Input*, bool);
    virtual void resetFlickX();
    virtual void resetFlickY();
    virtual void setOff(bool);
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
    virtual int getTrigger();
    virtual u8 getTriggerCount(u8 index);
    virtual u8 getTriggerCountPrev(u8 index);
    virtual int getButton();
    virtual int getRelease();
    virtual float getLr();
    virtual u8 getFlickBonus();
    virtual u8 getFlickBonusLr();
    virtual void resetFlickBonus();
    virtual void resetFlickBonusLr();
    virtual ~soController();

    static u32 getButtonMask(PadButton);
};
static_assert(sizeof(soController) == 8, "Class is wrong size!");

class soControllerImpl : public soController {

    class soControllerTriggerData {
        u8 m_countPrev;
        u8 m_count;
    };

public:
    float m_mainStickX;
    float m_mainStickY;
    float m_mainStickPrevX;
    float m_mainStickPrevY;
    char _24[8];
    float m_subStickX;
    float m_subStickY;
    float m_subStickPrevX;
    float m_subStickPrevY;
    char _48[8];
    float m_lr;
    char _60[8];
    int m_button;
    int m_buttonPrev;
    char _76[4];
    int m_trigger;
    int m_release;
    soControllerTriggerData m_triggerData[2];
    char _92[30];
    u8 m_flickX;
    u8 m_flickXDir;
    u8 m_flickY;
    u8 m_flickYDir;
    u8 m_flickNoResetX;
    char _127;
    u8 m_flickNoResetY;
    char _129;
    u8 m_flickAfterX;
    u8 m_flickAfterXDir;
    u8 m_flickAfterY;
    char _133;
    u8 m_flickBonus;
    u8 m_flickBonusLr;
    bool _136;
    bool _isOff;
    char _138[2];

    virtual void resetFlick();
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
    virtual void reset();
    virtual void update(Input*, bool);
    virtual void resetFlickX();
    virtual void resetFlickY();
    virtual void setOff(bool);
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
    virtual int getTrigger();
    virtual u8 getTriggerCount();
    virtual u8 getTriggerCountPrev();
    virtual int getButton();
    virtual int getRelease();
    virtual float getLr();
    virtual u8 getFlickBonus();
    virtual u8 getFlickBonusLr();
    virtual void resetFlickBonus();
    virtual void resetFlickBonusLr();
    virtual ~soControllerImpl();
};
static_assert(sizeof(soControllerImpl) == 140, "Class is wrong size!");

class soControllerNull : public soController {

};

extern soControllerNull g_soControllerNull;
