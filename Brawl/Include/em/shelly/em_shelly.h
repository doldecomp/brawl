#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emShelly : public Enemy {
    u8 unk5310[0xf90];
public:
    emShelly(u32 p1, emCreate* create);
    virtual ~emShelly();
    // TODO: emShelly virtual functions
};
static_assert(sizeof(emShelly) == 0x62a0, "Class is wrong size!");


