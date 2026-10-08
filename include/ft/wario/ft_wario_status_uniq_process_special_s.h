#pragma once
#include <so/status/so_status_module_impl.h>
#include <so/link/so_link_event_presenter.h>
#include <ft/wario/ft_wario.h>

#include <wn/wario/wn_wario_bike_link_event.h>

class ftWarioStatusUniqProcessSpecialS : public soStatusUniqProcess {
public:
    virtual ~ftWarioStatusUniqProcessSpecialS() {}
    virtual void initStatus(soModuleAccesser*);
};
class ftWarioStatusUniqProcessSpecialSCommon : public soStatusUniqProcess {
public:
    virtual ~ftWarioStatusUniqProcessSpecialSCommon() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
    virtual void execFixPos(soModuleAccesser*);
    virtual bool checkDamage(soModuleAccesser*, void*);
};
class ftWarioStatusUniqProcessSpecialSStart : public ftWarioStatusUniqProcessSpecialSCommon {
public:
    virtual ~ftWarioStatusUniqProcessSpecialSStart() {}
    virtual void execFixPos(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};
class ftWarioStatusUniqProcessSpecialSWheelie : public ftWarioStatusUniqProcessSpecialSCommon {
public:
    virtual ~ftWarioStatusUniqProcessSpecialSWheelie() {}
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
    virtual bool checkDamage(soModuleAccesser*, void*);
};
class ftWarioStatusUniqProcessSpecialSEscape : public ftWarioStatusUniqProcessSpecialSCommon {
public:
    virtual ~ftWarioStatusUniqProcessSpecialSEscape() {}
    virtual void execFixPosCounter(soModuleAccesser*);
};
class ftWarioStatusUniqProcessSpecialSDown : public ftWarioStatusUniqProcessSpecialSCommon {
public:
    virtual ~ftWarioStatusUniqProcessSpecialSDown() {}
    virtual void initStatus(soModuleAccesser*);
};
