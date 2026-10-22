#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emBombhead : public Enemy {
    u8 unk5310[0x2d10];
public:
    emBombhead(u32 p1, emCreate* create);
    virtual ~emBombhead();
    // TODO: emBombhead virtual functions
};
static_assert(sizeof(emBombhead) == 0x8020, "Class is wrong size!");



