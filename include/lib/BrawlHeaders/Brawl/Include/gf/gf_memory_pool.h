#pragma once

#include <StaticAssert.h>
#include <types.h>

class gfMemoryPool;

struct HeapInfo {
    const char* m_name;
    gfMemoryPool* m_memoryPool;
    u32 m_size;
    u32 m_arena;
};
extern HeapInfo g_HeapInfos[0x47];

class gfMemoryPool {
public:
    u32 getMaxFreeBlockSize();

    static void* alloc(void* heapAddr, size_t size, int align);
    static gfMemoryPool* create(void* heapAddr, size_t size, const char* heapName);

    /**
     * @brief Custom function to create a memory pool at a specific address
     *
     * @param heapAddr Start address of the memory pool
     * @param heapName Name to assign the memory pool
     * @param heapID ID of the memory pool
     * @param size Size of the memory pool
     * @param arena Whether this pool resides in MEM1 or MEM2
     */
    static gfMemoryPool* create(void* heapAddr, const char* heapName, int heapID, size_t size, int arena)
    {
        gfMemoryPool* pool = create(heapAddr, size, heapName);
        g_HeapInfos[heapID].m_name = heapName;
        g_HeapInfos[heapID].m_memoryPool = pool;
        g_HeapInfos[heapID].m_size = size;
        g_HeapInfos[heapID].m_arena = arena;
        return pool;
    }
}; // class gfMemoryPool
