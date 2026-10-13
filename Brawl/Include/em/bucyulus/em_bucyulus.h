#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emBucyulus : public Enemy {
    u8 unk5310[0x76c];
public:
    emBucyulus(u32 p1, emCreate* create);
    virtual ~emBucyulus();
    // TODO: emBucyulus virtual functions
};
static_assert(sizeof(emBucyulus) == 0x5a7c, "Class is wrong size!");





