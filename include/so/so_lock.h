#pragma once

#include <StaticAssert.h>
#include <types.h>

// NOTE: shadows the BrawlHeaders copy to add the lock counter accessors used by the status module.
class soLockable {
    s32 m_unk0;
    s32 m_lockCount;
public:
    void lock() { m_lockCount++; }
    void unlock() {
        if (m_lockCount > 0) {
            m_lockCount--;
        }
    }
};
static_assert(sizeof(soLockable) == 8, "Class is wrong size!");
