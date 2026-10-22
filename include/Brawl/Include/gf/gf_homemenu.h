#pragma once

#include <StaticAssert.h>
#include <types.h>

class gfHomeMenu {
public:
    bool setBan(u32 p1, u32 p2);
    void kill();
    void start();
};
// TODO size assertion

extern gfHomeMenu* g_gfHomeMenu;
