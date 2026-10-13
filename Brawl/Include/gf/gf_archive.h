#pragma once

#include <StaticAssert.h>
#include <gf/gf_file_io_handle.h>
#include <memory.h>
#include <types.h>

enum ARCNodeType {
    Data_Type_None = 0x0,
    Data_Type_Misc = 0x1,
    Data_Type_Model = 0x2,
    Data_Type_Tex = 0x3,
    Data_Type_Anim = 0x4,
    Data_Type_Scene = 0x5,
    Data_Type_6 = 0x6,
    Data_Type_Group = 0x7,
    Data_Type_Effect = 0x8
};

class gfArchiveFileHeader {
    // TODO
    u8 unk0[0x4];
    u16 unk4;
public:
    void* getDataChunk();
};
// TODO size assertion

class gfArchive {
public:
    // 0
    gfArchive* m_prevArchive;
    // 4
    gfArchive* m_nextArchive;
    // 8
    char _spacer[0x1];
    bool unk9 : 1;
    s16 m_refCount; // 0xA
    u8 unkC[0x8];
    // 20
    void* m_Heap;
    // 24
    char _spacer1[0x10];
    // 40
    char m_archiveFilePath[64];
    // 104
    int* m_entries;
    // 108
    gfFileIOHandle* m_requestHandle;
    // 112
    int m_returnStatus;
    // 116
    char _spacer2[4];

    // 120
    gfArchive();
    gfArchive(HeapType heap, int* unk1);
    virtual void notify(int unk1, gfFileIORequest* unk2);
    void* getData(ARCNodeType nodeType, int fileIndex, u16 archiveId);
    void* getData(int groupID, ARCNodeType nodeType, int fileIndex, u16 archiveId);
    void* getData(ARCNodeType nodeType, int fileIndex, int* nodeSize, u16 archiveId);
    void* getData(int groupID, ARCNodeType nodeType, int fileIndex, int* nodeSize, u16 archiveId);
    void setFileImage(void* data, int nodeSize, HeapType heapType);
    void update();
    ~gfArchive();

    // 124
    char _spacer3[4];
};
static_assert(sizeof(gfArchive) == 0x80, "Class is wrong size!");
