#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emKuribo : public Enemy {
    u8 unk5310[0xa14];
public:
    emKuribo(u32 p1, emCreate* create);
    virtual ~emKuribo();
    // TODO: emKuribo virtual functions
};
static_assert(sizeof(emKuribo) == 0x5d24, "Class is wrong size!");

