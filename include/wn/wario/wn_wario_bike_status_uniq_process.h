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

// RTTI8494 lists only soStatusUniqProcess; TurnStart does not inherit Utility.
class wnWarioBikeStatusUniqProcessTurnStart : public soStatusUniqProcess {
public:
    virtual ~wnWarioBikeStatusUniqProcessTurnStart() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};

class wnWarioBikeStatusUniqProcessTurnLoop : public soStatusUniqProcess {
public:
    virtual ~wnWarioBikeStatusUniqProcessTurnLoop() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPosCounter(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};

class wnWarioBikeStatusUniqProcessTurnEnd : public soStatusUniqProcess {
public:
    virtual ~wnWarioBikeStatusUniqProcessTurnEnd() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};
// Native RTTI and vtables establish these source class bases and overrides.
class wnWarioBikeStatusUniqProcessTurnDown : public soStatusUniqProcess {
public:
    virtual ~wnWarioBikeStatusUniqProcessTurnDown() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};

class wnWarioBikeStatusUniqProcessEscape : public wnWarioBikeStatusUniqProcessUtility {
public:
    virtual ~wnWarioBikeStatusUniqProcessEscape() {}
    virtual void execFixPos(soModuleAccesser*);
};

class wnWarioBikeStatusUniqProcessBump : public wnWarioBikeStatusUniqProcessUtility {
public:
    virtual ~wnWarioBikeStatusUniqProcessBump() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};

// RTTI confirms Down derives directly from soStatusUniqProcess.
class wnWarioBikeStatusUniqProcessDown : public soStatusUniqProcess {
public:
    virtual ~wnWarioBikeStatusUniqProcessDown() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};

// Appeal and Item have native RTTI/vtable entries and distinct status TUs.
class wnWarioBikeStatusUniqProcessAppeal : public wnWarioBikeStatusUniqProcessUtility {
public:
    virtual ~wnWarioBikeStatusUniqProcessAppeal() {}
    virtual void execFixPosCounter(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};

class wnWarioBikeStatusUniqProcessItem : public soStatusUniqProcess {
public:
    virtual ~wnWarioBikeStatusUniqProcessItem() {}
    virtual void initStatus(soModuleAccesser*);
};
