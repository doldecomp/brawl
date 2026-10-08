#pragma once
#include <so/status/so_status_module_impl.h>
#include <ft/wario/ft_wario.h>
class ftWarioStatusUniqProcessSpecialHiStart : public soStatusUniqProcess {
public:
    virtual ~ftWarioStatusUniqProcessSpecialHiStart() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftWarioStatusUniqProcessSpecialHiJump : public soStatusUniqProcess {
public:
    virtual ~ftWarioStatusUniqProcessSpecialHiJump() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};
