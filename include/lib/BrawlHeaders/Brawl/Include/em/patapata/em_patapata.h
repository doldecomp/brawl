#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emPatapata : public Enemy {
    u8 unk5310[0xb04];
public:
    emPatapata(u32 p1, emCreate* create);
    virtual ~emPatapata();
    // TODO: emPatapata virtual functions
};
static_assert(sizeof(emPatapata) == 0x5e14, "Class is wrong size!");

