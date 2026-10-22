#pragma once

#include <StaticAssert.h>
#include <ad/ad_list.h>
#include <gf/gf_task.h>
#include <if/if_utility.h>
#include <sr/sr_common.h>
#include <types.h>

struct muAdvGameOverTaskParam {
    bool unk0;
    u32 unk4;
    adList<u32, Heaps::MenuInstance>* unk8;
    adList<u32, Heaps::MenuInstance>* unkC;
    adList<u32, Heaps::MenuInstance>* unk10;
    adList<u32, Heaps::MenuInstance>* unk14;
    adList<u32, Heaps::MenuInstance>* unk18;
    adList<u32, Heaps::MenuInstance>* unk1C;
};
static_assert(sizeof(muAdvGameOverTaskParam) == 0x20, "Size is the wrong size!");

struct muAdvGameOverTask : public utility::StandardMenu {
    u8 unk40[0x16C];
    s32 unk1AC;

    virtual ~muAdvGameOverTask();
    virtual bool preLoad();
    virtual void loadResource();
    virtual bool checkLoadFinish() const;
    virtual void createModel();
    virtual void update();

    s32 getSelection() const;

    static muAdvGameOverTask* create(const muAdvGameOverTaskParam* param);
};
// TODO size
