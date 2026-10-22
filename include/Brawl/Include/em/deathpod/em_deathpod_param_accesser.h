#pragma once

#include <StaticAssert.h>
#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/deathpod/em_deathpod.h>
#include <em/resource/em_resource_module_impl.h>
#include <types.h>

struct emDeathpodParam {

};

class emDeathpodParamAccesser : public emExtendParamAccesser {
public:
    emDeathpodParamAccesser();
    virtual ~emDeathpodParamAccesser();
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual void* getParamIndefinite(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
};
static_assert(sizeof(emDeathpodParamAccesser) == 0xC, "Class is the wrong size!");

extern emDeathpodParamAccesser g_emRoturretParamAccesser;
