#pragma once

#include <StaticAssert.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

class emExtendParamAccesser : public soParamAccesser {
public:
    emExtendParamAccesser(u32 index);
    virtual ~emExtendParamAccesser();
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) = 0;
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) = 0;
    virtual void* getParamIndefinite(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) = 0;

    static void reset(emExtendParamAccesser* acc, u32 index);
    static emExtendParamAccesser* getAccesser(u32 index);
};
static_assert(sizeof(emExtendParamAccesser) == 0xC, "Class is the wrong size!");
