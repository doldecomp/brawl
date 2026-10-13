#pragma once

#include <StaticAssert.h>
#include <gf/gf_file_io_handle.h>
#include <gf/gf_scene.h>
#include <mu/adv/mu_adv_name.h>
#include <types.h>

class scAdvName : public gfScene {
    muAdvNameTask* unk8;
    u32 unkC;
    u32 unk10;
    gfFileIOHandle unk14;
    u32 unk18;
    s32 unk1C;
public:
    static scAdvName* create();
    scAdvName(const char* name) : gfScene(name), unk8(nullptr), unkC(0),
            unk10(0), unk18(0) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
};
static_assert(sizeof(scAdvName) == 0x1C, "Class is the wrong size!");
