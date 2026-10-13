#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emPorky : public Enemy {
    u8 unk5310[0x10f0];
public:
    emPorky(u32 p1, emCreate* create);
    virtual ~emPorky();
    // TODO: emPorky virtual functions
};
static_assert(sizeof(emPorky) == 0x6400, "Class is wrong size!");

