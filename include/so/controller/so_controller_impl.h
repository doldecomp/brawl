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
    virtual ~soController() { }

    static u32 getButtonMask(PadButton);
};
static_assert(sizeof(soController) == 8, "Class is wrong size!");

class soControllerImpl : public soController {
public:
    class soControllerTriggerData {
    public:
        u8 m_countPrev;
        u8 m_count;
    };

    float m_mainStickX;          // 0x08
    float m_mainStickY;          // 0x0C
    float m_mainStickPrevX;      // 0x10
    float m_mainStickPrevY;      // 0x14
    float m_savedMainStickX;     // 0x18 HYPOTHESIS: snapshot taken when going "off"
    float m_savedMainStickY;     // 0x1C
    float m_subStickX;           // 0x20
    float m_subStickY;           // 0x24
    float m_subStickPrevX;       // 0x28
    float m_subStickPrevY;       // 0x2C
    float m_savedSubStickX;      // 0x30
    float m_savedSubStickY;      // 0x34
    float m_lr;                  // 0x38
    float m_lrPrev;              // 0x3C
    float m_savedLr;             // 0x40
    int m_button;                // 0x44
    int m_buttonPrev;            // 0x48
    int m_savedButton;           // 0x4C
    int m_trigger;               // 0x50
    int m_release;               // 0x54
    soControllerTriggerData m_triggerData[17]; // 0x58
    u8 m_flickX;                 // 0x7A
    s8 m_flickXDir;              // 0x7B
    u8 m_flickY;                 // 0x7C
    s8 m_flickYDir;              // 0x7D
    u8 m_flickNoResetX;          // 0x7E
    s8 m_flickNoResetXDir;       // 0x7F
    u8 m_flickNoResetY;          // 0x80
    s8 m_flickNoResetYDir;       // 0x81
    u8 m_flickAfterX;            // 0x82
    s8 m_flickAfterXDir;         // 0x83
    u8 m_flickAfterY;            // 0x84
    s8 m_flickAfterYDir;         // 0x85
    u8 m_flickBonus;             // 0x86
    u8 m_flickBonusLr;           // 0x87
    bool m_hasSaved;             // 0x88
    bool m_isOff;                // 0x89
    char _8A[2];

    soControllerImpl();
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
    virtual ~soControllerImpl();
};
static_assert(sizeof(soControllerImpl) == 140, "Class is wrong size!");

class soControllerNull : public soController {

};

extern soControllerNull g_soControllerNull;
