#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emBoobas : public Enemy {
    u8 unk5310[0xa14];
public:
    emBoobas(u32 p1, emCreate* create);
    virtual ~emBoobas();
    // TODO: emBoobas virtual functions
};
static_assert(sizeof(emBoobas) == 0x5d24, "Class is wrong size!");



