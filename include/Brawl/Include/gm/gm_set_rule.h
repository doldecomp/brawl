#pragma once

#include <StaticAssert.h>
#include <gm/gm_result_info.h>
#include <types.h>

struct gmSetRule {
    char _0[0x2];
    u8 _1 : 5;
    GameRule m_rule : 3;
    u8 m_timeMinutes;
    u8 m_stockCount;
    u8 m_handicap;
    u8 m_damageRatio; // Multiplied by 10
    u8 m_stageChoice;
    u8 m_stockTimeMinutes;
    u8 m_isTeamAttack;
    u8 m_allowPause;
    u8 m_showScoreDisplay;
    u8 m_showDamageGauge;
    char _13[11];
    u8 m_spMeleeSetting1; // 0x18
    u8 m_spMeleeSetting2; // 0x19
    u8 m_spMeleeSetting3; // 0x1A
    u8 m_spMeleeSetting4; // 0x1B
    u8 m_spMeleeSetting5; // 0x1C
    u8 m_spMeleeSetting6; // 0x1D
    u8 m_spMeleeSetting7; // 0x1E
    u8 m_spMeleeSetting8; // 0x1F
    char _32[0x68];       // 0x20
};
static_assert(sizeof(gmSetRule) == 0x88, "Class is wrong size!");
