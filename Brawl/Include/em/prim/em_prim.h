#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emPrim : public Enemy {
    u8 unk5310[0x595c];
public:
    emPrim(u32 p1, emCreate* create);
    virtual ~emPrim();
    // TODO: emPrim virtual functions
};
static_assert(sizeof(emPrim) == 0xac6c, "Class is wrong size!");


