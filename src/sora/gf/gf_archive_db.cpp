#include <gf/gf_archive.h>
#include <gf/gf_archive_db.h>
#include <sr/sr_common.h>
#include <types.h>

gfArchiveDatabase* gfArchiveDatabase::create(u32 count, Heaps::HeapType heap) {
    return new (heap, count) gfArchiveDatabase(count);
}

gfArchiveDatabase::~gfArchiveDatabase() {
    for (s32 i = 0; i < m_capacity; i++) {
        gfArchiveDatabaseEntry* ep = &m_entries[i];
        if (ep->m_isActive) {
            if (!--ep->m_archive->m_refCount) {
                if (ep->m_isOwner) {
                    delete ep->m_archive;
                }
                ep->m_archive = nullptr;
                ep->m_isActive = false;
            }
            ep = &m_entries[i];
            ep->m_archive = nullptr;
            ep->unk4_b7 = ep->m_isActive = false;
            ep->m_isOwner = true;
            ep->m_next = nullptr;
        }
    }
    m_entries = nullptr;
    m_capacity = 0;
    m_size = 0;
}

s32 gfArchiveDatabase::add(gfArchive* arc, bool makeOwner) {
    s32 idx = findAvail();
    arc->m_refCount++;
    m_entries[idx].m_archive = arc;
    m_entries[idx].m_isActive = true;
    m_entries[idx].m_isOwner = makeOwner;
    m_size++;
    return idx;
}

gfArchive* gfArchiveDatabase::get(s32 i) const {
    const gfArchiveDatabaseEntry* ep = &m_entries[i];
    gfArchive* arc = nullptr;
    if (ep->m_isActive) {
        arc = ep->m_archive;
    }
    return arc;
}
