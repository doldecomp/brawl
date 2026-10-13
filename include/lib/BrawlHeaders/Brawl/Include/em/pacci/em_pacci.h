#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emPacci : public Enemy {
    u8 unk5310[0xda8];
public:
    emPacci(u32 p1, emCreate* create);
    virtual ~emPacci();
    // TODO: emPacci virtual functions
};
static_assert(sizeof(emPacci) == 0x60b8, "Class is wrong size!");


