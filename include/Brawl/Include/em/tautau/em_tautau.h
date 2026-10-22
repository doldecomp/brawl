#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emTautau : public Enemy {
    u8 unk5310[0xb0c];
public:
    emTautau(u32 p1, emCreate* create);
    virtual ~emTautau();
    // TODO: emTautau virtual functions
};
static_assert(sizeof(emTautau) == 0x5e1c, "Class is wrong size!");

