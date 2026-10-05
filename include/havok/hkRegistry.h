#pragma once

#include <havok/hkVersion.h>

// Per-class registration record (partial; offsets seen from registerList).
struct hkTypeInfo {
    int unk0;                // 0x00
    int unk4;                // 0x04
    int unk8;                // 0x08
    const void* m_vtable;    // 0x0C
};

// Maps virtual-table pointers to reflection classes.
struct hkVtableClassRegistry : hkReferencedObject {
    virtual void registerVtable(const void* vtable, const hkClass* klass) = 0;   // 0x10
    virtual const hkClass* getClassFromVirtualInstance(const void* instance) const = 0; // 0x14

    void registerList(const hkTypeInfo* const* infos, const hkClass* const* classes);
};

// A named, typed object inside a packfile.
struct hkRootLevelContainerNamedVariant {
    hkString m_name;       // 0x00
    hkString m_className;  // 0x04
    hkVariant m_variant;   // 0x08

    const char* getTypeName() const {
        if (m_className.m_string != 0) {
            return m_className.m_string;
        }
        if (m_variant.m_class != 0) {
            return m_variant.m_class->getName();
        }
        return 0;
    }
};

struct hkRootLevelContainer {
    hkArrayBase<hkRootLevelContainerNamedVariant> m_namedVariants; // 0x00

    void* findObjectByType(const char* typeName, const void* prevObject = 0) const;
};
