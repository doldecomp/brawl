#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <mt/mt_vector.h>
#include <gr/collision/gr_collision.h>

bool stRayCheck(Vec3f* pos, Vec3f* dir, bool, grCollision*, bool, u8 targetMask);
bool stRayCheck(Vec3f* pos, Vec3f* dir, Vec3f* outHitPos, Vec3f* outCollNormalVec, bool, grCollision*, bool, u8 targetMask);
bool stRayCheck(Vec3f* pos, Vec3f* dir, int* lineId, Vec3f* outHitPos, Vec3f* outCollNormalVec, bool, bool, u8 targetMask);

