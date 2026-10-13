#pragma once

#include <StaticAssert.h>
#include <types.h>

class ipKeyRecorder {
public:
    char _0[60];
    int m_pauseStatus;
    char _64[64];
};
static_assert(sizeof(ipKeyRecorder) == 0x80, "Class is wrong size!");
