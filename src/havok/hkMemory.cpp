#include <havok/hkMemory.h>
#include <havok/hkThreadMemory.h>
#include <revolution/MEM.h>

extern MEMAllocator g_hkRevolutionAllocator;

void* hkRevolutionMalloc(int size, int alignment);
void hkRevolutionFree(void* p);

void* (*g_hkMalloc)(int size, int alignment) = hkRevolutionMalloc;
void (*g_hkFree)(void* p) = hkRevolutionFree;

hkMemory::hkMemory() {
    m_referenceCount = 1;
    unk10[0] = 0;
    unk10[1] = 0;
    unk10[2] = 0;
    unk10[3] = 0;
    unk10[4] = 0;
    unk10[5] = 0;
    unk10[6] = 0;
    unk4 = 0;
    unk8 = 0x7FFFFFFF;
}

void* hkRevolutionMalloc(int size, int alignment) {
    char* raw = (char*)MEMAllocFromAllocator(&g_hkRevolutionAllocator, size + alignment);
    char* aligned = (char*)((alignment + (unsigned)raw) & ~(alignment - 1));
    *(int*)(aligned - 4) = aligned - raw;
    return aligned;
}

void hkRevolutionFree(void* p) {
    MEMFreeToAllocator(&g_hkRevolutionAllocator, (char*)p - *(int*)((char*)p - 4));
}

void hkMemory::replaceInstance(hkMemory* m) {
    if (m) {
        m->m_referenceCount++;
    }
    hkMemory* old = s_instance;
    if (old && --old->m_referenceCount == 0) {
        delete old;
    }
    s_instance = m;
}

int hkMemory::getAllocatedSize(int nbytes) {
    if (nbytes <= 0x10) {
        return nbytes + 8;
    }
    return ((nbytes + 0xF) & ~0xF) + 0x10;
}

hkBool hkMemory::isOk() const {
    return hkBool(true);
}

void* hkMemory::allocateChunkByRow(int row, int cl) {
    return allocateChunk(hkThreadMemory::s_instance->m_rowToSize[row], cl);
}

void hkMemory::deallocateChunkByRow(void* p, int row, int cl) {
    deallocateChunk(p, hkThreadMemory::s_instance->m_rowToSize[row], cl);
}

bool hkMemory::isAllocateChunkByRowSupported() {
    return false;
}
