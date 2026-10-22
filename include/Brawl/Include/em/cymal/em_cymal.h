#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emCymal : public Enemy {
    u8 unk5310[0x5a8];
public:
    emCymal(u32 p1, emCreate* create);
    virtual ~emCymal();
    // TODO: emCymal virtual functions
};
static_assert(sizeof(emCymal) == 0x58b8, "Class is wrong size!");

