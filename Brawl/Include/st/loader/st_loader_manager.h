#pragma once

#include <StaticAssert.h>
#include <st/loader/st_loader_player.h>
#include <gm/gm_lib.h>
#include <types.h>

class stLoaderManager {
public:
    stLoaderPlayer* m_loaderPlayers[MAX_PLAYERS];
    void* m_loaderStage;
    void* m_loaderStageAlt;
    void* m_loaderStageSe;
    void* m_loaderPokemonSe;
    void* m_loaderInfo;
    void* m_loaderSandbag;
    void* m_loaderStageAdvCommon;
    char _0x38[0x1C];
};

extern stLoaderManager* g_stLoaderManager;