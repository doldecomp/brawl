#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emDuon : public Enemy {
    u8 unk5310[0x12fc];
public:
    emDuon(u32 p1, emCreate* create);
    virtual ~emDuon();
    // TODO: emDuon virtual functions
};
static_assert(sizeof(emDuon) == 0x660c, "Class is wrong size!");

