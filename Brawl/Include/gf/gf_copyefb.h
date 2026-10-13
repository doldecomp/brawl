#pragma once

#include <StaticAssert.h>
#include <memory.h>
#include <types.h>
#include <GX.h>

struct gfCopyEFB {
    char _0[4];
    void* m_texBuffer;
    u32 m_texBufferSize;
    char _12[4];
    GXTexObj m_gxTexObj;
    bool m_isValid;
    char _49[3];
};
static_assert(sizeof(gfCopyEFB) == 52, "Class is wrong size!");

class gfCopyEFBMgr {
public:
    gfCopyEFB m_copyEFBs[2];
    bool m_104;
    char _105[3];
    int m_108;

    void createCopyEFB(int index, HeapType heapType);
    void getEFB(int index);
    void drawCopyEFB(int index, GXColor* color);

    bool isValid(int index);
    GXTexObj* getCopyEFBTex(int index);
    static gfCopyEFBMgr* getInstance();
};
static_assert(sizeof(gfCopyEFBMgr) == 112, "Class is wrong size!");
