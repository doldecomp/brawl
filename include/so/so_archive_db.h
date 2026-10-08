#pragma once

// Local shadow of BrawlHeaders' so/so_archive_db.h: the original plus create (the map names fn_27_6FCF4
// soArchiveDb::create; the fighter manager constructor creates archive 0 with 0x60).

#include <StaticAssert.h>
#include <ut/ut_archive_manager.h>

// TODO: class size
class soArchiveDb {
public:
    static utArchiveManager* getManager(u32 index);
    static bool create(u32 index, u32 size);
};
