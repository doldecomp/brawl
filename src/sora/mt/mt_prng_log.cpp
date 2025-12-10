#include <gm/gm_global.h>
#include <gf/gf_heap_manager.h>
#include <mt/mt_prng.h>
#include <types.h>

mtPrngLogManager g_mtPrngLogManager;

// A node in a PPC stack trace, referencing the caller's SP and LR
// UBFIX: ABI-specific
struct PPCFrameInfo {
    PPCFrameInfo* m_next;
    void* m_retaddr;

    bool isValid() const {
        return reinterpret_cast<u32>(this) != -1;
    }

    bool isInRange() const {
        return reinterpret_cast<u32>(this) & 0x80000000;
    }
};

mtPrngLog::mtPrngLog(u32 val, void* sp) {
    m_randVal = val;
    PPCFrameInfo* bt = static_cast<PPCFrameInfo*>(sp)->m_next;
    u32 i = 0;

    // Store a stack trace of up to 2 return addresses in m_backtrace
    if (bt && bt->isValid() && bt->isInRange()) {
        m_backtrace[i++] = bt->m_retaddr;
        bt = bt->m_next;
        if (bt && bt->isValid() && bt->isInRange()) {
            m_backtrace[i++] = bt->m_retaddr;
        }
    }

    for ( ; i < BacktraceLength; i++) {
        m_backtrace[i] = nullptr;
    }
    m_gameFrame = g_GameGlobal->getGameFrame();
}

mtPrngLogManager::~mtPrngLogManager() {
    if (m_logs && m_logs) {
        gfHeapManager::free(m_logs);
        m_logs = nullptr;
        m_len = 0;
        m_maxLen = 0;
    }
}

bool mtPrngLogManager::addLog(const mtPrngLog* log) {
    bool res = false;
    if (m_len < m_maxLen) {
        m_logs[m_len] = *log;
        res = true;
        m_len++;
    }
    return res;
}
