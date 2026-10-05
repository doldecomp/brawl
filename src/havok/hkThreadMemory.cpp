#include <havok/hkThreadMemory.h>

static inline int getRow(int size) {
    int row;
    if (size <= 8) {
        row = 1;
    } else if (size <= 0x10) {
        row = 2;
    } else if (size <= 0x20) {
        row = 3;
    } else if (size <= 0x30) {
        row = 4;
    } else if (size <= 0x40) {
        row = 5;
    } else if (size <= 0x60) {
        row = 6;
    } else if (size <= 0x80) {
        row = 7;
    } else if (size <= 0xA0) {
        row = 8;
    } else if (size <= 0xC0) {
        row = 9;
    } else if (size <= 0x100) {
        row = 10;
    } else if (size <= 0x140) {
        row = 11;
    } else if (size <= 0x200) {
        row = 12;
    } else if (size <= 0x400) {
        row = 13;
    } else if (size <= 0x800) {
        row = 14;
    } else if (size <= 0x1000) {
        row = 15;
    } else if (size <= 0x2000) {
        row = 16;
    } else {
        *(int*)0 = 0;
        row = -1;
    }
    return row;
}

// MATCH-ONLY: the original loops are not unrolled
#pragma opt_unroll_loops off
hkThreadMemory::hkThreadMemory(hkMemory* memory, int maxFreeListSize) {
    m_referenceCount = 1;
    m_stackTop = 0;
    m_stackBlock = 0;
    m_stackBase = (char*)-1;
    m_stackEnd = 0;
    m_memory = memory;
    if (memory->isAllocateChunkByRowSupported()) {
        m_maxFreeListSize = maxFreeListSize;
    } else {
        m_maxFreeListSize = 0;
    }
    for (int i = 16; i >= 0; i--) {
        m_freeList[i] = 0;
        m_numFree[i] = 0;
    }
    for (int size = 0; size < 0x201; size++) {
        int row = getRow(size);
        m_sizeToRow[size] = row;
        m_rowToSize[row] = size;
    }
    for (int k = 0; k < 8; k++) {
        int size = (k + 1) << 10;
        int row = getRow(size);
        m_largeSizeToRow[k] = row;
        m_rowToSize[row] = size;
    }
}
#pragma opt_unroll_loops reset

void hkThreadMemory::releaseCachedMemory() {
    for (int i = 16; i >= 0; i--) {
        while (m_freeList[i] != 0) {
            void* p = m_freeList[i];
            m_freeList[i] = *(void**)p;
            m_memory->deallocateChunkByRow(p, i, 1);
        }
        m_freeList[i] = 0;
        m_numFree[i] = 0;
    }
}

hkThreadMemory::~hkThreadMemory() {
    releaseCachedMemory();
}

#pragma dont_inline on
void hkThreadMemory::removeReference() {
    if (--m_referenceCount == 0) {
        delete this;
    }
}

void hkThreadMemory::addReference() {
    m_referenceCount++;
}

void* hkThreadMemory::allocateChunk(int nbytes, int cl) {
    if (nbytes <= 0x2000 && m_maxFreeListSize != 0) {
        int row;
        if (nbytes <= 0x200) {
            row = m_sizeToRow[nbytes];
        } else {
            row = m_largeSizeToRow[(nbytes - 1) >> 10];
        }
        void* p = m_freeList[row];
        if (p != 0) {
            m_numFree[row]--;
            m_freeList[row] = *(void**)p;
            return p;
        }
        return m_memory->allocateChunkByRow(row, cl);
    }
    return m_memory->allocateChunk(nbytes, cl);
}

void hkThreadMemory::onAllocate() {}

void hkThreadMemory::deallocateChunk(void* p, int nbytes, int cl) {
    if (nbytes <= 0x2000 && m_maxFreeListSize != 0) {
        int row;
        if (nbytes <= 0x200) {
            row = m_sizeToRow[nbytes];
        } else {
            row = m_largeSizeToRow[(nbytes - 1) >> 10];
        }
        if (m_numFree[row] < m_maxFreeListSize) {
            m_numFree[row]++;
            *(void**)p = m_freeList[row];
            m_freeList[row] = p;
            return;
        }
        m_memory->deallocateChunkByRow(p, row, cl);
        return;
    }
    m_memory->deallocateChunk(p, nbytes, cl);
}

void hkThreadMemory::onDeallocate() {}
#pragma dont_inline reset

void* hkThreadMemory::onStackOverflow(int nbytes) {
    int size = nbytes + 0x400;
    if (size <= 0x1000) {
        size = 0x1000;
    }
    char* block = (char*)s_instance->allocateChunk(size + 0x10, 0x15);
    char* base = block + 0x10;
    ((char**)block)[0] = m_stackTop;
    ((char**)block)[1] = m_stackBlock;
    ((char**)block)[2] = m_stackBase;
    ((char**)block)[3] = m_stackEnd;
    m_stackBlock = block;
    m_stackBase = base;
    m_stackTop = base + nbytes;
    m_stackEnd = base + size;
    return base;
}

void hkThreadMemory::onStackUnderflow() {
    char* base = m_stackBase;
    char* block = base - 0x10;
    int total = m_stackEnd - base + 0x10;
    m_stackTop = ((char**)block)[0];
    m_stackBlock = ((char**)block)[1];
    m_stackBase = ((char**)block)[2];
    m_stackEnd = ((char**)block)[3];
    deallocateChunk(block, total, 0x15);
}

void hkThreadMemory::setStackArea(void* area, int size) {
    m_stackBase = (char*)-1;
    m_stackSize = size;
    int misalign = (unsigned)area & 0xF;
    if (misalign != 0) {
        char* aligned = (char*)area + 0x10 - misalign;
        m_stackTop = aligned;
        m_stackEnd = aligned + (size - misalign);
    } else {
        m_stackTop = (char*)area;
        m_stackEnd = (char*)area + size;
    }
}

void hkThreadMemory::replaceInstance(hkThreadMemory* m) {
    if (m) {
        m->addReference();
    }
    if (s_instance) {
        s_instance->removeReference();
    }
    s_instance = m;
}

void hkThreadMemory::init() {}

void hkThreadMemory::quit() {}
