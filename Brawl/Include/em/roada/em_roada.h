#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emRoada : public Enemy {
    u8 unk5310[0x77c];
public:
    emRoada(u32 p1, emCreate* create);
    virtual ~emRoada();
    // TODO: emRoada virtual functions
};
static_assert(sizeof(emRoada) == 0x5a8c, "Class is wrong size!");

