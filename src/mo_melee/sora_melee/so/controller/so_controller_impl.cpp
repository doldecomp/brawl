#include <so/controller/so_controller_impl.h>
#include <mt/mt_common.h>
#include <types.h>

// HYPOTHESIS: the three 0.25f values at the start of this unit's .rodata are unused
// (symbol name taken from the earlier link_ref placement).
namespace so_controller_module_link_ref {
    extern const float unused_floats[] = { 0.25f, 0.25f, 0.25f };
}

static const u32 s_buttonMasks[17] = {
    0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000008, 0x00000020, 0x00000400,
    0x00001000, 0x00000800, 0x00002000, 0x00004000, 0x00000040, 0x00000080, 0x000000C0,
    0x00000010, 0x00000100, 0x00008000,
};

soControllerImpl::soControllerImpl() {
    m_hasSaved = false;
    m_isOff = false;
    resetButton();
    m_savedButton = 0;
    m_savedLr = 0.0f;
    resetMainStick();
    m_savedMainStickY = 0.0f;
    m_savedMainStickX = 0.0f;
    resetSubStick();
    m_savedSubStickY = 0.0f;
    m_savedSubStickX = 0.0f;
    resetFlick();
}

soControllerImpl::~soControllerImpl() { }

void soControllerImpl::resetFlickX() {
    m_flickX = 0xFE;
    m_flickXDir = 0;
}

void soControllerImpl::resetFlickY() {
    m_flickY = 0xFE;
    m_flickYDir = 0;
}

void soControllerImpl::resetFlickBonus() {
    m_flickBonus = 0xFE;
}

void soControllerImpl::resetFlickBonusLr() {
    m_flickBonusLr = 0xFE;
}

void soControllerImpl::resetFlick() {
    resetFlickX();
    resetFlickY();
    m_flickNoResetY = 0xFE;
    m_flickNoResetX = 0xFE;
    m_flickNoResetYDir = 0;
    m_flickNoResetXDir = 0;
    m_flickAfterY = 0xFE;
    m_flickAfterX = 0xFE;
    m_flickAfterYDir = 0;
    m_flickAfterXDir = 0;
}

void soControllerImpl::resetButton() {
    m_release = 0;
    m_buttonPrev = 0;
    m_button = 0;
    m_lrPrev = 0.0f;
    m_lr = 0.0f;
}

void soControllerImpl::resetTrigger() {
    m_trigger = 0;
    for (int i = 0; i < 17; i++) {
        m_triggerData[i].m_countPrev = 0xFE;
        m_triggerData[i].m_count = 0xFE;
    }
}

void soControllerImpl::resetMainStick() {
    resetMainStickX();
    resetMainStickY();
}

void soControllerImpl::resetMainStickX() {
    m_mainStickPrevX = 0.0f;
    m_mainStickX = 0.0f;
}

void soControllerImpl::resetMainStickY() {
    m_mainStickPrevY = 0.0f;
    m_mainStickY = 0.0f;
}

void soControllerImpl::resetSubStick() {
    resetSubStickX();
    resetSubStickY();
}

void soControllerImpl::resetSubStickX() {
    m_subStickPrevX = 0.0f;
    m_subStickX = 0.0f;
}

void soControllerImpl::resetSubStickY() {
    m_subStickPrevY = 0.0f;
    m_subStickY = 0.0f;
}

void soControllerImpl::reset() {
    resetMainStick();
    resetSubStick();
    resetButton();
    resetTrigger();
    resetFlick();
}

