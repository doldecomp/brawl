#pragma once

#include <StaticAssert.h>
#include <gf/gf_heap_manager.h>
#include <gf/gf_memory_util.h>
#include <sr/sr_common.h>
#include <types.h>

struct stDataContainerData {
    u32 m_MAGIC;
    u32 m_numFiles;
    s32 m_version;
    u32 m_extParam;
};

struct BlocMagicT {
    u32 data;
    BlocMagicT(u32 d) : data(d) { }
};
extern u32 g_BlocMagicInit;
extern BlocMagicT g_BlocMagic;

class stDataContainer {
public:
    stDataContainer(stDataContainerData* data);
    virtual ~stDataContainer();
    virtual u32 getVersion() const { return 0; }
    virtual u32 getExtParam() const { return 0; }
    virtual stDataContainerData* getData(u32 index);
    virtual void* getDataAddressHead();

    u32 m_headerSize;
    stDataContainerData* m_filedata;
    static const u32 HeaderSize = 8;
};
static_assert(sizeof(stDataContainer) == 0xC, "Class is wrong size!");

class stDataSimpleContainer : public stDataContainer {
    static const u32 SimpleHeaderSize = 16;

public:
    stDataSimpleContainer(stDataContainerData* data);
    virtual ~stDataSimpleContainer();
};
static_assert(sizeof(stDataSimpleContainer) == 0xC, "Class is wrong size!");

class stDataMultiContainer : public stDataContainer {
private:
    u16 m_maxFiles;
    u16 m_numFiles;
    stDataContainer** m_nodes;

    static const u32 Capacity = 64;
    static const u32 HeaderSize = 16;
public:
    stDataMultiContainer(stDataContainerData* filedata, HeapType destHeap) :
        stDataContainer(filedata),
        m_maxFiles(Capacity),
        m_numFiles(0),
        m_nodes((stDataContainer**)(gfHeapManager::alloc(destHeap, sizeof(m_nodes[0]) * Capacity)))
    {
        gfMemFill(m_nodes, 0, sizeof(m_nodes[0]) * Capacity);
        m_headerSize = HeaderSize;
        const u32 numFiles = m_filedata->m_numFiles;
        for (u32 i = 0; i < numFiles; i++) {
            stDataContainerData* data = getData(i);
            // BUG: starts to leak stDataContainers once Capacity is exceeded
            stDataContainer* c = new (destHeap) stDataContainer(data);
            if (m_numFiles < m_maxFiles) {
                m_nodes[m_numFiles] = c;
                m_numFiles++;
            }
        }
    }

    virtual ~stDataMultiContainer();
    virtual u32 getVersion() const;
    virtual u32 getExtParam() const;

    stDataContainer* searchContainer(u32 targetMagic, u32 nodeIdx);
    stDataContainerData* getContainerData(u32 targetMagic, u32 nodeDataIdx, u32 nodeIdx);
    u32 getContainerDataNum(u32 targetMagic, u32 nodeIdx);

    static stDataMultiContainer* create(stDataContainerData* filedata, HeapType destHeap);
};
static_assert(sizeof(stDataMultiContainer) == 0x14, "Class is wrong size!");
