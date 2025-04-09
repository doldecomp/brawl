#include <gf/gf_gameframe_counter.h>
#include <gm/gm_global.h>
#include <types.h>

void gfGameFrameCounter::reset() {
    m_startFrame = ResetState;
    m_latestStopFrame = 0;
    m_stoppedFrames = 0;
}

void gfGameFrameCounter::start() {
    if (m_startFrame == ResetState) {
        m_startFrame = g_GameGlobal->getGameFrame();
    } else {
        u32 now = g_GameGlobal->getGameFrame();
        m_stoppedFrames += (now - m_latestStopFrame);
        m_latestStopFrame = 0;
    }
}

void gfGameFrameCounter::stop() {
    m_latestStopFrame = g_GameGlobal->getGameFrame();
}

u32 gfGameFrameCounter::getCounter() const {
    u32 now = g_GameGlobal->getGameFrame();
    if (m_latestStopFrame) {
        return m_latestStopFrame - m_startFrame - m_stoppedFrames;
    }
    return now - m_startFrame - m_stoppedFrames;
}
