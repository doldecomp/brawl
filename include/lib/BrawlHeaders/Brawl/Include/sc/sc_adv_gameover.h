#pragma once

#include <ad/ad_list.h>
#include <StaticAssert.h>
#include <ad/ad_autosave.h>
#include <gf/gf_scene.h>
#include <mu/adv/mu_adv_game_over.h>
#include <sr/sr_common.h>
#include <types.h>

class scAdvGameover : public gfScene {
    muAdvGameOverTask* m_task;
    bool unkC;
    adList<u32, Heaps::MenuInstance> unk10;
    adList<u32, Heaps::MenuInstance> unk24;
    adList<u32, Heaps::MenuInstance> unk38;
    adList<u32, Heaps::MenuInstance> unk4C;
    adList<u32, Heaps::MenuInstance> unk60;
    adList<u32, Heaps::MenuInstance> unk74;
public:
    static scAdvGameover* create();
    scAdvGameover(const char* name) : gfScene(name), m_task(nullptr), unkC(true) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
};
static_assert(sizeof(scAdvGameover) == 0x88, "Class is the wrong size!");
