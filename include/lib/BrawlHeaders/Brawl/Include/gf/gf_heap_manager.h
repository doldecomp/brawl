#pragma once

#include <StaticAssert.h>
#include <MEM/mem_allocator.h>
#include <memory.h>
#include <sr/sr_common.h>
#include <types.h>

class gfHeapManager {
public:
    static int getMaxFreeSize(Heaps::HeapType heapType);
    static void dumpAll();
    static void dumpList();
    static void createHeap(int heapId, const char* heapName, int memArena, int heapSize);

    static void* alloc(Heaps::HeapType heapType, size_t size);
    static void* alloc(Heaps::HeapType heapType, size_t size, s32 align);
    static void free(void* ptr);
    static MEMAllocator* getMEMAllocator(Heaps::HeapType heapType);
    static void* getHeap(Heaps::HeapType heapType);
};
