#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>

class muWifiInterfaceTask : public gfTask {
    char _0x40[0x1018];

public:
    virtual void processDefault();
    virtual ~muWifiInterfaceTask();
    virtual void exit();

    void connect(bool);
    static muWifiInterfaceTask* create();

};
static_assert(sizeof(muWifiInterfaceTask) == 0x1058, "Class is wrong size!");

void netReport(const char* fmt, ...);
void netReport0(const char* fmt, ...);

extern muWifiInterfaceTask* g_muWifiInterfaceTask;
