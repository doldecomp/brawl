#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emBitan : public Enemy {
    u8 unk5310[0x620];
public:
    emBitan(u32 p1, emCreate* create);
    virtual ~emBitan();
    // TODO: emBitan virtual functions
};
static_assert(sizeof(emBitan) == 0x5930, "Class is wrong size!");





