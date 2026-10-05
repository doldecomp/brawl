#pragma once

#include <havok/hkMemory.h>

// Singleton base: reference counted object whose deallocation goes through hkMemory
// using the generic base allocation class.
template <typename T>
struct hkSingleton : hkReferencedObject {
    static T* s_instance;

    HK_DECLARE_REF_ALLOCATOR(HK_MEMORY_CLASS_BASE)

    static T& getInstance() {
        return *s_instance;
    }
};
