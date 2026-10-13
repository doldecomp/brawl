#pragma once

#include <StaticAssert.h>
#include <gm/gm_result_info.h>
#include <st/operator/st_operator_rule.h>
#include <types.h>

class stOperatorRuleMelee : public stOperatorRule {
public:
    gmResultInfo* m_resultInfo;
    char _144[2];
    u8 m_146;
    char _147[12];
    bool m_isStart;
    u32 m_remainingFrameTime;
    u32 m_framesElapsed;
    u32 m_frameCounter;
    char _0xAC[0x18];
    int m_numPlayers;
    u32 m_playersLastDeadSleepFrame[MAX_PLAYERS];
    u32 m_0x124[MAX_PLAYERS];
    int m_0x140[MAX_PLAYERS];
    int m_0x15C[MAX_PLAYERS];
    int m_0x178[MAX_PLAYERS];
    int m_playersRankPoint[MAX_PLAYERS];
    char _0x1B0[0xA4];
    DecisionKind m_decisionKind;
    char _0x258[4];

    virtual void processBegin();
    virtual ~stOperatorRuleMelee();
    virtual bool isEnd();
    virtual void startOperator();
    virtual void calcScore();
    virtual bool isSuddenDeath();
    virtual void adjustResultInfo();
    virtual void notifyEventKnockout(u32);
    virtual bool notifyEventDead(int entryId, u32 playerIndex, int);
    virtual void notifyEventStartStage();
    virtual void notifyEventSetupCorps();
    virtual void notifyEventBeat(u32 playerIndex1, u32 playerIndex2);
    virtual void networkWriteRanking();
    virtual void updateExtraInfo();
    virtual bool checkExtraRule();
    virtual void decisionExtraRule();
    virtual void calcHighScore();
    virtual bool getNextCorpsPutMemberCharaKind(u8*, u8*);
    virtual bool searchCorpsPutMember(u32, int, u32*, u32*, u8*);
    virtual void putCorpsPutMember(void*, u32 characterKind, u32 costumeId, u8, bool);
};
static_assert(sizeof(stOperatorRuleMelee) == 604, "Class is wrong size!");