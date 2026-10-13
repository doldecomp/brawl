#pragma once

#include <StaticAssert.h>
#include <types.h>

class ftBombheiLog
{
public:
    ftBombheiLog();
    ~ftBombheiLog();
};
static_assert(sizeof(ftBombheiLog) == 0x1, "Class is wrong size!");
