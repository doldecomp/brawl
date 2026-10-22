#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emMetaridley : public Enemy {
    u8 unk5310[0x1b1c];
public:
    emMetaridley(u32 p1, emCreate* create);
    virtual ~emMetaridley();
    // TODO: emMetaridley virtual functions
};
static_assert(sizeof(emMetaridley) == 0x6e2c, "Class is wrong size!");

