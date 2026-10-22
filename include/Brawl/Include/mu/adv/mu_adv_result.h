#pragma once

#include <StaticAssert.h>
#include <ad/ad_list.h>
#include <gf/gf_task.h>
#include <sr/sr_common.h>
#include <types.h>

struct muAdvResultTaskParam {
    u32 m_mainPlayerPort;
    u32 m_earnedCoinsForClear;
    u32 m_scoreInCurrentStage;
    u32 m_totalScore;
    adList<u32, Heaps::MenuInstance>* unk10;
    adList<u32, Heaps::MenuInstance>* unk14;
    adList<u32, Heaps::MenuInstance>* unk18;
};
static_assert(sizeof(muAdvResultTaskParam) == 0x1C, "Size is the wrong size!");

struct muAdvResultTask : public gfTask {
    u32 unk40;
    u8 unk44[0x560];
    bool unk5A4;

    static muAdvResultTask* create(const muAdvResultTaskParam* param);
};
// TODO size
