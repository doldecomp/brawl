#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <so/area/so_area_module_impl.h>
#include <so/so_module_accesser.h>
#include <types.h>

class emAreaModuleImpl : public soAreaModuleImpl {
public:
    static s32 getTargetFoundDistance(soModuleAccesser* acc, s32 p2);
    static bool isTargetFoundDir(soModuleAccesser* acc, s32 p2, s32 p3);
    static Vec3f getTargetPos(soModuleAccesser* acc, u32 p2, bool p3);
    static bool isExistTarget(soModuleAccesser* acc, u32 p2);

    bool checkArea(soModuleAccesser* acc, u32 p2, u32 p3);
};
// TODO size assertion
