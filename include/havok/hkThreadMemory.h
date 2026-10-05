#pragma once

#include <havok/hkMemory.h>

// Per-thread caching front end for hkMemory: size-class free lists plus a chained stack area.
struct hkThreadMemory {
    virtual void setStackArea(void* area, int size);        // 0x08
    virtual void releaseCachedMemory();                     // 0x0C
    virtual ~hkThreadMemory();                              // 0x10
    virtual void* onStackOverflow(int nbytes);              // 0x14
    virtual void onStackUnderflow();                        // 0x18

    hkMemory* m_memory;       // 0x04
    int m_referenceCount;     // 0x08
    int unkC;                 // 0x0C
    char* m_stackTop;         // 0x10
    char* m_stackBlock;       // 0x14
    char* m_stackBase;        // 0x18
    char* m_stackEnd;         // 0x1C
    int m_stackSize;          // 0x20
    int m_maxFreeListSize;    // 0x24
    void* m_freeList[17];     // 0x28
    int m_numFree[17];        // 0x6C
    int m_rowToSize[17];      // 0xB0
    signed char m_sizeToRow[0x201]; // 0xF4
    int m_largeSizeToRow[8];  // 0x2F8

    static hkThreadMemory* s_instance;

    hkThreadMemory(hkMemory* memory, int maxFreeListSize);

    void addReference();
    void removeReference();
    // Stack allocation from the chained stack area (16 byte granularity).
    void* allocateStack(int nbytes) {
        int size = (nbytes + 0x10) & ~0xF;
        char* p = m_stackTop;
        char* next = p + size;
        if (next <= m_stackEnd) {
            m_stackTop = next;
            return p;
        }
        return onStackOverflow(size);
    }
    void deallocateStack(void* p) {
        m_stackTop = (char*)p;
        if (p == m_stackBase) {
            onStackUnderflow();
        }
    }

    void onAllocate();
    void onDeallocate();
    void* allocateChunk(int nbytes, int cl);
    void deallocateChunk(void* p, int nbytes, int cl);
    static void replaceInstance(hkThreadMemory* m);
    static void init();
    static void quit();

    static void operator delete(void* p) {
        g_hkFree(p);
    }
};
