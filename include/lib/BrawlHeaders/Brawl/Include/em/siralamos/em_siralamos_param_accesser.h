#pragma once

#include <StaticAssert.h>
#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/siralamos/em_siralamos.h>
#include <em/resource/em_resource_module_impl.h>
#include <types.h>

struct emSiralamosParam {

};

class emSiralamosParamAccesser : public emExtendParamAccesser {
public:
    emSiralamosParamAccesser();
    virtual ~emSiralamosParamAccesser();
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual void* getParamIndefinite(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
};
static_assert(sizeof(emSiralamosParamAccesser) == 0xC, "Class is the wrong size!");

extern emSiralamosParamAccesser g_emArmightParamAccesser;
