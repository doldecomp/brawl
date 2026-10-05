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
