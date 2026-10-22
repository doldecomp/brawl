#pragma once

#include <StaticAssert.h>
#include <types.h>

class muSelCharPlayerArea;
class muSelCharHand;

class muSelCharCoin {
public:
    char _0x0[0x10];
    muSelCharHand* m_selCharHand;
    muSelCharPlayerArea* m_selCharPlayerArea;
    char _0x18[0x8];
};
static_assert(sizeof(muSelCharCoin) == 0x20, "Class is wrong size!");