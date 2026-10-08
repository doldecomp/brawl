// SHADOW of BrawlHeaders/so/visibility/so_visibility_module_impl.h: identical except for the FT_MODULE_BUILDER-guarded declarations
// (constructors/destructors of sora_melee classes that fighter module builders call). Built only for fighter RELs.
#pragma once

#include <StaticAssert.h>
#include <so/visibility/so_visibility_module_simple.h>
#include <so/status/so_status_event_presenter.h>
#include <types.h>

class soVisibilityModuleImpl : public soVisibilityModuleSimple, public soStatusEventObserver {
#ifdef FT_MODULE_BUILDER
public:
    soVisibilityModuleImpl(soModuleAccesser* acc, soVisibilityData* data, int n);
private:
#endif
    char _0x18[2];
    soVisibilityData* m_data;
    s8* m_setData;
    u32 m_numSets;
    char _0x2c[4];

public:
    virtual void activate();
    virtual void setData(soVisibilityData*);
    virtual void set(u32, int);
    virtual void setStatusDefault(u32, u8, bool);
    virtual void setDefaultAll();
    virtual void update();
    virtual void hideAll();
    virtual int get(u32);

    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soVisibilityModuleImpl) == 0x30, "Class is wrong size!");