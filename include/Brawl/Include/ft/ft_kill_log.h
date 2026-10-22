#pragma once

#include <StaticAssert.h>
#include <types.h>

class ftKillLog
{
public:
    ftKillLog();
    ~ftKillLog();
};
static_assert(sizeof(ftKillLog) == 0x1, "Class is wrong size!");
