#pragma once

#include <havok/hkObjectInspector.h>
#include <havok/hkPackfile.h>
#include <havok/hkStream.h>
#include <havok/hkStructureLayout.h>

// Header at the start of every binary packfile (0x40 bytes).
struct hkPackfileHeader {
    hkPackfileHeader() {
        hkString::memSet(this, -1, 0x40);
        m_magic[0] = 0x57E0E057;
        m_magic[1] = 0x10C0C010;
        m_contentsVersion[0] = 0;
    }

    int m_magic[2];                          // 0x00
    int m_userTag;                           // 0x08
    int m_fileVersion;                       // 0x0C
    hkStructureLayout::LayoutRules m_layoutRules; // 0x10
    int m_numSections;                       // 0x14
    int m_contentsSectionIndex;              // 0x18
    int m_contentsSectionOffset;             // 0x1C
    int m_contentsClassNameSectionIndex;     // 0x20
    int m_contentsClassNameSectionOffset;    // 0x24
    char m_contentsVersion[16];              // 0x28
    int m_flags;                             // 0x38
    int m_pad;                               // 0x3C
};

// Description of one section of a packfile (0x30 bytes).
struct hkPackfileSectionHeader {
    char m_sectionTag[20];        // 0x00
    int m_absoluteDataStart;      // 0x14
    int m_localFixupsOffset;      // 0x18
    int m_globalFixupsOffset;     // 0x1C
    int m_virtualFixupsOffset;    // 0x20
    int m_exportsOffset;          // 0x24
    int m_importsOffset;          // 0x28
    int m_endOffset;              // 0x2C

    void getExports(void* sectionData, hkArray<hkPackfileData::Export>& exports) const;
    void getImports(void* sectionData, hkArray<hkPackfileData::Import>& imports) const;
};

// Multi-valued pointer map: every key maps to a chain of values threaded through an array.
template <typename Value>
struct hkPointerMultiMap {
    struct Entry {
        Value m_value;  // 0x00
        int m_next;     // 0x04
    };

    hkArray<Entry> m_elements;                       // 0x00
    hkPointerMap<void*, int> m_indexMap;             // 0x0C
    int m_freeList;                                  // 0x18

    int getFirstIndex(void* key) const;
    void insert(void* key, const Value& value);
    int removeByIndex(void* key, int index);
    int getFreeIndex();
};

// Tracks pointers into a loaded packfile while its objects are replaced during versioning.
struct hkPackfileObjectUpdateTracker : hkObjectUpdateTracker {
    hkPackfileData* m_packfileData;                        // 0x08
    hkPointerMultiMap<void**> m_pointers;                  // 0x0C
    hkPointerMap<void*, const char*> m_finishObjects;      // 0x28
    void* m_topLevelObject;                                // 0x34
    const char* m_topLevelClassName;                       // 0x38

    HK_DECLARE_REF_ALLOCATOR(0x13)

    hkPackfileObjectUpdateTracker(hkPackfileData* data) {
        m_packfileData = data;
        m_packfileData->addReference();
        m_pointers.m_freeList = -1;
        m_topLevelObject = 0;
        m_topLevelClassName = 0;
    }
    virtual ~hkPackfileObjectUpdateTracker();
    virtual void addAllocation(void* p);
    virtual void addChunk(void* p, int nbytes, int cl);
    virtual void objectPointedBy(void* newObject, void* fromWhere);
    virtual void replaceObject(void* oldObject, void* newObject, const hkClass* newClass);
    virtual void addFinish(void* newObject, const char* className);
    virtual hkResult removeFinish(void* oldObject);
};

// Loads a binary packfile (from a stream, or in place from memory) and resolves its fixups.
struct hkBinaryPackfileReader : hkPackfileReader {
    struct BinaryPackfileData : hkPackfileData {};

    hkPackfileData* m_data;                      // 0x08
    hkPackfileHeader* m_header;                  // 0x0C
    hkPackfileSectionHeader* m_sectionHeaders;   // 0x10
    hkInplaceArray<void*, 16> m_sections;        // 0x14
    int m_startOffset;                           // 0x60
    hkArray<hkVariant>* m_loadedObjects;         // 0x64
    hkPackfileObjectUpdateTracker* m_tracker;    // 0x68

    HK_DECLARE_REF_ALLOCATOR(6)

    hkBinaryPackfileReader();
    virtual ~hkBinaryPackfileReader();

    virtual hkResult loadEntireFile(hkStreamReader* reader);                                     // 0x10
    virtual void* getContentsWithRegistry(const char* expectedClassName,
                                          hkFinishLoadedObjectRegistry* registry);               // 0x14
    virtual const char* getContentsClassName();                                                  // 0x1C
    virtual hkArray<hkVariant>& getLoadedObjects();                                              // 0x20
    virtual hkObjectUpdateTracker& getUpdateTracker();                                           // 0x24
    virtual const char* getOriginalContentsVersion();                                            // 0x28
    virtual hkPackfileData* getPackfileData();                                                   // 0x2C
    virtual hkResult loadEntireFileInplace(void* fileInMemory);                                  // 0x30
    virtual int getSectionIndex(const char* sectionTag);                                         // 0x34
    virtual void* getSectionDataByIndex(int sectionIndex, int offset);                           // 0x38

    hkClassNameRegistry* getClassNameRegistry();
    hkResult loadFileHeader(hkStreamReader* reader, void* buffer);
    hkResult loadSectionHeadersNoSeek(hkStreamReader* reader, void* buffer);
    hkResult loadSectionNoSeek(hkStreamReader* reader, int sectionIndex, void* buffer);
    hkResult fixupGlobalReferences();
    hkResult finishLoadedObjects(hkFinishLoadedObjectRegistry* registry);
    void* getOriginalContents();
    const char* getOriginalContentsClassName();
};
