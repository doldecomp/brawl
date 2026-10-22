#pragma once

#include <StaticAssert.h>
#include <gf/gf_callback.h>
#include <gf/gf_system_callback.h>
#include <types.h>

class gfShutdownManager {
public:
    bool unk0_b7 : 1;
    bool m_reset : 1;
    bool m_powerOff : 1;
    bool m_returnToWiiMenu : 1;
    bool unk0_b3 : 1;
    s32 unk0 : 8;
    gfCallBackList unk4;
    gfReturnStatusCallbackList unk8;
    bool unkC;
    bool unkD;

    // BUG(?): this ctor doesn't initialize unk0_b3
    gfShutdownManager() : unk0_b7(true), m_reset(false), m_powerOff(false),
                          m_returnToWiiMenu(false), unk0(0),
                          unk4(), unk8(), unkC(false), unkD(true) { }
    void initilize();
    static void ResetCallback();
    static void PowerOffCallback();
    void enterRestartProcess();
    void enterReturnToWiiMenuProcess();
    void update();
};
static_assert(sizeof(gfShutdownManager) == 0x10, "Class is the wrong size!");

extern gfShutdownManager g_gfShutdownManager;
