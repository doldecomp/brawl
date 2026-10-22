#pragma once

#include <StaticAssert.h>
#include <types.h>

class soSuspendable {
    u8 m_isSuspend : 1;
public:
    bool isSuspend() const { return m_isSuspend; }

};
static_assert(sizeof(soSuspendable) == 1, "Class is wrong size!");
