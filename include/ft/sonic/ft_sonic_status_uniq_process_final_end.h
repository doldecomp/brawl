#pragma once
#include <so/status/so_status_module_impl.h>
class soModuleAccesser;
class ftSonicStatusUniqProcessFinalEnd : public soStatusUniqProcess {
public:
    virtual ~ftSonicStatusUniqProcessFinalEnd() {}
    virtual void initStatus(soModuleAccesser*);
};
extern ftSonicStatusUniqProcessFinalEnd g_ftSonicStatusUniqProcessFinalEnd;
