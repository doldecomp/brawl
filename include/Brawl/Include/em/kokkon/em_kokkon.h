#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emKokkon : public Enemy {
    u8 unk5310[0x9d0];
public:
    emKokkon(u32 p1, emCreate* create);
    virtual ~emKokkon();
    // TODO: emKokkon virtual functions
};
static_assert(sizeof(emKokkon) == 0x5ce0, "Class is wrong size!");

