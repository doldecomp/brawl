#pragma once

#include <StaticAssert.h>
#include <types.h>

struct gmStageEditData {
    char _spacer[0x24e4]; // 0x00
};
static_assert(sizeof(gmStageEditData) == 0x24e4, "Class is wrong size!");