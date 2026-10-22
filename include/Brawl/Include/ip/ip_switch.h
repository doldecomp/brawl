#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <ip/ip_padrec.h>

// TODO: related to ipPadButton?
struct ipPadStatus {
    u16 m_button;
    s8 m_stickX;
    s8 m_stickY;
};

class ipSwitch {
public:
    char _0[24];
    ipKeyRecorder* m_keyRecorder;
    char _28[12];

    static ipSwitch* getInstance();
    bool getPadStatus(s32 p1, ipPadStatus& p2);
};
static_assert(sizeof(ipSwitch) == 0x28, "Class is wrong size!");

extern ipSwitch* g_ipSwitch;
