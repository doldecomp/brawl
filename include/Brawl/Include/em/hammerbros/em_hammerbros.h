#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emHammerbros : public Enemy {
    u8 unk5310[0xb94];
public:
    emHammerbros(u32 p1, emCreate* create);
    virtual ~emHammerbros();
    // TODO: emHammerbros virtual functions
};
static_assert(sizeof(emHammerbros) == 0x5ea4, "Class is wrong size!");




