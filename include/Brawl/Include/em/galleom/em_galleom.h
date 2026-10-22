#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emGalleom : public Enemy {
    u8 unk5310[0x1560];
public:
    emGalleom(u32 p1, emCreate* create);
    virtual ~emGalleom();
    // TODO: emGalleom virtual functions
};
static_assert(sizeof(emGalleom) == 0x6870, "Class is wrong size!");

