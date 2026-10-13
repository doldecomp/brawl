#pragma once

#include <StaticAssert.h>
#include <so/so_module_accesser.h>
#include <so/so_target_search_unit.h>
#include <types.h>

class emTargetSearchUnit : public soTargetSearchUnit {
public:
    emTargetSearchUnit();
    ~emTargetSearchUnit();
    virtual bool checkTargetExist(soModuleAccesser* acc, u32 p2);
    virtual bool checkTargetInArea(soModuleAccesser* acc, u32 p2, u32 p3);
    virtual Vec3f getTargetPos(soModuleAccesser* acc, u32 p2);
    virtual Vec3f getSelfPos(soModuleAccesser* acc);
    virtual void initInterval(soModuleAccesser* acc);
};
static_assert(sizeof(emTargetSearchUnit) == 0x18, "Class is the wrong size!");
