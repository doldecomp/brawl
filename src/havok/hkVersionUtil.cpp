#include <havok/hkVersion.h>
#include <havok/hkString.h>

const char* hkVersionUtil::getCurrentVersion() {
    return "Havok-4.0.0-r1";
}

hkResult hkVersionUtil::updateBetweenVersions(hkArray<hkVariant>& objectsInOut, hkObjectUpdateTracker& tracker,
                                              const hkVersionRegistry& reg, const char* versionFrom,
                                              const char* versionTo) {
    versionTo = versionTo ? versionTo : getCurrentVersion();
    hkArray<const hkVersionRegistry::Updater*> path;
    if (reg.getVersionPath(versionFrom, versionTo, path) == HK_SUCCESS) {
        for (int i = 0; i < path.getSize(); i++) {
            path[i]->m_updateFunction(objectsInOut, tracker);
        }
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

hkResult hkVersionUtil::updateToCurrentVersion(hkPackfileReader& reader, const hkVersionRegistry& reg) {
    const char* version = reader.getOriginalContentsVersion();
    if (hkString::strCmp(version, getCurrentVersion()) != 0) {
        hkArray<hkVariant>& objects = reader.getLoadedObjects();
        if (objects.m_size != 0) {
            return updateBetweenVersions(objects, reader.getUpdateTracker(), reg, version, getCurrentVersion());
        }
        return HK_FAILURE;
    }
    return HK_SUCCESS;
}
