#pragma once

#include <havok/hkArray.h>
#include <havok/hkClass.h>
#include <havok/hkString.h>

struct hkVariant {
    void* m_object;          // 0x00
    const hkClass* m_class;  // 0x04
};

// Receives allocation/pointer bookkeeping while loaded objects are rewritten.
struct hkObjectUpdateTracker : hkReferencedObject {
    virtual void addAllocation(void* p, int nbytes) = 0;                 // 0x10
    virtual void addChunk(void* p, int nbytes, int cl) = 0;              // 0x14
    virtual void objectPointedBy(void* newObject, void* fromWhere) = 0;  // 0x18
    virtual void replaceObject(void* oldObject, void* newObject, const hkClass* newClass) = 0; // 0x1C
    virtual void addFinish(void* newObject, const char* className) = 0;  // 0x20
    virtual void removeFinish(void* oldObject) = 0;                      // 0x24
};

struct hkVersionRegistry {
    // One step in a versioning path.
    struct Updater {
        int unk0;  // 0x00
        int unk4;  // 0x04
        hkResult (*m_updateFunction)(hkArrayBase<hkVariant>& objects, hkObjectUpdateTracker& tracker); // 0x08
    };

    hkResult getVersionPath(const char* versionFrom, const char* versionTo, hkArrayBase<const Updater*>& pathOut) const;
};

// Abstract source of loaded objects.
struct hkPackfileReader : hkReferencedObject {
    virtual void unk10() = 0;
    virtual void unk14() = 0;
    virtual void unk18() = 0;
    virtual void unk1C() = 0;
    virtual hkArrayBase<hkVariant>& getLoadedObjects() = 0;         // 0x20
    virtual hkObjectUpdateTracker& getUpdateTracker() = 0;      // 0x24
    virtual const char* getOriginalContentsVersion() = 0;       // 0x28
};

struct hkVersionUtil {
    static const char* getCurrentVersion();
    static hkResult updateBetweenVersions(hkArrayBase<hkVariant>& objectsInOut, hkObjectUpdateTracker& tracker,
                                          const hkVersionRegistry& reg, const char* versionFrom,
                                          const char* versionTo = 0);
    static hkResult updateToCurrentVersion(hkPackfileReader& reader, const hkVersionRegistry& reg);
};
