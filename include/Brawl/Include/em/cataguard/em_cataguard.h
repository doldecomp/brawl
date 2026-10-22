#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emCataguard : public Enemy {
    u8 unk5310[0xa6c];
public:
    emCataguard(u32 p1, emCreate* create);
    virtual ~emCataguard();
    // TODO: emCataguard virtual functions
};
static_assert(sizeof(emCataguard) == 0x5d7c, "Class is wrong size!");



