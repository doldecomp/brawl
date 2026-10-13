#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emRobodistance : public Enemy {
    u8 unk5310[0xf3c];
public:
    emRobodistance(u32 p1, emCreate* create);
    virtual ~emRobodistance();
    // TODO: emRobodistance virtual functions
};
static_assert(sizeof(emRobodistance) == 0x624c, "Class is wrong size!");

