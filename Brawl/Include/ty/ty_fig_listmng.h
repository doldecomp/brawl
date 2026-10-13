#pragma once

#include <StaticAssert.h>
#include <gf/gf_file_io_handle.h>
#include <mt/mt_vector.h>
#include <types.h>

struct tyFigListData {
    s32 id;
    u8 unk4[0x4];
    const char* name; // relocated pointer to a string at data section start
    u32 unkC;
    u8 unk10[0x10];
    s32 series;
    s32 kind;
    Vec3f unk28;
    float unk34;
    float unk38;
    float unk3C;
    u8 unk40[0xC];
    s32 bilTexIdx;
    u8 unk50[0x10];
};
static_assert(sizeof(tyFigListData) == 0x60, "Class is the wrong size!");

struct tyFigListDataManager {
    tyFigListData* m_data; // address of symbol tyDataList in file
    u32 m_count;           // count of items in tyDataList, i.e. 544
    u32 m_bySeries[0x28A]; // trophy IDs in order of increasing series code
    u32 m_byKind[0x28A];   // trophy IDs in order of increasing kind (or type) code
    u32 unk1458;
    u8 m_isLoaded;
    gfFileIOHandle m_fileHandle;
    u8 m_isUnloaded;

    static const u32 TrophiesPerPage = 12;

public:
    tyFigListDataManager(bool loadFile);
    ~tyFigListDataManager();
    bool loadRequest();
    bool isLoadFinish();
    void setData(void* fileBuf, u32 fileSz);
    u32 getFigListSeries(s32 series, u32 pageNum, u32* figList);
    u32 getPageNumSeries(s32 series);
    u32 nextIdSeries(u32 id);
    u32 prevIdSeries(u32 id);
    u32 getFigListKind(s32 kind, u32 pageNum, u32* figList);
    u32 getPageNumKind(s32 kind);
    u32 nextIdKind(u32 id);
    u32 prevIdKind(u32 id);
    u32 getTotalId(u32 id, bool bySeries);
    s32 getBilTexFileIdx(u32 id);
    s32 getBilTexFileIdxFigId(u16 id);
    void getBilTexFileNameFigId(u16 id, char* name);
    void getBilTexName(u32 i, char* name);
    void getBilTexNameFigId(u32 id, char* name);
    tyFigListData* getFigDataId(u32 id);
};
static_assert(sizeof(tyFigListDataManager) == 0x1468, "Class is the wrong size!");
