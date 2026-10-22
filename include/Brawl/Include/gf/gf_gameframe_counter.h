#pragma once

#include <StaticAssert.h>
#include <types.h>

class gfGameFrameCounter {
    u32 m_startFrame;
    u32 m_latestStopFrame;
    u32 m_stoppedFrames;
    static const u32 ResetState = 0xFFFFFFFF;

public:
    void reset();
    void start();
    void stop();
    u32 getCounter() const;
};
static_assert(sizeof(gfGameFrameCounter) == 0xC, "Class is the wrong size!");
