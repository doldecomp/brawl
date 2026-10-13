#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>

class gfKeepFrameBuffer {
    bool m_isActive : 1;
    bool m_needsUpdate : 1;
public:
    void endKeepScreen();
    void startKeepScreen();
    void render();
    void update();
};
static_assert(sizeof(gfKeepFrameBuffer) == 1, "Class is the wrong size!");
