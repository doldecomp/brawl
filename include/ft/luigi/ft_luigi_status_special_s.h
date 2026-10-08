#pragma once

#include <so/status/so_status_module_impl.h>

class ftLuigiStatusUniqProcessSpecialSRam : public soStatusUniqProcess {
public:
    virtual ~ftLuigiStatusUniqProcessSpecialSRam() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};

class ftLuigiStatusUniqProcessSpecialSWall : public soStatusUniqProcess {
public:
    virtual ~ftLuigiStatusUniqProcessSpecialSWall() {}
    virtual void initStatus(soModuleAccesser*);
};

extern ftLuigiStatusUniqProcessSpecialSRam g_ftLuigiStatusUniqProcessSpecialSRam;
extern ftLuigiStatusUniqProcessSpecialSWall g_ftLuigiStatusUniqProcessSpecialSWall;
