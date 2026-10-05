#pragma once

#include <havok/hkVersion.h>
#include <havok/hkMap.h>
#include <havok/hkMemory.h>
#include <havok/hkSingleton.h>

// Per-class registration record (partial; offsets seen from registerList).
struct hkTypeInfo {
    const char* m_name;      // 0x00
    void (*m_finish)(void*); // 0x04 (HYPOTHESIS: finishLoadedObject callback)
    void (*m_cleanup)(void*);// 0x08 (cleanupLoadedObject callback)
    const void* m_vtable;    // 0x0C
};

// Name -> reflection class table.
struct hkClassNameRegistry : hkReferencedObject {
    hkStringMap<const hkClass*> m_map;  // 0x08

    HK_DECLARE_REF_ALLOCATOR(0x13)

    virtual void registerClass(const hkClass* klass, const char* name = 0);   // 0x10
    virtual const hkClass* getClassByName(const char* name) const;            // 0x14
    virtual void registerList(const hkClass* const* classes);                 // 0x18
    virtual void merge(hkClassNameRegistry& other);                           // 0x1C
};

// Name -> hkTypeInfo (finish/cleanup callbacks) table.
struct hkFinishLoadedObjectRegistry : hkReferencedObject {
    hkStringMap<const hkTypeInfo*> m_map;  // 0x08

    HK_DECLARE_REF_ALLOCATOR(0x13)

    virtual void registerTypeInfo(const hkTypeInfo* info);                    // 0x10
    virtual void finishLoadedObject(void* object, const char* className) const; // 0x14
    virtual void merge(hkFinishLoadedObjectRegistry& other);                  // 0x18
};

// Maps virtual-table pointers to reflection classes.
struct hkVtableClassRegistry : hkReferencedObject {
    hkPointerMap<const void*, const hkClass*> m_map;  // 0x08

    HK_DECLARE_REF_ALLOCATOR(0x13)

    virtual void registerVtable(const void* vtable, const hkClass* klass);   // 0x10
    virtual const hkClass* getClassFromVirtualInstance(const void* instance) const; // 0x14

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
    hkArrayBase m_namedVariants; // 0x00

    void* findObjectByType(const char* typeName, const void* prevObject = 0) const;
};

// Registry of all built-in (statically linked) Havok types.
struct hkBuiltinTypeRegistry : hkSingleton<hkBuiltinTypeRegistry> {
    virtual hkFinishLoadedObjectRegistry* getFinishLoadedObjectRegistry() = 0; // 0x10
    virtual hkClassNameRegistry* getClassNameRegistry() = 0;                   // 0x14
    virtual hkVtableClassRegistry* getVtableClassRegistry() = 0;               // 0x18
    virtual void addType(const hkTypeInfo* info, const hkClass* klass);        // 0x1C

    static hkBuiltinTypeRegistry* create();
};
