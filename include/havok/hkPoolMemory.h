#pragma once

#include <havok/hkMemory.h>

// Size-class pool allocator layered over the system allocator (g_hkMalloc / g_hkFree).
struct hkPoolMemory : hkMemory {
    struct RuntimeBlock {
        char m_free;     // 0x00
        int m_size;      // 0x04
        void* m_ptr;     // 0x08
        int m_class;     // 0x0C
        char m_provided; // 0x10
    };

    int m_numRuntimeBlocks;         // 0x2C
    RuntimeBlock m_blocks[128];     // 0x30
    void* m_blockHead;              // 0xA30
    void* m_blockStart;             // 0xA34
    char* m_blockEnd;               // 0xA38
    char* m_blockCur;               // 0xA3C
    int unkA40;                     // 0xA40
    void* m_freeList[17];           // 0xA44
    int m_rowToSize[17];            // 0xA88
    signed char m_sizeToRow[0x201]; // 0xACC
    int m_largeSizeToRow[8];        // 0xCD0
    int m_numFree[17];              // 0xCF0

    static void operator delete(void* p) {
        g_hkFree(p);
    }

    hkPoolMemory();
    virtual ~hkPoolMemory();

    virtual int getAllocatedSize(int nbytes);
    virtual void printStatistics(hkOstream* os);
    virtual void* allocate(int nbytes, int cl);
    virtual void deallocate(void* p);
    virtual void* alignedAllocate(int alignment, int nbytes, int cl);
    virtual void alignedDeallocate(void* p);
    virtual void* allocateChunk(int nbytes, int cl);
    virtual void* allocateChunkByRow(int row, int cl);
    virtual void deallocateChunk(void* p, int nbytes, int cl);
    virtual void deallocateChunkByRow(void* p, int row, int cl);
    virtual void getStatSynopsis(int* stats);
    virtual bool isAllocateChunkByRowSupported();
    virtual void preAllocateRuntimeBlock(int nbytes, int cl);
    virtual void freeRuntimeBlocks();
    virtual void* allocateRuntimeBlock(int nbytes, int cl);
    virtual void deallocateRuntimeBlock(void* p, int nbytes, int cl);
    virtual void provideRuntimeBlock(void* p, int nbytes, int cl);
};
