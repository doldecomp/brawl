#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emFaulong : public Enemy {
    u8 unk5310[0x8c4];
public:
    emFaulong(u32 p1, emCreate* create);
    virtual ~emFaulong();
    // TODO: emFaulong virtual functions
};
static_assert(sizeof(emFaulong) == 0x5bd4, "Class is wrong size!");
