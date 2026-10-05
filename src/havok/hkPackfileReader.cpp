#include <havok/hkRegistry.h>

void* hkPackfileReader::getContents(const char* expectedClassName) {
    return getContentsWithRegistry(expectedClassName,
                                   hkBuiltinTypeRegistry::getInstance().getFinishLoadedObjectRegistry());
}
