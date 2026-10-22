#pragma once

#include <StaticAssert.h>
#include <gf/gf_thread.h>
#include <revolution/OS/OSMutex.h>

class sndInitThread : public gfThread {
    mutable OSMutex m_mutex;
    bool m_initDone;
    bool m_loadDone;
public:
    void run();
    bool isFinishInitialize() const;
    bool isFinishLoad() const;
};
static_assert(sizeof(sndInitThread) == 0x360, "Class is the wrong size!");
