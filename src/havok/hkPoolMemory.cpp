#include <havok/hkError.h>
#include <havok/hkIostream.h>
#include <havok/hkPoolMemory.h>
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

int hkPoolMemory::getAllocatedSize(int nbytes) {
    if (nbytes <= 0x2000) {
        int row;
        if (nbytes <= 0x200) {
            row = m_sizeToRow[nbytes];
        } else {
            row = m_largeSizeToRow[(nbytes - 1) >> 10];
        }
        return m_rowToSize[row];
    }
    return hkMemory::getAllocatedSize(nbytes);
}

hkPoolMemory::hkPoolMemory() {
    m_blockStart = 0;
    m_blockEnd = 0;
    m_blockCur = 0;
    m_blockHead = 0;
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
    m_stats[0] = 0;
    m_stats[1] = 0;
    m_stats[2] = 0;
    m_stats[3] = 0;
    m_stats[4] = 0x2000;
    m_stats[5] = 0x40;
    m_stats[6] = 0;
    m_numRuntimeBlocks = 0;
}

hkPoolMemory::~hkPoolMemory() {
    freeRuntimeBlocks();
    while (m_blockHead != 0) {
        void* head = m_blockHead;
        m_blockHead = *(void**)head;
        g_hkFree(head);
    }
}

void hkPoolMemory::printStatistics(hkOstream* os) {
    os->printf("Statistics are disabled, please enable them in hkbase/config/hkConfigMemoryStats.h\n");
}

void* hkPoolMemory::allocate(int nbytes, int cl) {
    int* p = (int*)allocateChunk(nbytes + 0x10, cl);
    p[0] = 0x2345656;
    p[1] = nbytes;
    p[2] = cl;
    return p + 4;
}

void hkPoolMemory::deallocate(void* p) {
    if (p != 0) {
        int* h = (int*)p - 4;
        h[0] = 0xDEADBEEF;
        deallocateChunk(h, h[1] + 0x10, h[2]);
    }
}

void* hkPoolMemory::alignedAllocate(int alignment, int nbytes, int cl) {
    int total = alignment + nbytes;
    char* raw = (char*)allocateChunk(total + 0x10, cl);
    char* aligned = (char*)((alignment + (unsigned)raw + 0xF) & ~(alignment - 1));
    int* h = (int*)aligned - 4;
    h[0] = 0x2345656;
    h[1] = total;
    h[2] = cl;
    h[3] = aligned - raw;
    return aligned;
}

void hkPoolMemory::alignedDeallocate(void* p) {
    if (p != 0) {
        int* h = (int*)p - 4;
        int size = h[1] + 0x10;
        int offset = h[3];
        h[0] = 0xDEADBEEF;
        deallocateChunk((char*)p - offset, size, h[2]);
    }
}

// Row allocation shared (by duplication) between allocateChunk and allocateChunkByRow.
#define ALLOC_FROM_ROW(row, p) \
    m_numFree[row]++; \
    m_stats[6] += m_rowToSize[row]; \
    p = m_freeList[row]; \
    if (p == 0) { \
        if (row < 13) { \
            int sz = m_rowToSize[row]; \
            if (m_blockEnd < m_blockCur + sz) { \
                char* blk = (char*)g_hkMalloc(0x2040, 0x40); \
                *(void**)blk = m_blockHead; \
                m_blockHead = blk; \
                m_blockStart = blk + 0x40; \
                m_blockCur = blk + 0x40; \
                m_blockEnd = blk + 0x2040; \
                m_stats[3]++; \
            } \
            p = m_blockCur; \
            m_blockCur += sz; \
            int saved = m_numFree[row]; \
            int accum = sz; \
            while (accum < 0x200 && m_blockCur + sz < m_blockEnd) { \
                void* q = m_blockCur; \
                m_numFree[row]--; \
                *(void**)q = m_freeList[row]; \
                m_freeList[row] = q; \
                accum += sz; \
                m_blockCur += sz; \
            } \
            m_numFree[row] = saved; \
        } else { \
            int sz = m_rowToSize[row]; \
            char* blk = (char*)g_hkMalloc(0x2040, 0x40); \
            if (m_blockHead == 0) { \
                *(void**)blk = 0; \
                m_blockHead = blk; \
            } else { \
                *(void**)blk = *(void**)m_blockHead; \
                *(void**)m_blockHead = blk; \
            } \
            p = blk + 0x40; \
            m_stats[3]++; \
            int saved = m_numFree[row]; \
            int accum = sz; \
            char* q = (char*)p; \
            while (q += sz, accum < 0x2000) { \
                m_numFree[row]--; \
                *(void**)q = m_freeList[row]; \
                accum += sz; \
                m_freeList[row] = q; \
            } \
            m_numFree[row] = saved; \
        } \
    } else { \
        m_freeList[row] = *(void**)p; \
    }

void* hkPoolMemory::allocateChunk(int nbytes, int cl) {
    if (nbytes <= 0x2000) {
        int row;
        if (nbytes <= 0x200) {
            row = m_sizeToRow[nbytes];
        } else {
            row = m_largeSizeToRow[(nbytes - 1) >> 10];
        }
        void* p;
        ALLOC_FROM_ROW(row, p);
        return p;
    }
    m_stats[0]++;
    m_stats[1] += nbytes;
    if (m_stats[2] < m_stats[1]) {
        m_stats[2] = m_stats[1];
    }
    return g_hkMalloc(nbytes, 0x40);
}

