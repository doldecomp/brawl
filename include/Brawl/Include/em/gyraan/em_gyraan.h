#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emGyraan : public Enemy {
    u8 unk5310[0x4f3c];
public:
    emGyraan(u32 p1, emCreate* create);
    virtual ~emGyraan();
    // TODO: emGyraan virtual functions
};
static_assert(sizeof(emGyraan) == 0xa24c, "Class is wrong size!");
