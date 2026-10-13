#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emRidley : public Enemy {
    u8 unk5310[0x19bc];
public:
    emRidley(u32 p1, emCreate* create);
    virtual ~emRidley();
    // TODO: emRidley virtual functions
};
static_assert(sizeof(emRidley) == 0x6ccc, "Class is wrong size!");


