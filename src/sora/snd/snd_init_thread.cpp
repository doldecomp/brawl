#include <gf/gf_thread.h>
#include <revolution/OS/OSMutex.h>
#include <revolution/OS/OSThread.h>
#include <snd/snd_init_thread.h>
#include <snd/snd_system.h>

void sndInitThread::run() {
    sndSystem* sndSys = g_sndSystem;
    bool passed = sndSys->loadArchiveHeader();
    if (passed) {
        passed = sndSys->setupBuffers();
    }
    OSLockMutex(&m_mutex);
    m_initDone = true;
    OSUnlockMutex(&m_mutex);
    if (passed) {
        sndSys->loadCommon();
    }
    if (passed) {
        OSLockMutex(&m_mutex);
        m_loadDone = true;
        OSUnlockMutex(&m_mutex);
    }
    OSExitThread(nullptr);
}

bool sndInitThread::isFinishInitialize() const {
    OSLockMutex(&m_mutex);
    bool ret = m_initDone;
    OSUnlockMutex(&m_mutex);
    return ret;
}

bool sndInitThread::isFinishLoad() const {
    OSLockMutex(&m_mutex);
    bool ret = m_loadDone;
    OSUnlockMutex(&m_mutex);
    return ret;
}
