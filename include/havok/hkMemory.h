#pragma once

#include <havok/hkBase.h>

// Allocation classes (HK_MEMORY_CLASS_*), values observed in allocation calls.
enum {
    HK_MEMORY_CLASS_BASE = 0x16,
    HK_MEMORY_CLASS_STREAM = 0x18,
};

extern void* (*g_hkMalloc)(int size, int alignment);
extern void (*g_hkFree)(void* p);

// Abstract allocator interface (vtable has no destructor in slot 2: layout is
// allocate*, chunk*, runtime blocks, statistics, then the destructor last).
struct hkMemory {
    hkMemory();

    virtual void* allocate(int nbytes, int cl) = 0;                     // 0x08
    virtual void deallocate(void* p) = 0;                               // 0x0C
    virtual void* alignedAllocate(int alignment, int nbytes, int cl) = 0; // 0x10
    virtual void alignedDeallocate(void* p) = 0;                        // 0x14
    virtual void* allocateChunk(int nbytes, int cl) = 0;                // 0x18
    virtual void deallocateChunk(void* p, int nbytes, int cl) = 0;      // 0x1C
    virtual void* allocateChunkByRow(int row, int cl);                  // 0x20
    virtual void deallocateChunkByRow(void* p, int row, int cl);        // 0x24
    virtual bool isAllocateChunkByRowSupported();                       // 0x28
    virtual void* allocateRuntimeBlock(int nbytes, int cl) = 0;         // 0x2C
    virtual void deallocateRuntimeBlock(void* p, int nbytes, int cl) = 0; // 0x30
    virtual void preAllocateRuntimeBlock(int nbytes, int cl) = 0;       // 0x34
    virtual void provideRuntimeBlock(void* p, int nbytes, int cl) = 0;  // 0x38
    virtual void freeRuntimeBlocks() = 0;                               // 0x3C
    virtual void printStatistics(struct hkOstream* os) = 0;             // 0x40
    virtual int getAllocatedSize(int nbytes);                           // 0x44
    virtual void getStatSynopsis(int* stats) = 0;                       // 0x48
    virtual hkBool isOk() const;                                        // 0x4C
    virtual ~hkMemory() {}                                              // 0x50

    int unk4;             // 0x04
    int unk8;             // 0x08
    int m_referenceCount; // 0x0C
    int m_stats[7];       // 0x10..0x2C

    static hkMemory* s_instance;
    static hkMemory& getInstance() {
        return *s_instance;
    }
    static void replaceInstance(hkMemory* m);
};

// Class-specific allocation for reference counted objects: the allocation size is stashed in
// m_memSizeAndFlags so deletion can hand it back to the allocator.
#define HK_DECLARE_REF_ALLOCATOR(CLS)                                                        \
    static void* operator new(unsigned long nbytes) {                                          \
        hkReferencedObject* p =                                                                \
            (hkReferencedObject*)hkMemory::getInstance().allocateChunk(nbytes, CLS);           \
        p->m_memSizeAndFlags = nbytes;                                                         \
        return p;                                                                              \
    }                                                                                          \
    static void operator delete(void* p) {                                                     \
        hkMemory::getInstance().deallocateChunk(                                               \
            p, ((hkReferencedObject*)p)->m_memSizeAndFlags, CLS);                              \
    }

void* hkRevolutionMalloc(int size, int alignment);
void hkRevolutionFree(void* p);
