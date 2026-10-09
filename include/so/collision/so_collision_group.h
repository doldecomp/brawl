#pragma once

// Local shadow of BrawlHeaders' so/collision/so_collision_group.h. The SDK copy is a plain 120-byte blob (alignment 1);
// the original class has 4-byte alignment, which matters for arrays that embed it (soArrayVector<soCollisionGroup, N>
// places its elements 4-aligned). Translation units that need the aligned layout define SO_COLLISION_GROUP_ALIGNED.

#include <StaticAssert.h>
#include <types.h>

class soCollisionGroup {
#ifdef SO_COLLISION_GROUP_ALIGNED
    u32 _spacer[30];
#else
    char _spacer[120];
#endif

public:
    soCollisionGroup();
    ~soCollisionGroup();

};
static_assert(sizeof(soCollisionGroup) == 120, "Class is wrong size!");
