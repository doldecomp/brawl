#pragma once

#include <StaticAssert.h>
#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/prim/em_prim.h>
#include <em/resource/em_resource_module_impl.h>
#include <types.h>

struct emPrimParam {

};

class emPrimParamAccesser : public emExtendParamAccesser {
public:
    emPrimParamAccesser();
    virtual ~emPrimParamAccesser();
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual void* getParamIndefinite(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
};
static_assert(sizeof(emPrimParamAccesser) == 0xC, "Class is the wrong size!");

extern emPrimParamAccesser g_emPrimidParamAccesser;
