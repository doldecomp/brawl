#include <cstring>
#include <gf/gf_pad_queue.h>
#include <gf/gf_pad_status.h>
#include <revolution/OS/OSInterrupt.h>
#include <types.h>

namespace {
// Only State::One is ever used
enum State {
    Zero = 0,
    One = 1,
    Two = 2
};
}

gfPadStatusQueue::gfPadStatusQueue() : m_front(0), m_back(0) {
    for (u32 i = 0; i < NRows; i++)
        for (u32 j = 0; j < NCols / 2; j++)
            m_padStats[i][j].init();
}

void gfPadStatusQueue::clear() {
    s32 diff = m_back - m_front;
    if (diff < 0)
        diff += NRows;
    u16 queueSize = diff;
    if (queueSize > 1) {
        BOOL intr = OSDisableInterrupts();
        // This is the current position of m_back; put m_front right behind it.
        // This effectively pops the queue until there is one element left
        s32 back = m_front + queueSize;
        m_front = (back - 1) % NRows;
        OSRestoreInterrupts(intr);
    }
}

void gfPadStatusQueue::push(const gfPadStatus padStatus[NCols]) {
    BOOL intr;
    State state = One;
    intr = OSDisableInterrupts();
    u16 next = ((m_back + 1) % NRows);
    if (m_front != next) {
        // The queue is not full; push back
        memcpy(m_padStats[m_back], padStatus, sizeof(m_padStats[0]));
        m_back = (m_back + 1) % NRows;
    } else {
        // The queue is full; overwrite the element in the back
        u32 back = ((m_back + (NRows - 1)) % NRows) & 0xFFFF;
        switch (state) {
            case Zero:
                break;
            case One:
                memcpy(m_padStats[back], padStatus, sizeof(m_padStats[0]));
                break;
            case Two:
                memcpy(m_padStats[back], padStatus, sizeof(m_padStats[0]));
                break;
        }
    }
    OSRestoreInterrupts(intr);
}

bool gfPadStatusQueue::pop(gfPadStatus output[NCols]) {
    BOOL intr = OSDisableInterrupts();
    if (m_front != m_back) {
        // The queue is non-empty; pop front
        memcpy(output, m_padStats[m_front], sizeof(m_padStats[0]));
        m_front = (m_front + 1) % NRows;
        OSRestoreInterrupts(intr);
        return true;
    }
    OSRestoreInterrupts(intr);
    return false;
}
