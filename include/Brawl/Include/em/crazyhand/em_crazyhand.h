#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emCrazyhand : public Enemy {
    u8 unk5310[0xe10];
public:
    emCrazyhand(u32 p1, emCreate* create);
    virtual ~emCrazyhand();
    // TODO: emCrazyhand virtual functions
};
static_assert(sizeof(emCrazyhand) == 0x6120, "Class is wrong size!");

