#pragma once

#include <StaticAssert.h>
#include <gf/gf_scene.h>
#include <gf/gf_task.h>
#include <mu/wifi/mu_wifi_time_result.h>
#include <types.h>

class scNetTimeResult : public gfScene {
    muWifiTimeResultTask* m_task;
    muWifiTimeResultTaskParam m_taskParam;
public:
    static scNetTimeResult* create();
    scNetTimeResult(const char* name) : gfScene(name) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
};
static_assert(sizeof(scNetTimeResult) == 0x28, "Class is the wrong size!");
