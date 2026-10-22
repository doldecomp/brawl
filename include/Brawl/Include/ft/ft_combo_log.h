#pragma once

#include <StaticAssert.h>
#include <types.h>

class ftComboLog
{
public:
    ftComboLog();
    ~ftComboLog();
};
static_assert(sizeof(ftComboLog) == 0x1, "Class is wrong size!");
