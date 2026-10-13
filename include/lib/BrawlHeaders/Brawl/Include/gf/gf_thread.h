#pragma once

#include <StaticAssert.h>
#include <revolution/OS/OSThread.h>
#include <sr/sr_common.h>
#include <types.h>

class gfRunnable {
public:
    virtual void run() = 0;
};
static_assert(sizeof(gfRunnable) == 0x4, "Class is the wrong size!");

class gfThread : public gfRunnable {
protected:
    u8 unk4[0x4];
    OSThread m_thread;          // 0x8
    u32 m_stackSize;            // 0x320
    void* m_stackLow;           // 0x324
    void* m_stackHi;            // 0x328
    const char* m_name;
    u32 m_priority;             // 0x330
    u8 unk334[0x4];
    u16 m_flags;                // 0x338
    gfRunnable* m_startRoutine; // 0x33C
public:
    gfThread() {
        createThread(this, 0x1F, 0x1000, Heaps::Thread);
    }
    virtual void run() { }
    ~gfThread();
    void createThread(gfRunnable* startRoutine, u32 priority, u32 stackSize, Heaps::HeapType heap);
    static void* startThread(void* arg);
};
static_assert(sizeof(gfThread) == 0x340, "Class is the wrong size!");
