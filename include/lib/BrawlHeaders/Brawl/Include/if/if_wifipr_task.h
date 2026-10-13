#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>

class ifWifiprTask : public gfTask {
public:
    ifWifiprTask() : gfTask(TaskName, Category_Info, 14, 6, true) { }
    virtual void processDefault();
    virtual ~ifWifiprTask();

    static ifWifiprTask* create();
    static char TaskName[];
};
static_assert(sizeof(ifWifiprTask) == 0x40, "Class is the wrong size!");
