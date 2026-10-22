#pragma once

#include <StaticAssert.h>
#include <types.h>

class MuSelctChrNameEntry {
public:
    char _0[0x94];
};

static_assert(sizeof(MuSelctChrNameEntry) == 0x94, "Wrong size for class!");