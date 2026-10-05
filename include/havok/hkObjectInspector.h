#pragma once

#include <havok/hkArray.h>
#include <havok/hkClass.h>

// Walks the pointers inside reflected objects.
struct hkObjectInspector {
    // One pointer slot found inside an object, with the class of what it points to.
    struct Pointer {
        void** m_address;         // 0x00
        const hkClass* m_class;   // 0x04
    };

    // Receives each reached object together with its pointer slots.
    struct Listener : hkBaseObject {
        virtual hkResult objectCallback(void* object, const hkClass& klass, hkArray<Pointer>& pointers) = 0; // 0x0C
    };

    static hkResult getPointers(void* object, const hkClass& klass, hkArray<Pointer>& pointersOut);
    static hkResult walkPointers(void* object, const hkClass& klass, Listener& listener);
};
