#pragma once

#include <StaticAssert.h>
#include <types.h>

class soDamageNoReactionModule {
    int m_mode;
    int m_modeStatus;
    char _8[8];
    int m_modeStatus2nd;
    char _20[8];
    bool m_isModeAlways;
    bool m_isModePerfect;
    char _30[2];
};
static_assert(sizeof(soDamageNoReactionModule) == 32, "Class is wrong size!");