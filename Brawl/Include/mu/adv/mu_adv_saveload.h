#pragma once

#include <StaticAssert.h>
#include <ad/ad_list.h>
#include <gf/gf_task.h>
#include <sr/sr_common.h>
#include <types.h>

struct muAdvSaveTaskParam {
    u8 unk0;
    u32 unk4;
};
static_assert(sizeof(muAdvSaveTaskParam) == 0x8, "Size is the wrong size!");

struct muAdvSaveTask : public gfTask {
    u32 unk40;
    u8 unk44[0x174];
    s32 unk1B8;
    u8 unk1BC[0x3E8];
    bool unk5A4;

    // TODO: type of p3
    static muAdvSaveTask* create(const muAdvSaveTaskParam* param, Heaps::HeapType p2, u32 p3);
};
// TODO size

struct muAdvLoadTaskParam {
    u8 unk0;
    u32 unk4;
};
static_assert(sizeof(muAdvLoadTaskParam) == 0x8, "Size is the wrong size!");

struct muAdvLoadTask : public gfTask {
    u32 unk40;
    u8 unk44[0x174];
    s32 unk1B8;
    u8 unk1BC[0x3E8];
    bool unk5A4;

    s32 isLoaded() const;
    static muAdvLoadTask* create(const muAdvLoadTaskParam* param);
};
// TODO size
