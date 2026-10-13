#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <types.h>

struct muWifiTimeResultTaskParam {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u32 unk18;

    muWifiTimeResultTaskParam() {
        unk0 = 0;
        unk4 = 0;
        unk8 = 0;
        unkC = 0;
        unk10 = 0;
        unk14 = 0;
        unk18 = 0;
    }
};
static_assert(sizeof(muWifiTimeResultTaskParam) == 0x1C, "Class is the wrong size!");

class muWifiTimeResultTask : public gfTask {
public:
    static muWifiTimeResultTask* create(const muWifiTimeResultTaskParam* p1);
};
// TODO size
