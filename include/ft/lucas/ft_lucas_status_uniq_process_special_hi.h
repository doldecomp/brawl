#pragma once

#include <so/status/so_status_module_impl.h>

class soModuleAccesser;

// Lucas's PK Thunder aim, flight, recovery, and reflector status processes.
class ftLucasStatusUniqProcessSpecialHi : public soStatusUniqProcess {
public:
    virtual ~ftLucasStatusUniqProcessSpecialHi();
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
    virtual void execFixPosCounter(soModuleAccesser* moduleAccesser);
};

class ftLucasStatusUniqProcessSpecialHiAttack : public soStatusUniqProcess {
public:
    virtual ~ftLucasStatusUniqProcessSpecialHiAttack();
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
    virtual void execFixPosCounter(soModuleAccesser* moduleAccesser);
};

class ftLucasStatusUniqProcessSpecialHiAttackEnd : public soStatusUniqProcess {
public:
    virtual ~ftLucasStatusUniqProcessSpecialHiAttackEnd();
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
};

class ftLucasStatusUniqProcessSpecialHiReflect : public soStatusUniqProcess {
public:
    virtual ~ftLucasStatusUniqProcessSpecialHiReflect();
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);
};
