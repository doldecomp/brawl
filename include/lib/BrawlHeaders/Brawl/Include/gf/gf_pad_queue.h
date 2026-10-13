#pragma once

#include <StaticAssert.h>
#include <gf/gf_pad_status.h>
#include <types.h>

// A circular queue of arrays of NCols gfPadStatus objects
// with a capacity of NRows-1
class gfPadStatusQueue {
    static const s32 NRows = 4;
    static const s32 NCols = 8;

    // Note: m_front and m_back are row selectors
    u16 m_front;
    u16 m_back;
    gfPadStatus m_padStats[NRows][NCols];

public:
    // BUG(?): This only calls init() on the left half of the m_padStats table
    gfPadStatusQueue();
    // NOTE: This method does not clear the queue fully; it leaves the
    // most recently pushed element. If the queue is already empty, however,
    // then it's a no-op
    void clear();
    void push(const gfPadStatus padStatus[NCols]);
    bool pop(gfPadStatus output[NCols]);
};
static_assert(sizeof(gfPadStatusQueue) == 0x804, "Class is the wrong size!");
