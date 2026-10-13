#pragma once

#include <StaticAssert.h>
#include <types.h>

enum soKind {
    StageObject_Invalid = -0x1,
    StageObject_Fighter = 0x0,
    StageObject_Enemy = 0x1,
    StageObject_Weapon = 0x2,
    StageObject_Yakumono = 0x3,
    StageObject_Item = 0x4
};