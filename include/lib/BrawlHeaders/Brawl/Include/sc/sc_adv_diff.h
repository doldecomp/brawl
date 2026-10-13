#pragma once

#include <StaticAssert.h>
#include <gf/gf_file_io_handle.h>
#include <gf/gf_scene.h>
#include <mu/adv/mu_adv_difficulty.h>
#include <types.h>

class scAdvDiff : public gfScene {
    muAdvDifficultyTask* m_task;
public:
    static scAdvDiff* create();
    scAdvDiff(const char* name) : gfScene(name), m_task(nullptr) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
};
static_assert(sizeof(scAdvDiff) == 0xC, "Class is the wrong size!");
