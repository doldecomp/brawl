#pragma force_active on

#include <ft/ft_log.h>

// Per-fighter log: match statistics plus the attack and pattern (staling) history.
ftLog::ftLog() {
    m_logDataAccesser.setup(&m_logData);
    m_logDataAccesser.reset();
}

ftLog::~ftLog() { }
