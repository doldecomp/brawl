#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emFalconflyer : public Enemy {
    u8 unk5310[0x734];
public:
    emFalconflyer(u32 p1, emCreate* create);
    virtual ~emFalconflyer();
    // TODO: emFalconflyer virtual functions
};
static_assert(sizeof(emFalconflyer) == 0x5a44, "Class is wrong size!");

