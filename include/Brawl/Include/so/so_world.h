#pragma once

#include <StaticAssert.h>
#include <types.h>

class soWorld {
public:
    float m_gravityUp;
    float m_gravityDown;
    float m_8;
    u8 m_12;
    u8 m_13;
    char _14[2];
};
static_assert(sizeof(soWorld) == 0x10, "Class is wrong size!");

extern soWorld* g_soWorld;
