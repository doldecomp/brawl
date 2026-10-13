#pragma once

#include <StaticAssert.h>
#include <st/operator/st_operator_rule_melee.h>
#include <types.h>

class stOperatorRuleTargetBreak : public stOperatorRuleMelee {
public:
    int m_damageBonus;
    int m_timeBonus;
    int m_leftTime;
    int m_brokenTargetCount;
    u32 m_level;
    u8 m_numPlayers;
    char _0x271[23];
    bool m_isComplete;
    char _0x289[3];

    virtual ~stOperatorRuleTargetBreak();
    virtual void calcScore();
    virtual bool isSuddenDeath();
    virtual bool notifyEventDead(int entryId, u32 playerIndex, int);
    virtual void notifyEventStartStage();
    virtual void updateExtraInfo();
    virtual bool checkExtraRule();
    virtual void decisionExtraRule();
    virtual void calcHighScore();
};
static_assert(sizeof(stOperatorRuleTargetBreak) == 0x28c, "Class is wrong size!");