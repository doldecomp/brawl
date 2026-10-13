#pragma once

#include <StaticAssert.h>
#include <ft/ft_param_customize_module_impl.h>
#include <types.h>

class soModuleAccesser;

class ftLucarioParamCustomizeModule : ftParamCustomizeModuleImpl {
public:
    ftLucarioParamCustomizeModule(soModuleAccesser* accsr);
    virtual ~ftLucarioParamCustomizeModule();
    virtual float getAttackPowerMul(void* p1);
};
static_assert(sizeof(ftLucarioParamCustomizeModule) == 0x694, "Class is the wrong size!");
