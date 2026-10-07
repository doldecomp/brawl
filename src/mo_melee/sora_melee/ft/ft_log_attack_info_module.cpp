#pragma force_active on

#include <ft/ft_log.h>

// History of the attacks a fighter has been hit by or has performed.
ftLogAttackInfoModule::ftLogAttackInfoModule() { }

ftLogAttackInfoModule::~ftLogAttackInfoModule() { }

// Appends the attack, dropping the oldest entry when the history is full.
void ftLogAttackInfoModule::addAttackInfo(const soLogAttackInfo& info) {
    if (m_logAttackInfoArrayVector.isFull() == true)
        m_logAttackInfoArrayVector.shift();
    m_logAttackInfoArrayVector.push(info);
}
