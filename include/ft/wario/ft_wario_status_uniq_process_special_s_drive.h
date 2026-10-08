#pragma once
#include <so/status/so_status_module_impl.h>
class ftWarioStatusUniqProcessSpecialSCommon : public soStatusUniqProcess {
public:
    virtual ~ftWarioStatusUniqProcessSpecialSCommon() { }
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
    virtual void execFixPos(soModuleAccesser*);
    virtual bool checkDamage(soModuleAccesser*, void*);
};
class ftWarioStatusUniqProcessSpecialSDrive : public ftWarioStatusUniqProcessSpecialSCommon {
public:
    virtual ~ftWarioStatusUniqProcessSpecialSDrive() { }
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
};
