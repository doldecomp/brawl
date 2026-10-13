#pragma once

#include <StaticAssert.h>
#include <gr/collision/gr_collision_joint.h>
#include <gr/collision/gr_collision_line.h>
#include <types.h>

class grCollision;

class grCollisionLineWork {
    // 0
    grCollisionLine* m_collisionLine;
    // 4
    grCollisionJoint* m_collisionJoint;
    // 8
    grCollision* m_collision;
    // 12
    char _spacer[4];
};
static_assert(sizeof(grCollisionLineWork) == 16, "Class is wrong size!");