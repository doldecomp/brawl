#pragma once

#include <StaticAssert.h>
#include <gf/gf_file_io_handle.h>
#include <memory.h>
#include <types.h>

// Documentation from Brawllib

class gfModuleHeader : public OSModuleHeader {
public:
    u32 getTextSectionAddr();
};

class gfModule {
public:
    gfModuleHeader* m_header;
    void* m_bssAddr;
    char m_flags;

    static gfModule* create(void* heap, void* buffer, size_t size);
};

class gfModuleInfo {
public:
    gfModule* m_module;
    int m_buffer;
    int m_size;
    char _12[4];
    void* m_heap;
    gfFileIOHandle* m_fileHandle;
    char _24;
    char m_flags;
    char m_moduleName;
    char _30[33];
};
static_assert(sizeof(gfModuleInfo) == 60, "Class is wrong size!");

class gfModuleManager {

public:
    HeapType m_loadHeap;
    void* m_loadHeapAddr;
    gfModuleInfo m_moduleInfos[16];

    struct LoadRequestResult {
        void* _0;
    };

    void setTempolaryLoadHeap(HeapType heapType);
    void destroy(const char* moduleName);
    void loadModuleRequestOnImage(const char* moduleName, HeapType heapType, gfModuleHeader* moduleHeader, int* nodeSize);
    bool isLoaded(const char* moduleName);
    static void loadModuleRequest(LoadRequestResult*, gfModuleManager*, const char* moduleName, HeapType heapType, bool, bool);

    static gfModuleManager* getInstance();
};
static_assert(sizeof(gfModuleManager) == 968, "Class is wrong size!");

extern gfModuleManager* g_gfModuleManager;
