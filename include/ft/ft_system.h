#pragma once

// Local shadow of BrawlHeaders' ft/ft_system.h: the two common-resource words are public so the fighter manager
// constructor call in ftManager::create can read them.

#include <StaticAssert.h>
#include <types.h>

class ftSystem {
public:
    u32 unk0;
    u32 unk4;

    ftSystem() : unk0(0), unk4(0) { }
    ~ftSystem();
    void setCommonResourceData(u32 p1, u32 p2);
};
static_assert(sizeof(ftSystem) == 8, "Class is the wrong size!");

extern ftSystem g_ftSystem;
