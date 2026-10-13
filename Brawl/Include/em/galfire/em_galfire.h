#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emGalfire : public Enemy {
    u8 unk5310[0x784];
public:
    emGalfire(u32 p1, emCreate* create);
    virtual ~emGalfire();
    // TODO: emGalfire virtual functions
};
static_assert(sizeof(emGalfire) == 0x5a94, "Class is wrong size!");

