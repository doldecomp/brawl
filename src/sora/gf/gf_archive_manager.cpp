#include <gf/gf_archive_manager.h>
#include <nw4r/ut/ut_LinkList.h>
#include <sr/sr_common.h>

gfArchiveManager* g_gfArchiveManager;

void gfArchiveManager::create() {
    g_gfArchiveManager = new (Heaps::SystemFW) gfArchiveManager;
}

void gfArchiveManager::update() {
    nw4r::ut::LinkList<gfArchive, 0>::Iterator it;
    for (it = m_archives.GetBeginIter(); it != m_archives.GetEndIter(); ++it) {
        if (!it->unk9)
            it->update();
    }

    // Note: unclear why this loop is repeated; possibly connected to the
    // unused extra list
    for (it = m_archives.GetBeginIter(); it != m_archives.GetEndIter(); ++it) {
        if (!it->unk9)
            it->update();
    }
}

void gfArchiveManager::pushback(gfArchive* arc) {
    m_archives.PushBack(arc);
}

void gfArchiveManager::remove(gfArchive* arc) {
    if (!m_archives.IsEmpty())
        m_archives.Erase(arc);
}
