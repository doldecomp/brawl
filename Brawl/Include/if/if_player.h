#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <gm/gm_lib.h>

class IfPlayer {
public:
    bool m_0x0_0 : 1;
    bool m_scoreDisplay : 1;
    char _2[10];
    GameRule m_gameRule;
    char _10[318];
    u8 teamNo;
    char _2b0[1154];
    void updateStockCoin(u8 amount);
    void updateCoinScoreSub(u8 amount);
    void disappear();
    virtual ~IfPlayer();
};
static_assert(sizeof(IfPlayer) == 1496, "Class is wrong size!");