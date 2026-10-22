#pragma once

#include <StaticAssert.h>
#include <gf/gf_archive.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <types.h>

// TODO: class size
class utArchiveManager {
public:
    void* getPublicAddress(u32 paramArcId, const char* nodeName, u16 fileIndex, u32 groupID, u32 endian);
    void resolveReference(u32 paramArcId, u32 emCommonArcId, u32 p3, u32 p4, u32 p5, u32 p6);
    nw4r::g3d::ResFileData* getResFileFromId(s32 p1, ARCNodeType type, u32 p3, u32 p4, u32 p5);
};
