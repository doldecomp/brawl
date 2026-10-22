#pragma once

#include <StaticAssert.h>
#include <types.h>

class soActivatable {
public:
    soActivatable(bool active) : m_isActive(active) { }
    virtual ~soActivatable() { }

    bool m_isActive;
    void setActive(bool active) { m_isActive = active; }
};
static_assert(sizeof(soActivatable) == 8, "Class is the wrong size!");
