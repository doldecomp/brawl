#pragma once

#include <StaticAssert.h>
#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/galleom/em_galleom.h>
#include <em/resource/em_resource_module_impl.h>
#include <types.h>

struct emGalleomParam {

};

class emGalleomParamAccesser : public emExtendParamAccesser {
public:
    emGalleomParamAccesser();
    virtual ~emGalleomParamAccesser();
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual void* getParamIndefinite(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
};
static_assert(sizeof(emGalleomParamAccesser) == 0xC, "Class is the wrong size!");

extern emGalleomParamAccesser g_emGalleomParamAccesser;
