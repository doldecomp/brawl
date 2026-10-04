#pragma once

#include <StaticAssert.h>
#include <types.h>

// NOTE: shadows the BrawlHeaders copy to add the setter used by fighter code.
class soEnable {
    u8 m_isEnable : 1;
public:
    bool isEnable() const { return m_isEnable; }
    void enable() { m_isEnable = true; }
    void disable() { m_isEnable = false; }
};
static_assert(sizeof(soEnable) == 1, "Class is wrong size!");
