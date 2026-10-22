#pragma once

#include <StaticAssert.h>
#include <so/resource/so_resource_id_accesser.h>
#include <so/resource/so_resource_module_impl.h>
#include <types.h>

class wnemResourceModuleImpl : public soResourceModuleImpl {
public:
    wnemResourceModuleImpl(u32 p1, soResourceIdAccesser* rsrcIdAcc, u8 p3);
    ~wnemResourceModuleImpl();
};
static_assert(sizeof(wnemResourceModuleImpl) == 0x18, "Class is wrong size!");
