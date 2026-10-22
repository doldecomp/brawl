#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emBosspackun : public Enemy {
    u8 unk5310[0x5030];
public:
    emBosspackun(u32 p1, emCreate* create);
    virtual ~emBosspackun();
    // TODO: emBosspackun virtual functions
};
static_assert(sizeof(emBosspackun) == 0xa340, "Class is wrong size!");



