#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emMite : public Enemy {
    u8 unk5310[0x7d4];
public:
    emMite(u32 p1, emCreate* create);
    virtual ~emMite();
    // TODO: emMite virtual functions
};
static_assert(sizeof(emMite) == 0x5ae4, "Class is wrong size!");


