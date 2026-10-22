#pragma once

#include <StaticAssert.h>
#include <types.h>

class emArchive {
    int enmCommonResourceId;
    int brresResourceId;
    int paramResourceId;
    int weaponResourceId;
    int faceTexBrresResourceId;
    int extendBrresResourceId;
};
static_assert(sizeof(emArchive) == 24, "Class is wrong size!");