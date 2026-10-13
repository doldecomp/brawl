#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emFlows : public Enemy {
    u8 unk5310[0xa74];
public:
    emFlows(u32 p1, emCreate* create);
    virtual ~emFlows();
    // TODO: emFlows virtual functions
};
static_assert(sizeof(emFlows) == 0x5d84, "Class is wrong size!");

