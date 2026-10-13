#pragma once

#include <StaticAssert.h>
#include <gm/gm_global_mode_melee.h>
#include <types.h>

struct gmSelCharData {
    char _spacer[0xb8]; // 0x00
    gmPlayerInitData m_playersInitData[MAX_PLAYERS];
    char _0x33c[4];
};
static_assert(sizeof(gmSelCharData) == 0x340, "Class is wrong size!");

namespace static_checks {

} // namespace static_checks
