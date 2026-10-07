#pragma once

#include <so/status/so_status_module_impl.h>

// The shared Fox reflector process is also used by Wolf, with a character-specific turn.
class ftFoxStatusUniqProcessReflector : public soStatusUniqProcess {
public:
    virtual ~ftFoxStatusUniqProcessReflector();
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void setTurn(soModuleAccesser* moduleAccesser);
};

class ftWolfStatusUniqProcessReflectorImpl : public ftFoxStatusUniqProcessReflector {
public:
    ftWolfStatusUniqProcessReflectorImpl();
    virtual ~ftWolfStatusUniqProcessReflectorImpl();
    virtual void setTurn(soModuleAccesser* moduleAccesser);
};
