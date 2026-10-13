#pragma once

#include <StaticAssert.h>
#include <so/resource/so_resource_id_accesser.h>
#include <types.h>

class soModuleAccesser;

class itResourceIdAccesserImpl : public soResourceIdAccesserImpl {
    soModuleAccesser* m_moduleAccsr;
    u32 m_archiveId;
public:
    itResourceIdAccesserImpl();
    virtual ~itResourceIdAccesserImpl() { }
    virtual u32 getArchiveId();

    itKind getItKind();
};
static_assert(sizeof(itResourceIdAccesserImpl) == 0x20, "Class is the wrong size!");
