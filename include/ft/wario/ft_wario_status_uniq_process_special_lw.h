#pragma once
#include <so/status/so_status_module_impl.h>
#include <ft/wario/ft_wario.h>
class ftWarioStatusUniqProcessSpecialLw : public soStatusUniqProcess {
public:
    virtual ~ftWarioStatusUniqProcessSpecialLw() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
    virtual void execStatus(soModuleAccesser*);
};
