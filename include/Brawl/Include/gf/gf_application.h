#pragma once

#include <StaticAssert.h>
#include <gf/gf_callback.h>
#include <gf/gf_keep_fb.h>
#include <types.h>

struct vcBootParam {
    u8 unk0[0x54];
    void init(int argc, const char* argv[]);
};
// TODO size assertion

class gfApplication;
extern gfApplication* g_gfApplication;
class gfApplication {
public:
    u8 unk0[0xD0];
    gfKeepFrameBuffer unkD0;
    u8 unkD1[0x13];
    int m_e4;
    u8 unkE8[0x10];
    u16 m_frameRate;
    u8 unkFA[0x1A];
    gfCallBackList m_114;
    u8 unk118[0x4];
    vcBootParam m_bootParam;

    gfApplication();
    ~gfApplication();
    void init();
    void reset();
    void restart();
    void mainLoop();
    void exit();

    inline static gfApplication* getInstance() { return g_gfApplication; }
};
static_assert(sizeof(gfApplication) == 0x170, "Class is wrong size!");

