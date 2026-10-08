#pragma once
#include <so/status/so_status_module_impl.h>
class ftSonicStatusUniqProcessSpecialSWallEnd : public soStatusUniqProcess {
public:
    virtual ~ftSonicStatusUniqProcessSpecialSWallEnd() {}
    virtual void initStatus(soModuleAccesser*);
};
extern ftSonicStatusUniqProcessSpecialSWallEnd g_ftSonicStatusUniqProcessSpecialSWallEnd;
