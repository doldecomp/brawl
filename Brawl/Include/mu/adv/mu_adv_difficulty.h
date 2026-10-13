#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <types.h>

struct muAdvDifficultyTaskParam {
    u32 unk0;
    u32 unk4;
    u32 unk8;
};
static_assert(sizeof(muAdvDifficultyTaskParam) == 0xC, "Class is the wrong size!");

class muAdvDifficultyTask : public gfTask {
public:
    u32 m_option;
    u8 unk44[0x8];
    u32 m_difficulty;

    static muAdvDifficultyTask* create(const muAdvDifficultyTaskParam* p1);
};
// TODO size
