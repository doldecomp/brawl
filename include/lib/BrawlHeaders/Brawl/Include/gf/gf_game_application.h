#pragma once

#include <StaticAssert.h>
#include <gf/gf_keep_fb.h>
#include <gf/gf_task.h>

class gfGameApplication {
public:
    char unk[0xD0];
    gfKeepFrameBuffer keepFB;
    gfGameApplication();
};