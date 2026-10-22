#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <gm/gm_lib.h>

struct gmPlayerResultInfo {
    gmCharacterKind m_characterKind : 8;
    u8 m_state;
    s8 m_colorFileIdx;
    char _3[3];
    u8 m_teamNo;
    char _7[1];
    s16 m_hitPointMax;
    u8 m_startStockCount;
    char _11[1];
    s16 m_startDamage;
    u8 m_rank;
    char _15[1];
    u32 m_koCount;
    u32 m_deadCount;
    u16 m_suicideCount;
    u16 m_playerBeatCounts[MAX_PLAYERS];
    u32 m_coins;
    u32 m_pickupCoins;
    u32 m_lostCoins;
    char _26[548];
    int m_rankCount;
    char _604[80];
};
static_assert(sizeof(gmPlayerResultInfo) == 684, "Class is wrong size!");

class gmResultInfo {
public:
    enum DecisionKind {
        Decision_Timeup = 0x1,
        Decision_Win = 0x2,
        Decision_Team_Win = 0x3,
        Decision_Failure = 0x4,
        Decision_Complete = 0x5,
        Decision_Success = 0x6,
        Decision_Event_Success = 0x7,
        Decision_Event_Failure = 0x8,
        Decision_NoContest = 0x9,
    };

    char _0[1];
    GameRule m_gameRule : 8;
    bool m_isTeams;
    char _4[0xc];
    u8 m_numWinners;
    char _16[15];
    s8 m_winningPlayer;
    char _32[4];
    gmPlayerResultInfo m_playersResultInfo[MAX_PLAYERS];
    char _4824[0xa0];
    DecisionKind m_decisionKind : 8;
    char _0x1379[11];
    int m_framesElapsed;
};
static_assert(sizeof(gmResultInfo) == 0x1388, "Class is wrong size!");

namespace static_checks {

} // namespace static_checks
