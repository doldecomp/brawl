#include <ft/ft_common_data_accesser.h>
#include <ft/ft_log.h>
#include <ft/ft_manager.h>

// Per-fighter attack pattern queue used for "staling" (repeated attacks deal less damage).
// m_logAttackInfoArrayVector holds the most recent distinct attacks, newest first.

// HYPOTHESIS: ftDataCommon + 0x44 is the table of pattern multipliers. Entry 0 is the bonus for a fresh
// attack; entry i + 1 is the penalty applied for the queue slot i. The header does not name this field.
static inline float* getPatternMulTable(ftDataCommon* common) {
    return *(float**)((u8*)common + 0x44);
}

ftLogPatternModule::ftLogPatternModule() {
    _0x78 = 1;
}

ftLogPatternModule::~ftLogPatternModule() { }

void ftLogPatternModule::addAttackPattern(const soLogAttackInfo& info) {
    int size = m_logAttackInfoArrayVector.size();
    for (int i = 0; i < size; i++) {
        soLogAttackInfo& entry = m_logAttackInfoArrayVector.at(i);
        if (entry._4 == info._4 && entry._0 == info._0)
            return;
    }
    if (m_logAttackInfoArrayVector.isFull() == true)
        m_logAttackInfoArrayVector.pop();
    m_logAttackInfoArrayVector.unshift(info);
}

float ftLogPatternModule::getPowerMul(const soLogAttackInfo& info) {
    float mul = 1.0f;
    // NOTE: the flag is named "no one pattern offset" in the header, but staling is only computed when it is set.
    if (!g_ftManager->m_noOnePatternOffsett)
        return mul;

    ftDataCommon* common = g_ftCommonData.dataCommon;
    if (info._4 == 0 || m_logAttackInfoArrayVector.isEmpty() == true) {
        mul += getPatternMulTable(common)[0];
        return mul;
    }

    int size = m_logAttackInfoArrayVector.size();
    bool isFresh = true;
    const soArrayVector<soLogAttackInfo, 9>& queue = m_logAttackInfoArrayVector;
    for (int i = 0; i < size; i++) {
        const soLogAttackInfo& entry = queue.at(i);
        if (entry._4 == info._4 && entry._0 != info._0) {
            isFresh = false;
            mul -= getPatternMulTable(common)[i + 1];
        }
    }
    if (isFresh == true)
        mul += getPatternMulTable(common)[0];
    return mul;
}

void ftLogPatternModule::clearPattern() {
    m_logAttackInfoArrayVector.clear();
}

soLogAttackInfo::soLogAttackInfo() : _0(0), _4(0), _8(0) { }
