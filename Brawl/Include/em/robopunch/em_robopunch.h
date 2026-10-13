#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emRobopunch : public Enemy {
    u8 unk5310[0xf1c];
public:
    emRobopunch(u32 p1, emCreate* create);
    virtual ~emRobopunch();
    // TODO: emRobopunch virtual functions
};
static_assert(sizeof(emRobopunch) == 0x622c, "Class is wrong size!");

