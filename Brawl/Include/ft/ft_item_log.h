#pragma once

#include <StaticAssert.h>
#include <types.h>

class ftItemLog
{
public:
    ftItemLog();
    ~ftItemLog();
};
static_assert(sizeof(ftItemLog) == 0x1, "Class is wrong size!");
