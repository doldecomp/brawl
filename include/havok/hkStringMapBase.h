#pragma once

#include <havok/hkMemory.h>

// Open addressing hash map keyed by C string. Storage is three parallel arrays of
// (hashMod + 1) entries: string hashes (0xFFFFFFFF = empty), string pointers, values.
struct hkStringMapBase {
    unsigned long* m_elem; // 0x00
    int m_numElems;        // 0x04
    int m_hashMod;         // 0x08

    static void* operator new(unsigned long nbytes) {
        return hkMemory::getInstance().allocateChunk(nbytes, 0x1A);
    }
    static void operator delete(void* p) {
        hkMemory::getInstance().deallocateChunk(p, sizeof(hkStringMapBase), 0x1A);
    }

    hkStringMapBase();
    ~hkStringMapBase();

    int getIterator() const;
    const char* getKey(int index) const;
    unsigned long getValue(int index) const;
    int getNext(int index) const;
    hkBool isValid(int index) const;
    void insert(const char* key, unsigned long value);
    int findKey(const char* key) const;
    hkResult get(const char* key, unsigned long* out) const;
    unsigned long getWithDefault(const char* key, unsigned long defaultValue) const;
    void resizeTable(int newCapacity);
    void clear();
};
