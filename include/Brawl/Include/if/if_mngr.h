#pragma once

#include <StaticAssert.h>
#include <if/if_player.h>
#include <gm/gm_lib.h>
#include <types.h>

class IfMngr;
extern IfMngr* g_IfMngr;
class IfMngr {
public:
    char _0x0[0x44];
    void* m_ifCenter;
    char _0x48[4];
    IfPlayer* m_ifPlayers[MAX_PLAYERS];
    char _0x64[8];
    void* m_ifPhoto;
    void* m_ifMinigameHomerun;
    void* m_ifMinigameTraining;
    char _0x7C[16];
    void* m_ifWifiIntrMenu;
    char _0x90[4];
    void* m_ifAdvBoss;
    char _0x98[17];
    bool m_isPauseMenuActive;
    char _spacer2[30];

    inline static IfMngr* getInstance() { return g_IfMngr; }
};
static_assert(sizeof(IfMngr) == 200, "Class is wrong size!");

