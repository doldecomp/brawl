#pragma once

#include <types.h>
#include <StaticAssert.h>

class soColorFlash {
public:
    char _0x0[0x34];
    bool m_isEnable;
    char _0x35[0x3];

    virtual ~soColorFlash();
    virtual void reset();
};
static_assert(sizeof(soColorFlash) == 0x3C, "Class is the wrong size!");
