#pragma once

#include <StaticAssert.h>
#include <types.h>

struct gmTournamentData {
    char _spacer[0x510]; // 0x00
};
static_assert(sizeof(gmTournamentData) == 0x510, "Class is wrong size!");