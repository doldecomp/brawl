#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <types.h>

struct muAdvNameTaskParam {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};
static_assert(sizeof(muAdvNameTaskParam) == 0x10, "Class is the wrong size!");

class muAdvNameTask : public gfTask {
public:
    static muAdvNameTask* create(const muAdvNameTaskParam* p1);
};
// TODO size
