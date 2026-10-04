#pragma once

#include <so/status/so_status_module_impl.h>
#include <types.h>

class soModuleAccesser;

// Status process for the ledge statuses (Cliff_Catch .. Cliff_Jump1, 0x74-0x79).
class ftStatusUniqProcessCliff : public soStatusUniqProcess {
public:
    virtual ~ftStatusUniqProcessCliff() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual bool isLeaveCliff(int status);

    static bool isLeaveCliffStatus(int status);
};
