#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emDekakuribo : public Enemy {
    u8 unk5310[0x9a8];
public:
    emDekakuribo(u32 p1, emCreate* create);
    virtual ~emDekakuribo();
    // TODO: emDekakuribo virtual functions
};
static_assert(sizeof(emDekakuribo) == 0x5cb8, "Class is wrong size!");

