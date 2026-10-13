#pragma once

#include <StaticAssert.h>
#include <gf/gf_archive.h>
#include <nw4r/ut/ut_LinkList.h>

class gfArchiveManager {
    nw4r::ut::LinkList<gfArchive, 0> m_archives;
    nw4r::ut::LinkList<gfArchive, 0> m_unused;
public:
    gfArchiveManager() { }
    void update();
    void pushback(gfArchive* arc);
    void remove(gfArchive* arc);
    static void create();
};
static_assert(sizeof(gfArchiveManager) == 0x18, "Class is the wrong size!");

extern gfArchiveManager* g_gfArchiveManager;