void soControllerImpl::update(Input* input, bool accumulate) {
    if (!m_hasSaved) {
        m_mainStickPrevX = m_savedMainStickX;
        m_mainStickPrevY = m_savedMainStickY;
        m_subStickPrevX = m_savedSubStickX;
        m_subStickPrevY = m_savedSubStickY;
        m_lrPrev = m_savedLr;
        m_buttonPrev = m_savedButton;
        m_hasSaved = true;
    } else {
        m_mainStickPrevX = m_mainStickX;
        m_mainStickPrevY = m_mainStickY;
        m_subStickPrevX = m_subStickX;
        m_subStickPrevY = m_subStickY;
        m_lrPrev = m_lr;
        m_buttonPrev = m_button;
    }

    input->update();
    *(Vec2f*) &m_mainStickX = input->getStickMain();
    m_subStickX = 0.0f;
    m_subStickY = 0.0f;

    ipPadTrigger trigger;
    trigger = input->getTrigger();
    float l = trigger.m_l;
    float r = trigger.m_r;
    m_lr = (l > r) ? l : r;

    ipPadButton button = input->getButton();
    m_button = button.m_mask;
    if (button.m_mask & ipPadButton::MASK_GUARD) {
        m_button = button.m_mask | ipPadButton::MASK_GUARD;
        m_lr = 1.0f;
    } else if (m_lr != 0.0f) {
        m_button = button.m_mask | ipPadButton::MASK_GUARD;
    }

    int diff = m_buttonPrev ^ m_button;
    int pressed = m_button & diff;
    int released = m_buttonPrev & diff;
    if (accumulate == true) {
        m_trigger |= pressed;
        m_release |= released;
    } else {
        m_trigger = pressed;
        m_release = released;
    }

    if (++m_flickAfterX > 0xFE) {
        m_flickAfterX = 0xFE;
    }
    if (m_mainStickX >= 0.25f) {
        if (m_mainStickPrevX >= 0.25f) {
            if (++m_flickX > 0xFE) {
                m_flickX = 0xFE;
            }
            if (++m_flickNoResetX > 0xFE) {
                m_flickNoResetX = 0xFE;
            }
        } else {
            m_flickAfterX = 0;
            m_flickNoResetX = 0;
            m_flickX = 0;
            m_flickAfterXDir = 1;
            m_flickNoResetXDir = 1;
            m_flickXDir = 1;
        }
    } else if (m_mainStickX <= -0.25f) {
        if (m_mainStickPrevX <= -0.25f) {
            if (++m_flickX > 0xFE) {
                m_flickX = 0xFE;
            }
            if (++m_flickNoResetX > 0xFE) {
                m_flickNoResetX = 0xFE;
            }
        } else {
            m_flickAfterX = 0;
            m_flickNoResetX = 0;
            m_flickX = 0;
            m_flickAfterXDir = -1;
            m_flickNoResetXDir = -1;
            m_flickXDir = -1;
        }
    } else {
        resetFlickX();
        m_flickNoResetX = 0xFE;
    }

    if (++m_flickAfterY > 0xFE) {
        m_flickAfterY = 0xFE;
    }
    if (m_mainStickY >= 0.25f) {
        if (m_mainStickPrevY >= 0.25f) {
            if (++m_flickY > 0xFE) {
                m_flickY = 0xFE;
            }
            if (++m_flickNoResetY > 0xFE) {
                m_flickNoResetY = 0xFE;
            }
        } else {
            m_flickAfterY = 0;
            m_flickNoResetY = 0;
            m_flickY = 0;
            m_flickAfterYDir = 1;
            m_flickNoResetYDir = 1;
            m_flickYDir = 1;
        }
    } else if (m_mainStickY <= -0.25f) {
        if (m_mainStickPrevY <= -0.25f) {
            if (++m_flickY > 0xFE) {
                m_flickY = 0xFE;
            }
            if (++m_flickNoResetY > 0xFE) {
                m_flickNoResetY = 0xFE;
            }
        } else {
            m_flickAfterY = 0;
            m_flickNoResetY = 0;
            m_flickY = 0;
            m_flickAfterYDir = -1;
            m_flickNoResetYDir = -1;
            m_flickYDir = -1;
        }
    } else {
        resetFlickY();
        m_flickNoResetY = 0xFE;
    }

    float mag = mtSqrtf(m_mainStickX * m_mainStickX + m_mainStickY * m_mainStickY);
    float magPrev = mtSqrtf(m_mainStickPrevX * m_mainStickPrevX + m_mainStickPrevY * m_mainStickPrevY);
    float threshold = mtSqrtf(0.125f);
    if (mag >= threshold) {
        if (magPrev >= threshold) {
            if (++m_flickBonus > 0xFE) {
                m_flickBonus = 0xFE;
            }
        } else {
            m_flickBonus = 0;
        }
    } else {
        resetFlickBonus();
    }

    if (m_lr >= 0.25f) {
        if (m_lrPrev >= 0.25f) {
            if (++m_flickBonusLr > 0xFE) {
                m_flickBonusLr = 0xFE;
            }
        } else {
            m_flickBonusLr = 0;
        }
    } else {
        resetFlickBonusLr();
    }

    for (u8 i = 0; i < 17; i++) {
        if (m_trigger & getButtonMask((PadButton) i)) {
            m_triggerData[i].m_countPrev = m_triggerData[i].m_count;
            m_triggerData[i].m_count = 0;
        } else if (m_triggerData[i].m_count < 0xFE) {
            m_triggerData[i].m_count++;
        }
    }

    if (m_isOff == true) {
        m_savedMainStickX = m_mainStickX;
        m_savedMainStickY = m_mainStickY;
        m_savedSubStickX = m_subStickX;
        m_savedSubStickY = m_subStickY;
        m_savedLr = m_lr;
        m_savedButton = m_button;
        m_hasSaved = false;
        reset();
    }
}

