#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emBotron : public Enemy {
    u8 unk5310[0x918];
public:
    emBotron(u32 p1, emCreate* create);
    virtual ~emBotron();
    // TODO: emBotron virtual functions
};
static_assert(sizeof(emBotron) == 0x5c28, "Class is wrong size!");




