#pragma once

#include <StaticAssert.h>
#include <types.h>

class ftEntry;

class ftInput {
    char _0x0[4];
    ftEntry* m_entry;
    char _0x8[24];
};
static_assert(sizeof(ftInput) == 0x20, "Class is wrong size!");