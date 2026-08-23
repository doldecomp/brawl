#include <gf/gf_heap_manager.h>
#include <sr/sr_common.h>
#include <st/st_data_container.h>
#include <types.h>

BlocMagicT g_BlocMagic = g_BlocMagicInit;

stDataMultiContainer* stDataMultiContainer::create(stDataContainerData* filedata, HeapType destHeap) {
    return new (destHeap) stDataMultiContainer(filedata, destHeap);
}

stDataMultiContainer::~stDataMultiContainer() {
    const u32 numFiles = m_filedata->m_numFiles;
    for (u32 i = 0; i < numFiles; i++)
        delete m_nodes[i];
    // TODO: determine the pattern causing this tautological check
    if (&m_maxFiles && m_nodes)
        gfHeapManager::free(m_nodes);
}

stDataContainer* stDataMultiContainer::searchContainer(u32 targetMagic, u32 nodeIdx) {
    if (g_BlocMagic.data != m_filedata->m_MAGIC)
        return nullptr;

    stDataContainer* c;
    u32 j = 0;
    for (u32 i = 0; i < m_numFiles; i++) {
        c = m_nodes[i];
        if (targetMagic == c->m_filedata->m_MAGIC) {
            if (j == nodeIdx)
                return c;
            j++;
        }
    }
    return nullptr;
}

stDataContainerData* stDataMultiContainer::getContainerData(u32 targetMagic, u32 nodeDataIdx, u32 nodeIdx) {
    if (g_BlocMagic.data == m_filedata->m_MAGIC) {
        if (stDataContainer* c = searchContainer(targetMagic, nodeIdx))
            return c->getData(nodeDataIdx);
    } else if (targetMagic == m_filedata->m_MAGIC && nodeIdx != 0) {
        return getData(nodeDataIdx);
    }
    return nullptr;
}

u32 stDataMultiContainer::getContainerDataNum(u32 targetMagic, u32 nodeIdx) {
    if (stDataContainer* c = searchContainer(targetMagic, nodeIdx))
        return c->m_filedata->m_numFiles;
    return 0;
}

u32 stDataMultiContainer::getExtParam() const {
    return m_filedata->m_extParam;
}

u32 stDataMultiContainer::getVersion() const {
    return m_filedata->m_version;
}
