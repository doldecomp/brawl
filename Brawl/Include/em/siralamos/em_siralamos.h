#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emSiralamos : public Enemy {
    u8 unk5310[0x5364];
public:
    emSiralamos(u32 p1, emCreate* create);
    virtual ~emSiralamos();
    // TODO: emSiralamos virtual functions
};
static_assert(sizeof(emSiralamos) == 0xa674, "Class is wrong size!");


