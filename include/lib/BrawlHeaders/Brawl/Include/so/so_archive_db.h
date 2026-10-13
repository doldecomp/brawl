#pragma once

#include <StaticAssert.h>
#include <ut/ut_archive_manager.h>

// TODO: class size
class soArchiveDb {
public:
    static utArchiveManager* getManager(u32 index);
};
