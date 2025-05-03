#include <gf/gf_thread.h>
#include <gf/gf_heap_manager.h>
#include <revolution/OS/OSThread.h>
#include <sr/sr_common.h>
#include <types.h>

gfThread::~gfThread() {
    u32 discard;
    OSJoinThread(&m_thread, &discard);
    gfHeapManager::free(m_stackLow);
}

void gfThread::createThread(gfRunnable* startRoutine, u32 priority, u32 stackSize, Heaps::HeapType heap) {
    unk32C = 0;
    m_stackSize = stackSize;
    m_priority = priority;
    m_stackHi = nullptr;
    m_attach = 0;
    if (startRoutine) {
        m_startRoutine = startRoutine;
    } else {
        m_startRoutine = this;
    }
    void* stack = gfHeapManager::alloc(heap, stackSize);
    m_stackLow = stack;
    m_stackHi = static_cast<char*>(stack) + stackSize;
    OSCreateThread(&m_thread, startThread, this, m_stackHi, m_stackSize, m_priority, m_attach);
}

void* gfThread::startThread(void* arg) {
    static_cast<gfThread*>(arg)->m_startRoutine->run();
    return nullptr;
}
