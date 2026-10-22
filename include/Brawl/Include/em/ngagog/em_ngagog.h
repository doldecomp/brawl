#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emNgagog : public Enemy {
    u8 unk5310[0xaf4];
public:
    emNgagog(u32 p1, emCreate* create);
    virtual ~emNgagog();
    // TODO: emNgagog virtual functions
};
static_assert(sizeof(emNgagog) == 0x5e04, "Class is wrong size!");


