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
    ~hkArray() {
        if (!(m_capacityAndFlags & DONT_DEALLOCATE_FLAG)) {
            hkThreadMemory::s_instance->deallocateChunk(m_data, sizeof(T) * m_capacityAndFlags, 0x15);
        }
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
