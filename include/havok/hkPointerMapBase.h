#pragma once

#include <havok/hkMemory.h>

// Open addressing hash map keyed by pointer-sized (or 64-bit) values.
// Keys occupy slots [0, hashMod], values follow at [hashMod + 1, 2 * hashMod + 1].
// A key of zero marks an empty slot.
template <typename T>
struct hkPointerMapBase {
    enum { DONT_DEALLOCATE_FLAG = 0x80000000 };

    T* m_elem;      // 0x00
    int m_numElems; // 0x04 (high bit: storage is not owned)
    int m_hashMod;  // 0x08

    static void* operator new(unsigned long nbytes) {
        return hkMemory::getInstance().allocateChunk(nbytes, 0x1A);
    }
    static void operator delete(void* p) {
        hkMemory::getInstance().deallocateChunk(p, sizeof(hkPointerMapBase<T>), 0x1A);
    }

    hkPointerMapBase();
    ~hkPointerMapBase();

    void insert(T key, T value);
    int findKey(T key) const;
    T getWithDefault(T key, T defaultValue) const;
    hkResult get(T key, T* out) const;
    hkBool isValid(int index) const;
    void remove(int index);
    hkResult remove(T key);
    void clear();
    void reserve(int numElements);
    void resizeTable(int newCapacity);
};
