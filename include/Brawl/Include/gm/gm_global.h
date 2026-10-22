#pragma once

#include <StaticAssert.h>
#include <gm/gm_global_corps.h>
#include <gm/gm_global_mode_melee.h>
#include <gm/gm_global_record.h>
#include <gm/gm_result_info.h>
#include <gm/gm_sel_char_data.h>
#include <gm/gm_sel_stage_data.h>
#include <gm/gm_set_rule.h>
#include <gm/gm_tournament_data.h>
#include <gm/gm_stage_data.h>
#include <gm/gm_stage_edit_data.h>
#include <types.h>

class GameGlobal {
public:
    /* data */
    gmAppData* m_appData;               // 0x00
    char _0[0x4];                       // 0x04
    gmGlobalModeMelee* m_modeMelee;     // 0x08
    char _1[0x04];                      // 0x0C
    gmSelCharData* m_selCharData;       // 0x10
    gmSelStageData* m_selStageData;     // 0x14
    gmResultInfo* m_resultInfo;         // 0x18
    gmSetRule* m_setRule;               // 0x1C
    char _3[0x04];                      // 0x20
    gmGlobalRecord* m_record;         // 0x24
    gmGlobalRecord::NameData* m_nameRecords;         // 0x28
    gmTournamentData* m_tournamentData; // 0x2C
    gmAdvData* m_advData;           // 0x30
    nteGlobalData* m_nteData;           // 0x34
    char _4[0x04];                      // 0x38
    gmGlobalCorps* m_corps;             // 0x3C
    gmStageEditData* m_stageEditData;   // 0x40
    gmStageData* m_stageData;           // 0x44
    char _6[0x8];                       // 0x48

    gmGlobalRecord::MenuData* getGlobalRecordMenuDatap();
    float getGameFrame() const;
    void updateGameFrame();
    u32 getSlowRate() const;
    void setSlowRate(u8 rate);

    static int getLanguage();
    static GameGlobal* getInstance();
};
static_assert(sizeof(GameGlobal) == 0x50, "Class is wrong size!");

extern GameGlobal* g_GameGlobal;
