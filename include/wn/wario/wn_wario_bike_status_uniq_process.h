#pragma once
#include <so/status/so_status_module_impl.h>
#include <wn/wario/wn_wario_bike.h>
class wnWarioBikeStatusUniqProcessUtility : public soStatusUniqProcess {
public:
    virtual ~wnWarioBikeStatusUniqProcessUtility() {}
    virtual void exitStatus(soModuleAccesser*, int);
    virtual void execStatus(soModuleAccesser*);
    virtual void execMapCorrection(soModuleAccesser*);
    virtual void execFixPosCounter(soModuleAccesser*);
};
class wnWarioBikeStatusUniqProcessStart : public soStatusUniqProcess {
public:
    virtual ~wnWarioBikeStatusUniqProcessStart() {}
    virtual void exitStatus(soModuleAccesser*, int);
    virtual void execFixPos(soModuleAccesser*);
};
class wnWarioBikeStatusUniqProcessDrive : public wnWarioBikeStatusUniqProcessUtility {
public:
    virtual ~wnWarioBikeStatusUniqProcessDrive() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execFixPosCounter(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};
class wnWarioBikeStatusUniqProcessWheelie : public wnWarioBikeStatusUniqProcessUtility {
public:
    virtual ~wnWarioBikeStatusUniqProcessWheelie() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
    virtual void execFixPosCounter(soModuleAccesser*);
};
