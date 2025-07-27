#include <StaticAssert.h>
#include <gf/gf_archive.h>
#include <gf/gf_heap_manager.h>
#include <gf/gf_resource_loader.h>
#include <revolution/CX/CXCompression.h>
#include <revolution/OS/OSCache.h>
#include <sr/sr_common.h>
#include <types.h>

void* gfResourceLoader::loadResource(HeapType heapTy, const char* path, gfArchive* archive, u32 freeSpaceToLeave) {
    return load(heapTy, path, archive, gfHeapManager::getMaxFreeSize(heapTy) - 0x800 - freeSpaceToLeave);
}

void* gfResourceLoader::loadResourceMemSizeOrder(HeapType heapTy, const char* path, gfArchive* archive, u32 size) {
    return load(heapTy, path, archive, size);
}

bool gfResourceLoader::isLoaded() {
    if (m_isLoaded == true) {
        return true;
    }
    if (!isReady()) {
        return false;
    }
    m_rsrcSize = CXGetUncompressedSize(m_compressedRsrcPtr);
    CXUncompressLZ(m_compressedRsrcPtr, m_rsrcPtr);
    DCFlushRange(m_rsrcPtr, m_rsrcSize);
    if (m_archive) {
        m_archive->setFileImage(m_rsrcPtr, m_rsrcSize, m_heapTy);
    }
    m_isLoaded = true;
    return true;
}

void gfResourceLoader::freeResource() {
    if (m_rsrcPtr) {
        gfHeapManager::free(m_rsrcPtr);
    }
    m_compressedRsrcPtr = nullptr;
    m_allocSize = 0;
    m_rsrcSize = 0;
    m_rsrcPtr = nullptr;
    m_isLoaded = false;
    m_archive = nullptr;
    m_heapTy = Heaps::Invalid;
}
