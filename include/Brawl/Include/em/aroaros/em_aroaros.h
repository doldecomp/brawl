#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emAroaros : public Enemy {
    u8 unk5310[0xa6c];
public:
    emAroaros(u32 p1, emCreate* create);
    virtual ~emAroaros();
    // TODO: emAroaros virtual functions
};
static_assert(sizeof(emAroaros) == 0x5d7c, "Class is wrong size!");


