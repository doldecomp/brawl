#pragma once

#include <havok/hkArray.h>
#include <havok/hkClass.h>
#include <havok/hkString.h>
#include <havok/hkMap.h>
#include <havok/hkSingleton.h>

struct hkVariant {
    void* m_object;          // 0x00
    const hkClass* m_class;  // 0x04
};

// Receives allocation/pointer bookkeeping while loaded objects are rewritten.
struct hkObjectUpdateTracker : hkReferencedObject {
    virtual void addAllocation(void* p) = 0;                             // 0x10
    virtual void addChunk(void* p, int nbytes, int cl) = 0;              // 0x14
    virtual void objectPointedBy(void* newObject, void* fromWhere) = 0;  // 0x18
    virtual void replaceObject(void* oldObject, void* newObject, const hkClass* newClass) = 0; // 0x1C
    virtual void addFinish(void* newObject, const char* className) = 0;  // 0x20
    virtual hkResult removeFinish(void* oldObject) = 0;                  // 0x24
};

struct hkClassNameRegistry;

// Holds the chain of object updaters between Havok releases and the class sets of each release.
struct hkVersionRegistry : hkSingleton<hkVersionRegistry> {
    // One step in a versioning path.
    struct Updater {
        const char* m_fromVersion;  // 0x00
        const char* m_toVersion;    // 0x04
        hkResult (*m_updateFunction)(hkArray<hkVariant>& objects, hkObjectUpdateTracker& tracker); // 0x08

        static int getNumElements(const Updater* const* updaters);
    };

    // Classes (null terminated) that existed in one release.
    struct ClassVersion {
        const char* m_version;               // 0x00
        const hkClass* const* m_classes;     // 0x04
    };

    hkArray<const Updater*> m_updaters;                                 // 0x08
    hkStringMap<hkClassNameRegistry*> m_versionToClassNameRegistryMap;  // 0x14

    static const Updater* const StaticLinkedUpdaters[];
    static const ClassVersion StaticLinkedClassVersions[];

    hkVersionRegistry();
    virtual ~hkVersionRegistry();

    hkResult getVersionPath(const char* versionFrom, const char* versionTo, hkArray<const Updater*>& pathOut) const;
    hkClassNameRegistry* getClassNameRegistry(const char* versionString);
    static hkVersionRegistry* create();
};

struct hkFinishLoadedObjectRegistry;
struct hkStreamReader;

// Abstract source of loaded objects.
struct hkPackfileReader : hkReferencedObject {
    virtual hkResult loadEntireFile(hkStreamReader* reader) = 0;                                       // 0x10
    virtual void* getContentsWithRegistry(const char* expectedClassName,
                                          hkFinishLoadedObjectRegistry* registry) = 0;                  // 0x14
    virtual void* getContents(const char* expectedClassName);                                          // 0x18
    virtual const char* getContentsClassName() = 0;                                                    // 0x1C
    virtual hkArray<hkVariant>& getLoadedObjects() = 0;                                                // 0x20
    virtual hkObjectUpdateTracker& getUpdateTracker() = 0;                                             // 0x24
    virtual const char* getOriginalContentsVersion() = 0;                                              // 0x28
};

struct hkVersionUtil {
    static const char* getCurrentVersion();
    static hkResult updateBetweenVersions(hkArray<hkVariant>& objectsInOut, hkObjectUpdateTracker& tracker,
                                          const hkVersionRegistry& reg, const char* versionFrom,
                                          const char* versionTo = 0);
    static hkResult updateToCurrentVersion(hkPackfileReader& reader, const hkVersionRegistry& reg);
};
