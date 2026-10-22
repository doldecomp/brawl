#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emRayquaza : public Enemy {
    u8 unk5310[0x1230];
public:
    emRayquaza(u32 p1, emCreate* create);
    virtual ~emRayquaza();
    // TODO: emRayquaza virtual functions
};
static_assert(sizeof(emRayquaza) == 0x6540, "Class is wrong size!");


