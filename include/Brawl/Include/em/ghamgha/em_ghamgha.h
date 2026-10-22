#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emGhamgha : public Enemy {
    u8 unk5310[0x858];
public:
    emGhamgha(u32 p1, emCreate* create);
    virtual ~emGhamgha();
    // TODO: emGhamgha virtual functions
};
static_assert(sizeof(emGhamgha) == 0x5b68, "Class is wrong size!");
