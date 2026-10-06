#pragma once

#include <StaticAssert.h>
#include <so/collision/so_collision.h>
#include <so/so_array.h>
#include <types.h>

// Shadows the BrawlHeaders placeholder with the layout verified by the array-copy methods.
struct soCollisionSearchData {
    // MATCH-ONLY: raw words preserve the original aggregate-copy instructions.
    u32 unk0, unk4, unk8, unkC, unk10, unk14;
};
static_assert(sizeof(soCollisionSearchData) == 0x18, "Class is wrong size!");

class soCollisionSearchPart {
    s32 unk0;
    soCollisionSearchData m_data;
    soArrayVector<clTarget, 6> m_targets;
    s32 unk58;
    s32 unk5C;
};
static_assert(sizeof(soCollisionSearchPart) == 0x60, "Class is wrong size!");
