#pragma once

// Local header: the collision manager singleton created by the fighter manager's setMode (sora map: soCollisionManager::soCollisionManager).

#include <StaticAssert.h>
#include <types.h>

class soCollisionManager {
public:
    soCollisionManager();
    char _0[0x1508];
};
static_assert(sizeof(soCollisionManager) == 0x1508, "Class is wrong size!");

// HYPOTHESIS: name of the singleton pointer (created lazily by ftManager::setMode)
extern soCollisionManager* g_soCollisionManager;
