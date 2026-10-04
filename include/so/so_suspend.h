#pragma once

#include <StaticAssert.h>
#include <types.h>

// NOTE: shadows the BrawlHeaders copy to add the constructor that clears the flag.
class soSuspendable {
    bool m_isSuspend;
public:
    soSuspendable() { m_isSuspend = false; }
    bool isSuspend() const { return m_isSuspend; }

};
static_assert(sizeof(soSuspendable) == 1, "Class is wrong size!");