u32 soController::getButtonMask(PadButton button) {
    if (button <= -1 || button >= 17) {
        return 0;
    }
    return s_buttonMasks[button];
}

u8 soControllerImpl::getFlickBonusLr() { return m_flickBonusLr; }
u8 soControllerImpl::getFlickBonus() { return m_flickBonus; }
float soControllerImpl::getLr() { return m_lr; }
int soControllerImpl::getRelease() { return m_release; }
int soControllerImpl::getButton() { return m_button; }
u8 soControllerImpl::getTriggerCountPrev(u8 index) { return m_triggerData[index].m_countPrev; }
u8 soControllerImpl::getTriggerCount(u8 index) { return m_triggerData[index].m_count; }
int soControllerImpl::getTrigger() { return m_trigger; }
float soControllerImpl::getSubStickPrevY() { return m_subStickPrevY; }
float soControllerImpl::getSubStickY() { return m_subStickY; }
float soControllerImpl::getSubStickPrevX() { return m_subStickPrevX; }
float soControllerImpl::getSubStickX() { return m_subStickX; }
u8 soControllerImpl::getFlickAfterY() { return m_flickAfterY; }
s8 soControllerImpl::getFlickAfterXDir() { s32 v = m_flickAfterXDir; return v; }
u8 soControllerImpl::getFlickAfterX() { return m_flickAfterX; }
u8 soControllerImpl::getFlickNoResetY() { return m_flickNoResetY; }
u8 soControllerImpl::getFlickNoResetX() { return m_flickNoResetX; }
s8 soControllerImpl::getFlickYDir() { s32 v = m_flickYDir; return v; }
u8 soControllerImpl::getFlickY() { return m_flickY; }
s8 soControllerImpl::getFlickXDir() { s32 v = m_flickXDir; return v; }
u8 soControllerImpl::getFlickX() { return m_flickX; }
float soControllerImpl::getStickPrevY() { return m_mainStickPrevY; }
float soControllerImpl::getStickY() { return m_mainStickY; }
float soControllerImpl::getStickPrevX() { return m_mainStickPrevX; }
float soControllerImpl::getStickX() { return m_mainStickX; }
void soControllerImpl::setOff(bool off) { m_isOff = off; }
void soControllerImpl::setMainStickY(float y) { m_mainStickY = y; }
void soControllerImpl::setMainStickX(float x) { m_mainStickX = x; }
