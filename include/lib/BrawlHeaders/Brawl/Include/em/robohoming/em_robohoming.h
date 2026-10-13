#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <types.h>

class emRobohoming : public Enemy {
    u8 unk5310[0xe54];
public:
    emRobohoming(u32 p1, emCreate* create);
    virtual ~emRobohoming();
    // TODO: emRobohoming virtual functions
};
static_assert(sizeof(emRobohoming) == 0x6164, "Class is wrong size!");

