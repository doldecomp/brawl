#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emSpar : public Enemy {
    u8 unk5310[0xc0c];
public:
    emSpar(u32 p1, emCreate* create);
    virtual ~emSpar();
    // TODO: emSpar virtual functions
};
static_assert(sizeof(emSpar) == 0x5f1c, "Class is wrong size!");


