#pragma once

#include <StaticAssert.h>
#include <types.h>

class soEnable {
    u8 m_isEnable : 1;
public:
    bool isEnable() const { return m_isEnable; }
};
static_assert(sizeof(soEnable) == 1, "Class is wrong size!");
