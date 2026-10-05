#pragma once

#include <havok/hkArray.h>
#include <havok/hkThreadMemory.h>

// Stack allocated scratch buffer (allocated from the thread memory stack area).
template <typename T>
struct hkLocalBuffer {
    T* m_data;  // 0x00
    int m_size; // 0x04

    static void* operator new(unsigned long nbytes) {
        return hkMemory::getInstance().allocateChunk(nbytes, 0x15);
    }
    static void operator delete(void* p) {
        hkMemory::getInstance().deallocateChunk(p, sizeof(hkLocalBuffer<T>), 0x15);
    }

    hkLocalBuffer(int size) {
        m_size = size;
        m_data = (T*)hkThreadMemory::s_instance->allocateStack(size * sizeof(T));
    }
    ~hkLocalBuffer() {
        hkThreadMemory::s_instance->deallocateStack(m_data);
    }
    T& operator[](int i) {
        return m_data[i];
    }
};

// Disjoint set forest stored in an external int array (negative entries are roots holding -size).
struct hkUnionFind {
    hkArrayBase* m_parents; // 0x00

    hkUnionFind(hkArrayBase& parents, int numElements);
    void addEdge(int a, int b);
    void collapseTree();
    void assignGroups(hkArrayBase& groupSizes);
};
