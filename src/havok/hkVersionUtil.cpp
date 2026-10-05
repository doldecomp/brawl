#include <havok/hkVersion.h>
#include <havok/hkString.h>

// MATCH-ONLY: the original calls getCurrentVersion/updateBetweenVersions out of line.
#pragma dont_inline on

const char* hkVersionUtil::getCurrentVersion() {
    return "Havok-4.0.0-r1";
}

hkResult hkVersionUtil::updateBetweenVersions(hkArrayBase<hkVariant>& objectsInOut, hkObjectUpdateTracker& tracker,
                                              const hkVersionRegistry& reg, const char* versionFrom,
                                              const char* versionTo) {
    versionTo = versionTo ? versionTo : getCurrentVersion();
    hkArrayBase<const hkVersionRegistry::Updater*> path;
    path.m_data = 0;
    path.m_size = 0;
    path.m_capacityAndFlags = 0x80000000;
    if (reg.getVersionPath(versionFrom, versionTo, path) == HK_SUCCESS) {
        for (int i = 0; i < path.m_size; i++) {
            path.m_data[i]->m_updateFunction(objectsInOut, tracker);
        }
        if ((path.m_capacityAndFlags & 0x80000000) == 0) {
            g_hkMemoryRowTable->deallocateChunk(path.m_data, path.m_capacityAndFlags << 2, HK_MEMORY_CLASS_ARRAY);
        }
        return HK_SUCCESS;
    }
    if ((path.m_capacityAndFlags & 0x80000000) == 0) {
        g_hkMemoryRowTable->deallocateChunk(path.m_data, path.m_capacityAndFlags << 2, HK_MEMORY_CLASS_ARRAY);
    }
    return HK_FAILURE;
}
hkResult hkVersionUtil::updateToCurrentVersion(hkPackfileReader& reader, const hkVersionRegistry& reg) {
    const char* version = reader.getOriginalContentsVersion();
    if (hkString::strCmp(version, getCurrentVersion()) != 0) {
        hkArrayBase<hkVariant>& objects = reader.getLoadedObjects();
        if (objects.m_size != 0) {
            return updateBetweenVersions(objects, reader.getUpdateTracker(), reg, version, getCurrentVersion());
        }
        return HK_FAILURE;
    }
    return HK_SUCCESS;
}
