#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emGhamghabase : public Enemy {
    u8 unk5310[0x65c];
public:
    emGhamghabase(u32 p1, emCreate* create);
    virtual ~emGhamghabase();
    // TODO: emGhamghabase virtual functions
};
static_assert(sizeof(emGhamghabase) == 0x596c, "Class is wrong size!");

