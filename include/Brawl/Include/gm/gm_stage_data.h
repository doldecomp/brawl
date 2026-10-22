#pragma once

#include <StaticAssert.h>
#include <types.h>

struct gmStageData {
    struct ItemCollection {
        u16 m_num;
        short m_variations[256];
        u8 m_kinds[256];
    };

    short m_exSetting;
    char _2[2];
    float m_motionRatio;
    float m_motionSubRatio;
    ItemCollection m_itemCollection;
    char _782[2310];
};
static_assert(sizeof(gmStageData) == 3092, "Class is wrong size!");