#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emJyakeel : public Enemy {
    u8 unk5310[0x424];
public:
    emJyakeel(u32 p1, emCreate* create);
    virtual ~emJyakeel();
    // TODO: emJyakeel virtual functions
};
static_assert(sizeof(emJyakeel) == 0x5734, "Class is wrong size!");
