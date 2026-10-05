#pragma once

#include <havok/hkMemory.h>

// Allocator entry point used by hkArray (per-thread memory object; this is a direct (non-virtual) call).
struct hkThreadMemory {
    void* allocateChunk(int nbytes, int cl);
    void deallocateChunk(void* p, int nbytes, int cl);
};
// HYPOTHESIS: g_hkMemoryRowTable is really the per-thread memory object pointer (see hkMemory.h)
#define HK_THREAD_MEMORY() ((hkThreadMemory*)g_hkMemoryRowTable)

enum { HK_MEMORY_CLASS_ARRAY = 0x15 };

// Havok 4.0 dynamic array storage: {data, size, capacityAndFlags}.
// MATCH-ONLY: callers that need the deallocation inlined at each exit use this base directly and call
// clearAndDeallocate() by hand; MWCC never inlines a destructor of a local, but the original code has the
// deallocation inlined.
template <typename T>
struct hkArrayBase {
    enum { DONT_DEALLOCATE_FLAG = 0x80000000 };

    T* m_data;                // 0x00
    int m_size;               // 0x04
    int m_capacityAndFlags;   // 0x08


    void clearAndDeallocate() {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0) {
            HK_THREAD_MEMORY()->deallocateChunk(m_data, m_capacityAndFlags * sizeof(T), HK_MEMORY_CLASS_ARRAY);
        }
    }

    int getSize() const { return m_size; }
    T& operator[](int i) { return m_data[i]; }
    const T& operator[](int i) const { return m_data[i]; }
};

template <typename T>
struct hkArray : hkArrayBase<T> {
    hkArray() {
        this->m_data = 0;
        this->m_size = 0;
        this->m_capacityAndFlags = hkArrayBase<T>::DONT_DEALLOCATE_FLAG;
    }
    ~hkArray() { this->clearAndDeallocate(); }
};
