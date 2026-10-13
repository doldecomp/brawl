#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emMasterhand : public Enemy {
    u8 unk5310[0xb6c];
public:
    emMasterhand(u32 p1, emCreate* create);
    virtual ~emMasterhand();
    // TODO: emMasterhand virtual functions
};
static_assert(sizeof(emMasterhand) == 0x5e7c, "Class is wrong size!");

