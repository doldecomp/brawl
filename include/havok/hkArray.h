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

    // Wraps caller-owned storage (never deallocated).
    hkArray(T* ptr, int size, int capacity) {
        m_data = ptr;
        m_size = size;
        m_capacityAndFlags = capacity | DONT_DEALLOCATE_FLAG;
    }

    int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }

    void reserve(int n) {
        if (n > getCapacity()) {
            reserveSmart(n);
        }
    }
    void reserveSmart(int n) {
        if (getCapacity() < n) {
            int c = getCapacity() * 2;
            int m = n;
            if (n < c) {
                m = c;
            }
            hkArrayUtil::_reserve(this, m, sizeof(T));
        }
    }

    void insertAt(int i, const T& t);
    void insertAt(int i, const hkArray<T>& other);

    void pushBack(const T& t) {
        if (m_size == (m_capacityAndFlags & CAPACITY_MASK)) {
            hkArrayUtil::_reserveMore(this, sizeof(T));
        }
        ((T*)m_data)[m_size++] = t;
    }
};

// Out-of-line template members (not inline: they are instantiated as separate functions).
template <typename T>
void hkArray<T>::insertAt(int i, const T& t) {
    hkArray<T> one((T*)&t, 1, 1);
    insertAt(i, one);
}

template <typename T>
void hkArray<T>::insertAt(int i, const hkArray<T>& other) {
    int n = other.m_size;
    int newSize = n + m_size;
    int numToMove = m_size - i;
    reserve(newSize);
    T* src = (T*)m_data + i;
    T* dst = src + n;
    for (int k = numToMove - 1; k >= 0; k--) {
        dst[k] = src[k];
    }
    const T* from = (const T*)other.m_data;
    T* to = (T*)m_data + i;
    for (int k = n - 1; k >= 0; k--) {
        to[k] = from[k];
    }
    m_size = newSize;
}
