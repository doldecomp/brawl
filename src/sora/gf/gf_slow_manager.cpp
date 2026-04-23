#include <gf/gf_application.h>
#include <gf/gf_slow_manager.h>
#include <gm/gm_global.h>
#include <types.h>

static bool s_needsUpdate;
static u8 s_maxSlowRate = 1;
static gfSlowManager s_gfSlowManager;

void gfSlowManager::reset() {
    s_needsUpdate = false;
    for (u32 i = 0; i < NRequests; i++) {
        s_gfSlowManager.m_reqs[i].m_state = StateInactive;
        s_gfSlowManager.m_reqs[i].m_slowRate = 1;
    }
}

void gfSlowManager::update() {
    u8 maxRate = 1;
    for (u32 i = 0; i < NRequests; i++) {
        if (s_gfSlowManager.m_reqs[i].m_state) {
            u8 rate = s_gfSlowManager.m_reqs[i].m_slowRate;
            if (maxRate < rate)
                maxRate = rate;
        }
    }
    if (s_needsUpdate) {
        s_maxSlowRate = maxRate;
        g_GameGlobal->setSlowRate(maxRate);
        s_needsUpdate = false;
    }
    g_GameGlobal->updateGameFrame();
}

// NONMATCHING regswap
u32 gfSlowManager::requestSlow(u8 rate) {
    u8 res = 0xFF;
    SlowRequest* reqs = s_gfSlowManager.m_reqs;
    SlowRequest* curr;
    for (u8 i = 0; i < NRequests; i++) {
        curr = &reqs[i];
        if (curr->m_state == StateInactive) {
            res = i;
            s_needsUpdate = true;
            curr->m_state = StateActive;
            curr->m_slowRate = rate;
            break;
        }
    }
    return static_cast<u32>(res) << 24;
}

bool gfSlowManager::removeRequest(const u8& idx) {
    bool res = false;
    if (s_gfSlowManager.m_reqs[idx].m_state == StateActive) {
        s_gfSlowManager.m_reqs[idx].m_state = StateInactive;
        s_gfSlowManager.m_reqs[idx].m_slowRate = 1;
        res = true;
        s_needsUpdate = true;
    }
    return res;
}

u8 gfSlowManager::getSlowRate() {
    return g_GameGlobal->getSlowRate();
}

u8 gfSlowManager::getSlowRate(const u8& idx) {
    if (s_gfSlowManager.m_reqs[idx].m_state == StateActive)
        return s_gfSlowManager.m_reqs[idx].m_slowRate;
    return 1;
}

float gfSlowManager::getQuickRate() {
    return g_gfApplication->m_frameRate / 60.0f;
}

float gfSlowManager::getRealTimeRate() {
    u8 sRate = g_GameGlobal->getSlowRate();
    return gfSlowManager::getQuickRate() / sRate;
}
