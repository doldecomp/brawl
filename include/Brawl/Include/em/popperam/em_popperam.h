#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emPopperam : public Enemy {
    u8 unk5310[0x938];
public:
    emPopperam(u32 p1, emCreate* create);
    virtual ~emPopperam();
    // TODO: emPopperam virtual functions
};
static_assert(sizeof(emPopperam) == 0x5c48, "Class is wrong size!");

