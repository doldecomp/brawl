#pragma once

#include <havok/hkThreadMemory.h>

// Untyped part of hkArray<T>: data pointer, element count, and capacity with flag bits.
struct hkArrayBase {
    enum {
        CAPACITY_MASK = 0x3FFFFFFF,
        FORCE_SIGN_FLAG = 0x40000000,
        DONT_DEALLOCATE_FLAG = 0x80000000,
    };

    void* m_data;            // 0x00
    int m_size;              // 0x04
    int m_capacityAndFlags;  // 0x08

    int getSize() const {
        return m_size;
    }
};

struct hkArrayUtil {
    static void _reserve(hkArrayBase* array, int newCapacity, int elemSize);
    static void _reserveMore(hkArrayBase* array, int elemSize);
    static void _reduce(hkArrayBase* array, int elemSize, void* buffer, int bufferCapacity);
};

// Typed dynamic array on top of hkArrayBase (storage comes from the thread memory).
template <typename T>
struct hkArray : hkArrayBase {
    hkArray() {
        m_data = 0;
        m_size = 0;
        m_capacityAndFlags = DONT_DEALLOCATE_FLAG;
    }
    // Wraps caller-owned storage (never deallocated).
    hkArray(T* ptr, int size, int capacity) {
        m_data = ptr;
        m_size = size;
        m_capacityAndFlags = capacity | DONT_DEALLOCATE_FLAG;
    }
    // The flag test lives in its own inline function: this keeps the capacity load from being
    // shared with the size computation, as in the original code (hkVersionUtil, hkVersionRegistry).
    bool mustDeallocate() const {
        return (m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0;
    }
    ~hkArray() {
        if (mustDeallocate()) {
            hkThreadMemory::s_instance->deallocateChunk(m_data, (m_capacityAndFlags & CAPACITY_MASK) * sizeof(T), 0x15);
        }
    }

    int getCapacity() const {
        return m_capacityAndFlags & CAPACITY_MASK;
    }
    hkArray<T>& operator=(const hkArray<T>& other) {
        if ((m_capacityAndFlags & CAPACITY_MASK) < other.m_size) {
            if (mustDeallocate()) {
                hkThreadMemory::s_instance->deallocateChunk(m_data, (m_capacityAndFlags & CAPACITY_MASK) * sizeof(T), 0x15);
            }
            m_data = hkThreadMemory::s_instance->allocateChunk(other.m_size * sizeof(T), 0x15);
            m_capacityAndFlags = other.m_size | (m_capacityAndFlags & FORCE_SIGN_FLAG);
        }
        int n = other.m_size;
        m_size = n;
        const T* src = (const T*)other.m_data;
        int i = 0;
        T* dst = (T*)m_data;
        for (; i < n; i++) {
            dst[i] = src[i];
        }
        return *this;
    }
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
    void swap(hkArray<T>& other);
    void insertAt(int i, const T& t);
    void insertAt(int i, const hkArray<T>& other);

    const T& operator[](int i) const {
        return ((const T*)m_data)[i];
    }
    void pushBack(const T& t) {
        if (m_size == (m_capacityAndFlags & CAPACITY_MASK)) {
            hkArrayUtil::_reserveMore(this, sizeof(T));
        }
        ((T*)m_data)[m_size++] = t;
    }
    T& operator[](int i) {
        return ((T*)m_data)[i];
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

template <typename T>
void hkArray<T>::swap(hkArray<T>& other) {
    void* d = m_data;
    m_data = other.m_data;
    other.m_data = d;
    int sz = m_size;
    m_size = other.m_size;
    other.m_size = sz;
    int cap = m_capacityAndFlags;
    m_capacityAndFlags = other.m_capacityAndFlags;
    other.m_capacityAndFlags = cap;
}

// Array with inline storage for N elements.
template <typename T, int N>
struct hkInplaceArray : hkArray<T> {
    T m_storage[N];

    hkInplaceArray() {
        this->m_data = m_storage;
        this->m_size = 0;
        this->m_capacityAndFlags = N | DONT_DEALLOCATE_FLAG;
    }
};
