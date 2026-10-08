#pragma once

#include <so/status/so_status_module_impl.h>

class ftPurinStatusUniqProcessSpecialS : public soStatusUniqProcess {
public:
    // MATCH-ONLY: retain the native out-of-line global constructor.
    ftPurinStatusUniqProcessSpecialS() __attribute__((never_inline)) { }
    virtual ~ftPurinStatusUniqProcessSpecialS() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    float getAngleSpecialAirSPurin(float stickY, soModuleAccesser* moduleAccesser);
};

class ftPurinStatusUniqProcessSpecialHi : public soStatusUniqProcess {
public:
    // MATCH-ONLY: retain the native out-of-line global constructor.
    ftPurinStatusUniqProcessSpecialHi() __attribute__((never_inline)) { }
    virtual ~ftPurinStatusUniqProcessSpecialHi() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
};

extern ftPurinStatusUniqProcessSpecialS g_ftPurinStatusUniqProcessSpecialS;
extern ftPurinStatusUniqProcessSpecialHi g_ftPurinStatusUniqProcessSpecialHi;
