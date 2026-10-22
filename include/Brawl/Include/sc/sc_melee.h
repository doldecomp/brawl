#pragma once

#include <StaticAssert.h>
#include <gm/gm_lib.h>
#include <gf/gf_scene.h>
#include <st/operator/st_operator_rule_targetbreak.h>
#include <st/operator/st_operator_rule_melee.h>
#include <st/operator/st_operator_drop_item.h>
#include <st/operator/st_operator_info.h>

#include <types.h>

class scMelee : public gfScene {
public:
    void* m_loaderPlayers[MAX_PLAYERS];
    void* m_loaderStage;
    char _40[12];
    void* m_loaderStageStarFox;
    char _56[8];
    void* m_operatorBgm;
    void* m_operatorAppearanceFighter;
    void* m_operatorReadyGo;
    void* m_operatorReadyGoSuddenDeath;
    stOperatorDropItemMelee* m_operatorDropItem;
    stOperatorRule* m_operatorRuleGameMode;
    stOperatorRuleMelee* m_operatorRuleMelee;
    void* m_operatorNoContest;
    void* m_operatorNetwork;
    void* m_operatorController;
    stOperatorInfo* m_operatorInfo;
    void* m_operatorFighterRebirths[MAX_PLAYERS];
    void* m_operatorFighterChange;
    void* m_operatorDefeatBoss;
    void* m_operatorEndProduction;
    void* m_operatorAppearanceHelper;
    char _152[4];
    void* m_operatorDebugIntrusions[2];
    void* m_operatorDebugFighterReset;
    void* m_operatorDebugStagePause;
    void* m_eventRule;
    char _176[36];
    int m_endNum;
    char _216[12];
    GameRule m_gameRule;
    char _232[24];

    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual ~scMelee();
    virtual int getEndNum();
};
static_assert(sizeof(scMelee) == 256, "Class is wrong size!");
