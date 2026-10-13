#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <gm/gm_lib.h>

struct gmSelStageData {
    char _0[34];
    srStageKind m_stageKind : 16;
    u8 m_subStageKind;
    char _37[771];
};
static_assert(sizeof(gmSelStageData) == 808, "Class is wrong size!");