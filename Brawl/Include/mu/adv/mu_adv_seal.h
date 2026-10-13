#pragma once

#include <StaticAssert.h>
#include <gf/gf_archive.h>
#include <gf/gf_task.h>
#include <types.h>

struct muAdvSealTaskParam {
    u32 unk0;
    u32 unk4;
};
static_assert(sizeof(muAdvSealTaskParam) == 0x8, "Size is the wrong size!");

struct muAdvSealTask : public gfTask {
    u32 unk40;

    static void getResourcePackData(const char** ppath, u32* psize);
    static muAdvSealTask* create(const muAdvSealTaskParam* param, gfArchive* arc);
};
// TODO size
