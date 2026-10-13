#pragma once

#include <StaticAssert.h>
#include <ad/ad_list.h>
#include <gf/gf_scene.h>
#include <mu/adv/mu_adv_result.h>
#include <sr/sr_common.h>
#include <types.h>

class scAdvResult : public gfScene {
    muAdvResultTask* m_task;
    u32 m_mainPlayerPort;
    u32 m_earnedCoinsForClear;
    u32 m_scoreInCurrentStage;
    u32 m_totalScore;
    u32 unk1C;
    adList<u32, Heaps::MenuInstance> unk20;
    adList<u32, Heaps::MenuInstance> unk34;
    adList<u32, Heaps::MenuInstance> unk48;
public:
    static scAdvResult* create();
    scAdvResult(const char* name) : gfScene(name), m_task(nullptr),
            m_mainPlayerPort(0), m_earnedCoinsForClear(0),
            m_scoreInCurrentStage(0), m_totalScore(0), unk1C(0) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
};
static_assert(sizeof(scAdvResult) == 0x5C, "Class is the wrong size!");
