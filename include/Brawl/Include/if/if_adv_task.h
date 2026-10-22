#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>

class ifAdvTask : public gfTask {
    u32 m_state;
public:
    ifAdvTask() : gfTask(TaskName, Category_Info, 14, 6, true), m_state(0) { }
    virtual void processDefault();
    virtual void renderPre();
    virtual ~ifAdvTask();

    static ifAdvTask* create();
    static char TaskName[];
};
static_assert(sizeof(ifAdvTask) == 0x44, "Class is the wrong size!");
