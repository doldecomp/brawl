#pragma once

#include <StaticAssert.h>
#include <gf/gf_scene.h>
#include <ty/ty_seal_list.h>
#include <types.h>

class scSealList : public gfScene {
    tySealListTask* m_task;
public:
    static scSealList* create();
    scSealList(const char* name) : gfScene(name) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
};
static_assert(sizeof(scSealList) == 0xC, "Class is the wrong size!");
