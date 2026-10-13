#pragma once

#include <StaticAssert.h>
#include <types.h>

class soLockable {
    char _spacer[8];
};
static_assert(sizeof(soLockable) == 8, "Class is wrong size!");