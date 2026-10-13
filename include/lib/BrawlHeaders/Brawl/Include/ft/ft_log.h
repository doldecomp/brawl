#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <ft/ft_log_data_accesser.h>
#include <ft/ft_trick_log.h>
#include <ft/ft_combo_log.h>
#include <ft/ft_kill_log.h>
#include <ft/ft_item_log.h>
#include <ft/ft_bombhei_log.h>
#include <ft/ft_log_attack_info_module.h>
#include <ft/ft_pattern_log.h>


struct ftLogActionInfo {
    char _[0x8];
};
static_assert(sizeof(ftLogActionInfo) == 0x8, "Class is wrong size!");

class ftLog {
    ftLogData m_logData;
public:
    ftLogDataAccesser m_logDataAccesser;
    ftTrickLog m_trickLog;
    ftComboLog m_comboLog;
    ftKillLog m_killLog;
    ftItemLog m_itemLog;
    ftBombheiLog m_bombheiLog;
    ftLogActionInfo m_logActionInfo;
    ftLogAttackInfoModule m_logAttackInfoModule;
    ftLogPatternModule m_logPatternModule;

    ftLog();
    ~ftLog();
};
static_assert(sizeof(ftLog) == 0x50C, "Class is wrong size!");
