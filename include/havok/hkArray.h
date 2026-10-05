#pragma once

#include <havok/hkMemory.h>

// Per-thread memory object used by arrays (direct, non-virtual calls).
struct hkThreadMemory {
    void* allocateChunk(int nbytes, int cl);
    void deallocateChunk(void* p, int nbytes, int cl);
};
// HYPOTHESIS: g_hkMemoryRowTable is really the per-thread memory object pointer (see hkMemory.h)
#define HK_THREAD_MEMORY() ((hkThreadMemory*)g_hkMemoryRowTable)

enum { HK_MEMORY_CLASS_ARRAY = 0x15 };

// Untyped array storage {data, size, capacityAndFlags}; the typed hkArray<T> derives from it.
struct hkArrayBase {
    enum { DONT_DEALLOCATE_FLAG = 0x80000000, CAPACITY_MASK = 0x3FFFFFFF };

    void* m_data;             // 0x00
    int m_size;               // 0x04
    int m_capacityAndFlags;   // 0x08

    int getSize() const { return m_size; }
};

struct hkArrayUtil {
    static void _reserve(hkArrayBase* array, int numElem, int sizeElem);
    static void _reserveMore(hkArrayBase* array, int sizeElem);
    static void _reduce(hkArrayBase* array, int numElem, void* data, int sizeElem);
};

// Typed array. The destructor is a real (out-of-line) destructor.
template <typename T>
struct hkArray : hkArrayBase {
    hkArray() {
        m_data = 0;
        m_size = 0;
        m_capacityAndFlags = DONT_DEALLOCATE_FLAG;
    }
    // The flag test lives in its own inline function: this keeps the capacity load from being
    // shared with the size computation, as in the original code.
    bool mustDeallocate() const { return (m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0; }
    ~hkArray() {
        if (mustDeallocate()) {
            HK_THREAD_MEMORY()->deallocateChunk(m_data, m_capacityAndFlags * sizeof(T), HK_MEMORY_CLASS_ARRAY);
        }
    }

    T& operator[](int i) { return ((T*)m_data)[i]; }
    const T& operator[](int i) const { return ((const T*)m_data)[i]; }

    void pushBack(const T& t) {
        if (m_size == (m_capacityAndFlags & CAPACITY_MASK)) {
            hkArrayUtil::_reserveMore(this, sizeof(T));
        }
        ((T*)m_data)[m_size++] = t;
    }
};
