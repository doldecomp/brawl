#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emDeathpod : public Enemy {
    u8 unk5310[0x7ec];
public:
    emDeathpod(u32 p1, emCreate* create);
    virtual ~emDeathpod();
    // TODO: emDeathpod virtual functions
};
static_assert(sizeof(emDeathpod) == 0x5afc, "Class is wrong size!");

