#pragma once

#include <so/area/so_area_module_impl.h>

// Fighter-specific area data extends the shared area module. The inheritance
// and size follow the native RTTI and builder layout; the added state is unknown.
class ftAreaModuleImpl : public soAreaModuleImpl {
    u8 unk4C[0x1C];
public:
    ftAreaModuleImpl(soModuleAccesser* acc, u8 category, void* instances,
                     void* contactLogs, void* checker, void* winds,
                     soEventObserverRegistrationDesc* regDesc, int unk8);
    virtual ~ftAreaModuleImpl();
    void setAreaData(soSet<soAreaData>* areas);
};
static_assert(sizeof(ftAreaModuleImpl) == 0x68, "Fighter area module layout");
