#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <types.h>

class tySealListTask : public gfTask {
public:
    u8 unk40[0x4];
    s32 unk44;
    u8 unk48[0x53D0];

    tySealListTask();
};
static_assert(sizeof(tySealListTask) == 0x5418, "Class is the wrong size!");
