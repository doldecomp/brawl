#pragma once

#include <StaticAssert.h>
#include <types.h>

class ftSystem {
    u32 unk0;
    u32 unk4;
public:
    ftSystem() : unk0(0), unk4(0) { }
    ~ftSystem();
    void setCommonResourceData(u32 p1, u32 p2);
};
static_assert(sizeof(ftSystem) == 8, "Class is the wrong size!");

extern ftSystem g_ftSystem;
