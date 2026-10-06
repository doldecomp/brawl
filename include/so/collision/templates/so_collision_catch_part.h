#pragma once

#include <StaticAssert.h>
#include <so/collision/so_collision.h>
#include <so/so_array.h>
#include <types.h>

// Layout verified by the array-copy methods and concrete-vector element stride.
struct soCollisionCatchData {
    // MATCH-ONLY: raw words preserve the original aggregate-copy instructions.
    u32 unk0, unk4, unk8, unkC, unk10, unk14;
};
static_assert(sizeof(soCollisionCatchData) == 0x18, "Class is wrong size!");

class soCollisionCatchPart {
    s32 unk0;
    soCollisionCatchData m_data;
    soArrayVector<clTarget, 6> m_targets;
    s32 unk58;
};
static_assert(sizeof(soCollisionCatchPart) == 0x5C, "Class is wrong size!");
