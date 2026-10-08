#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

class wnSnakeNikitaMissileStatusUniqProcessFly : public soStatusUniqProcess {
public:
    wnSnakeNikitaMissileStatusUniqProcessFly();
    virtual ~wnSnakeNikitaMissileStatusUniqProcessFly();
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    static wnSnakeNikitaMissileStatusUniqProcessFly* getInstance();
private:
    void processSoundEffect(soModuleAccesser* moduleAccesser, float turnDelta);
};

extern wnSnakeNikitaMissileStatusUniqProcessFly g_wnSnakeNikitaMissileStatusUniqProcessFly;