void* hkPoolMemory::allocateChunkByRow(int row, int cl) {
    void* p;
    ALLOC_FROM_ROW(row, p);
    return p;
}

void hkPoolMemory::deallocateChunk(void* p, int nbytes, int cl) {
    if (p == 0) {
        return;
    }
    if (nbytes <= 0x2000) {
        int row;
        if (nbytes <= 0x200) {
            row = m_sizeToRow[nbytes];
        } else {
            row = m_largeSizeToRow[(nbytes - 1) >> 10];
        }
        m_stats[6] -= m_rowToSize[row];
        m_numFree[row]--;
        *(void**)p = m_freeList[row];
        m_freeList[row] = p;
        return;
    }
    m_stats[1] -= nbytes;
    g_hkFree(p);
}

void hkPoolMemory::deallocateChunkByRow(void* p, int row, int cl) {
    m_stats[6] -= m_rowToSize[row];
    m_numFree[row]--;
    *(void**)p = m_freeList[row];
    m_freeList[row] = p;
}

void hkPoolMemory::getStatSynopsis(int* stats) {
    stats[0] = m_stats[0];
    stats[1] = m_stats[1];
    stats[2] = m_stats[2];
    stats[3] = m_stats[3];
    stats[4] = m_stats[4];
    stats[5] = m_stats[5];
    stats[6] = m_stats[6];
}

bool hkPoolMemory::isAllocateChunkByRowSupported() {
    return true;
}

void hkPoolMemory::preAllocateRuntimeBlock(int nbytes, int cl) {
    int i = m_numRuntimeBlocks++;
    m_blocks[i].m_free = 1;
    m_blocks[i].m_size = nbytes;
    m_blocks[i].m_ptr = allocateChunk(nbytes, cl);
    m_blocks[i].m_class = cl;
    m_blocks[i].m_provided = 0;
}

void hkPoolMemory::freeRuntimeBlocks() {
    for (int i = 0; i < m_numRuntimeBlocks; i++) {
        if (!m_blocks[i].m_provided) {
            deallocateChunk(m_blocks[i].m_ptr, m_blocks[i].m_size, m_blocks[i].m_class);
        }
    }
    m_numRuntimeBlocks = 0;
}

void* hkPoolMemory::allocateRuntimeBlock(int nbytes, int cl) {
    if (nbytes < 0x2000) {
        return hkThreadMemory::s_instance->allocateChunk(nbytes, cl);
    }
    int numBlocks = m_numRuntimeBlocks;
    RuntimeBlock* best = 0;
    for (int i = 0; i < numBlocks; i++) {
        RuntimeBlock* b = &m_blocks[i];
        bool fits = false;
        if (b->m_free == 1 && nbytes <= b->m_size) {
            fits = true;
        }
        if (fits) {
            if (best == 0 || b->m_size < best->m_size) {
                best = b;
            }
        }
    }
    if (best == 0) {
        int alloc = 1;
        for (int n = nbytes + 0x40; n > 0; n >>= 1) {
            alloc *= 2;
        }
        if (numBlocks < 0x80) {
            char buf[0x200];
            hkBool isString(true);
            hkOstream os(buf, 0x200, isString);
            os << "No block of size " << nbytes
               << " currently available. Allocating new block from system memory.";
            hkError::getInstance().message(1, 0xAF55ADDE, buf, "hkPoolMemory.cpp", 779);
            int i = m_numRuntimeBlocks++;
            m_blocks[i].m_free = 0;
            m_blocks[i].m_size = alloc - 0x40;
            m_blocks[i].m_ptr = allocateChunk(alloc - 0x40, cl);
            m_blocks[i].m_class = cl;
            m_blocks[i].m_provided = 0;
            return m_blocks[i].m_ptr;
        }
        char buf[0x200];
        hkBool isString(true);
        hkOstream os(buf, 0x200, isString);
        os << "No block of size " << nbytes
           << " currently available and out of big block memory slots. Allocating unmanaged system memory.";
        hkError::getInstance().message(1, 0xAF55ADDE, buf, "hkPoolMemory.cpp", 792);
        return allocateChunk(nbytes, cl);
    }
    best->m_free = 0;
    return best->m_ptr;
}

void hkPoolMemory::deallocateRuntimeBlock(void* p, int nbytes, int cl) {
    if (nbytes < 0x2000) {
        hkThreadMemory::s_instance->deallocateChunk(p, nbytes, cl);
        return;
    }
    int numBlocks = m_numRuntimeBlocks;
    RuntimeBlock* b = &m_blocks[0];
    for (int i = 0; i < numBlocks; i++, b++) {
        if (b->m_ptr == p) {
            b->m_free = 1;
            return;
        }
    }
    char buf[0x200];
    hkBool isString(true);
    hkOstream os(buf, 0x200, isString);
    os << "Deallocating unmanaged big block.";
    hkError::getInstance().message(1, 0xAF55ADDF, buf, "hkPoolMemory.cpp", 820);
    deallocateChunk(p, nbytes, cl);
}

void hkPoolMemory::provideRuntimeBlock(void* p, int nbytes, int cl) {
    int i = m_numRuntimeBlocks++;
    m_blocks[i].m_free = 1;
    m_blocks[i].m_size = nbytes;
    m_blocks[i].m_ptr = p;
    m_blocks[i].m_class = cl;
    m_blocks[i].m_provided = 1;
}
