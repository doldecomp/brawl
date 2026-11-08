#pragma once

#include <StaticAssert.h>
#include <ut/ut_archive_manager.h>

// TODO: class size
class soArchiveDb {
public:
    static bool create(u32 index, u32 numArchives);
    static void remove(u32 index);
    static utArchiveManager* getManager(u32 index);
};
