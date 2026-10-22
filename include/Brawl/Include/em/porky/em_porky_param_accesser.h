#pragma once

#include <StaticAssert.h>
#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/porky/em_porky.h>
#include <em/resource/em_resource_module_impl.h>
#include <types.h>

struct emPorkyParam {

};

class emPorkyParamAccesser : public emExtendParamAccesser {
public:
    emPorkyParamAccesser();
    virtual ~emPorkyParamAccesser();
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual void* getParamIndefinite(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
};
static_assert(sizeof(emPorkyParamAccesser) == 0xC, "Class is the wrong size!");

extern emPorkyParamAccesser g_emPorkyParamAccesser;
