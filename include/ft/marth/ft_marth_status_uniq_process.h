#pragma once

#include <so/status/so_status_module_impl.h>
#include <types.h>

class soModuleAccesser;

// Marth's special move status processes.

class ftMarthStatusUniqProcessSpecialS : public soStatusUniqProcess {
public:
    virtual ~ftMarthStatusUniqProcessSpecialS() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
};

class ftMarthStatusUniqProcessSpecialHi : public soStatusUniqProcess {
public:
    virtual ~ftMarthStatusUniqProcessSpecialHi() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual bool onChangeLr(soModuleAccesser* moduleAccesser, float, float);
};

class ftMarthStatusUniqProcessSpecialLw : public soStatusUniqProcess {
public:
    virtual ~ftMarthStatusUniqProcessSpecialLw() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
};

class ftMarthStatusUniqProcessFinal : public soStatusUniqProcess {
public:
    virtual ~ftMarthStatusUniqProcessFinal() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execStop(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
};

extern ftMarthStatusUniqProcessSpecialS g_ftMarthStatusUniqProcessSpecialS;
extern ftMarthStatusUniqProcessSpecialHi g_ftMarthStatusUniqProcessSpecialHi;
extern ftMarthStatusUniqProcessSpecialLw g_ftMarthStatusUniqProcessSpecialLw;
extern ftMarthStatusUniqProcessFinal g_ftMarthStatusUniqProcessFinal;
