#pragma once

#include <havok/hkArray.h>
#include <havok/hkMap.h>
#include <havok/hkRegistry.h>
#include <havok/hkVersion.h>

// Everything a loaded packfile owns: the name, the tracked objects with their type infos, raw allocations,
// and the import/export tables.
struct hkPackfileData : hkReferencedObject {
    struct Export {
        const char* m_name;   // 0x00
        void* m_object;       // 0x04
    };
    struct Import {
        const char* m_name;   // 0x00
        void* m_object;       // 0x04
    };
    struct Allocation {
        void* m_pointer;      // 0x00
        int m_size;           // 0x04
        int m_class;          // 0x08
    };

    char* m_name;                              // 0x08 (heap string)
    hkPointerMap<void*, const hkTypeInfo*> m_trackedObjects;  // 0x0C  object -> type info
    hkArray<void*> m_memory;                   // 0x18  chunks released with hkMemory::deallocate
    hkArray<Allocation> m_allocations;         // 0x24  chunks released with hkMemory::deallocateChunk
    hkArray<Export> m_exports;                 // 0x30
    hkArray<Import> m_imports;                 // 0x3C

    HK_DECLARE_REF_ALLOCATOR(0x13)

    hkPackfileData();
    virtual ~hkPackfileData();
    virtual const char* getName() { return m_name; }                                 // 0x10
    virtual void callDestructors();                                                  // 0x14
    virtual void getImportsExports(hkArray<Export>& exports, hkArray<Import>& imports); // 0x18

    void addExport(const char* name, void* object);
    void addImport(const char* name, void* object);
};
