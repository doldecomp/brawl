#pragma once

#include <so/status/so_status_module_impl.h>

class ftStatusUniqProcessCatchPull : public soStatusUniqProcess {
public:
    virtual void initStatus(soModuleAccesser*);
    // Original CatchPull vtable imports this override, rather than the generic false callback.
    virtual bool checkDamage(soModuleAccesser*, void*);
};
