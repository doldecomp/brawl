#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emKiller : public Enemy {
    u8 unk5310[0x734];
public:
    emKiller(u32 p1, emCreate* create);
    virtual ~emKiller();
    // TODO: emKiller virtual functions
};
static_assert(sizeof(emKiller) == 0x5a44, "Class is wrong size!");

