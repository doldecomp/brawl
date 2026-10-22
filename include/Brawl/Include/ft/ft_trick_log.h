#pragma once

#include <StaticAssert.h>
#include <types.h>

class ftTrickLog
{
public:
    ftTrickLog();
    ~ftTrickLog();
};
static_assert(sizeof(ftTrickLog) == 0x1, "Class is wrong size!");
