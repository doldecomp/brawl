#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emArman : public Enemy {
    u8 unk5310[0x3398];
public:
    emArman(u32 p1, emCreate* create);
    virtual ~emArman();
    // TODO: emArman virtual functions
};
static_assert(sizeof(emArman) == 0x86a8, "Class is wrong size!");

