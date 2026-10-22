#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emTaboo : public Enemy {
    u8 unk5310[0x2248];
public:
    emTaboo(u32 p1, emCreate* create);
    virtual ~emTaboo();
    // TODO: emTaboo virtual functions
};
static_assert(sizeof(emTaboo) == 0x7558, "Class is wrong size!");

