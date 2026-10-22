#pragma once

#include <StaticAssert.h>
#include <types.h>

class MuSelctChrList {
public:
    char _0[0x160];
};

static_assert(sizeof(MuSelctChrList) == 0x160, "Wrong size for class!");