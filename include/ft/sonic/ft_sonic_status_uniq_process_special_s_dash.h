#pragma once
#include <so/status/so_status_module_impl.h>
class soModuleAccesser;
class ftSonicStatusUniqProcessSpecialSDash : public soStatusUniqProcess {
public:
    virtual ~ftSonicStatusUniqProcessSpecialSDash() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
    void processChangeGroundMotion(soModuleAccesser*);
    void addGroundMotionTransitionTerm(soModuleAccesser*);
    void processChangeGroundCorrect(soModuleAccesser*);
    void syncSpeedMotionRate(soModuleAccesser*);
    void processCheckAttack(soModuleAccesser*);
    void syncSpeedAttackPower(soModuleAccesser*);
    float getCurrentSpeed(soModuleAccesser*);
};
extern ftSonicStatusUniqProcessSpecialSDash g_ftSonicStatusUniqProcessSpecialSDash;
