#include <gf/gf_heap_manager.h>
#include <sr/sr_common.h>
#include <types.h>

static s32 DebugLevel = 4;

s32 srSystemGetDebugLevel() {
    return DebugLevel;
}

void* operator new(size_t size) {
    return gfHeapManager::alloc(Heaps::Tmp, size);
}

void* operator new(size_t size, Heaps::HeapType heap) {
    return gfHeapManager::alloc(heap, size);
}

void operator delete(void* ptr) {
    gfHeapManager::free(ptr);
}

void* operator new[](size_t size, Heaps::HeapType heap) {
    return gfHeapManager::alloc(heap, size);
}

void operator delete[](void* ptr) {
    gfHeapManager::free(ptr);
}
