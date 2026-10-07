#pragma once
// Shadows BrawlHeaders to name the shared game-2D scene group and its task helpers.

#include <StaticAssert.h>
#include <if/if_player.h>
#include <gm/gm_lib.h>
#include <types.h>

namespace nw4r { namespace g3d { class ScnGroup; class ScnObj; } }

class IfMngr;
extern IfMngr* g_IfMngr;
class IfMngr {
public:
    u8 unk0[0x14];
    nw4r::g3d::ScnGroup* m_game2DGroup;
    u8 unk18[0x2c];
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

    void addGame2DObj(nw4r::g3d::ScnObj* object);
    void removeGame2DObj(nw4r::g3d::ScnObj* object);

    inline static IfMngr* getInstance() { return g_IfMngr; }
};
static_assert(sizeof(IfMngr) == 200, "Class is wrong size!");
