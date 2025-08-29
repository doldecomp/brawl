#include <gf/gf_pad_system.h>
#include <ip/input.h>
#include <ip/ip_padconfig.h>
#include <ip/ip_human.h>
#include <ip/ip_switch.h>
#include <mt/mt_vector.h>
#include <types.h>

IpHuman::IpHuman(u32 contNo) {
    m_contNo = contNo;
    m_rumbleEnabled = true;
    m_stickMain.m_y = 0.0f;
    m_stickMain.m_x = 0.0f;
    m_stickSub.m_y = 0.0f;
    m_stickSub.m_x = 0.0f;
    m_button.m_mask = 0;
    m_trigger.m_r = 0.0f;
    m_trigger.m_l = 0.0f;
}

IpHuman::~IpHuman() { }

static void clampStick(Vec2f& stk) {
    stk.m_x *= 0.0125f;
    stk.m_y *= 0.0125f;
    if (stk.m_x > 1.0f) {
        stk.m_x = 1.0f;
    } else if (stk.m_x < -1.0f) {
        stk.m_x = -1.0f;
    }

    if (stk.m_y > 1.0f) {
        stk.m_y = 1.0f;
    } else if (stk.m_y < -1.0f) {
        stk.m_y = -1.0f;
    }

    if (float(__fabs(stk.m_x)) <= 0.28f) {
        stk.m_x = 0.0f;
    }
    if (float(__fabs(stk.m_y)) <= 0.28f) {
        stk.m_y = 0.0f;
    }
}

void IpHuman::update() {
    ipPadStatus padStatus;
    bool isPlayer = false;
    s32 playerNo = m_contNo;
    if (playerNo >= 0) {
        playerNo = ipPadConfig::getInstance()->getPlayerNo(playerNo);
        if (playerNo >= 0) {
            isPlayer = true;
            ipSwitch::getInstance()->getPadStatus(playerNo, padStatus);
        }
    }

    if (isPlayer) {
        Vec2f stickVal;
        stickVal.m_y = padStatus.m_stickY;
        stickVal.m_x = padStatus.m_stickX;
        clampStick(stickVal);
        m_stickMain = stickVal;
        m_button.m_mask = padStatus.m_button;
    } else {
        m_button.m_mask = 0;
        m_stickMain = Vec2f(0.0f, 0.0f);
    }
}

bool IpHuman::isWinPoseIndicate() const {
    return getWinPose() != 0;
}

u32 IpHuman::getWinPose() const {
    return ((m_button.m_mask >> 6) & 1) | (-((m_button.m_mask >> 7) & 1) & 2);
}

void IpHuman::setEnableRumble(bool enable) {
    if (m_rumbleEnabled == true && enable == false) {
        stopRumble();
    }
    m_rumbleEnabled = enable;
}

#define CHECK_RUMBLE() (m_rumbleEnabled == true && m_contNo >= 0 && m_contNo < 8)

void IpHuman::setRumble(u32 p1, u32 p2, s32 p3, u8 p4) {
    if (CHECK_RUMBLE()) {
        g_gfPadSystem->m_gfRumble->lbSetRumble(m_contNo, p1, p2, p3, p4);
    }
}

void IpHuman::stopRumble() {
    if (CHECK_RUMBLE()) {
        g_gfPadSystem->m_gfRumble->lbStopRumble(m_contNo);
    }
}

void IpHuman::removeRumble() {
    if (CHECK_RUMBLE()) {
        g_gfPadSystem->m_gfRumble->HSD_PadRumbleRemove(m_contNo);
    }
}

void IpHuman::removeRumbleId(s32 p1, s32 p2) {
    if (CHECK_RUMBLE()) {
        g_gfPadSystem->m_gfRumble->HSD_PadRumbleRemoveId(m_contNo, p1, p2);
    }
}

void IpHuman::removeRumbleMask(u32 p1) {
    if (CHECK_RUMBLE()) {
        g_gfPadSystem->m_gfRumble->HSD_PadRumbleRemoveMask(m_contNo, p1);
    }
}

s32 IpHuman::getContNo() const {
    return m_contNo;
}

ipPadTrigger IpHuman::getTrigger() const {
    return m_trigger;
}

ipPadButton IpHuman::getButton() const {
    return m_button;
}

Vec2f IpHuman::getStickSub() const {
    return m_stickSub;
}

Vec2f IpHuman::getStickMain() const {
    return m_stickMain;
}
