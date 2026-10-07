#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

class ftYoshiStatusUniqProcessSpecialLw : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialLw() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
};

class ftYoshiStatusUniqProcessSpecialAirLw : public soStatusUniqProcess {
public:
    virtual ~ftYoshiStatusUniqProcessSpecialAirLw() { }
    virtual void execStatus(soModuleAccesser* moduleAccesser);
};

extern ftYoshiStatusUniqProcessSpecialLw g_ftYoshiStatusUniqProcessSpecialLw;
extern ftYoshiStatusUniqProcessSpecialAirLw g_ftYoshiStatusUniqProcessSpecialAirLw;
