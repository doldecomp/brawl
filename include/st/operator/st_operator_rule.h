#pragma once

// Supersedes include/lib/BrawlHeaders/Brawl/Include/st/operator/st_operator_rule.h (shadows it via -I include).
// Adds exchangeGmCharacterKind2FigureId (sora_melee 0x24810C), which the BrawlHeaders submodule lacks. Keep in sync.

#include <StaticAssert.h>
#include <gm/gm_lib.h>
#include <st/operator/st_operator.h>
#include <types.h>

class stOperatorRule : public stOperator {
public:
    enum DecisionKind {
        Decision_Timeup = 0x0,
        Decision_Gameset = 0x1,
        Decision_Complete = 0x2,
        Decision_Failure = 0x3,
        Decision_Success = 0x4
    };

    // HYPOTHESIS: maps a fighter kind to the id of its figure (trophy); the result is used as the figure item's variation.
    static u32 exchangeGmCharacterKind2FigureId(gmCharacterKind kind);

    void* m_operatorBgm;
    void* m_operatorNetwork;
    void* m_operatorController;
    char _20[32];
    bool m_isGameSet;
    char _53[87];

    virtual void processBegin();
    virtual ~stOperatorRule();
    virtual void setOperatorBgm(void*);
    virtual void setOperatorNetwork(void*);
    virtual void setOperatorController(void*);
    virtual bool isGameSet();
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
    virtual void notifyEventYoshiEgg();
    virtual void notifyEventPikminBloom();
    virtual void nortifyNetworkOtherNodeExit();
    virtual void networkWriteRanking();
    virtual void setOpAppearanceHelper(void*);
};
static_assert(sizeof(stOperatorRule) == 204, "Class is wrong size!");
