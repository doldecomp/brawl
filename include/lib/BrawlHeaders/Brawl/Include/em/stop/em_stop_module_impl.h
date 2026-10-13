#pragma once

#include <StaticAssert.h>
#include <so/so_module_accesser.h>
#include <so/stop/so_stop_module_impl.h>

class emStopModuleImpl : public soStopModuleImpl {
public:
    emStopModuleImpl(soModuleAccesser* acc);
    virtual ~emStopModuleImpl();
};
static_assert(sizeof(emStopModuleImpl) == 0x24, "Class is the wrong size!");
