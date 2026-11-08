#include <em/em_archive.h>
#include <em/em_create.h>
#include <em/em_info.h>
#include <em/em_manager.h>
#include <em/enemy.h>
#include <snd/snd_system.h>
#include <so/so_archive_db.h>
#include <so/so_external_value_accesser.h>
#include <sr/sr_common.h>
#include <types.h>

emManager* g_emManager;

void emManager::create(u32 numEnemyEntries, u32 numArchiveEntries, u8 primidFaceType) {
    if (g_emManager == nullptr) {
        Entry* enemyEntries = new (Heaps::EnemyInstance) Entry[numEnemyEntries];
        if (enemyEntries != nullptr) {
            Entry* archiveEntries = new (Heaps::EnemyInstance) Entry[numArchiveEntries];
            if (archiveEntries == nullptr) {
                delete[] enemyEntries;
            } else if (!soArchiveDb::create(1, numArchiveEntries * 2 + 1)) {
                delete[] enemyEntries;
                delete[] archiveEntries;
            } else {
                g_emManager = new (Heaps::EnemyInstance) emManager(numEnemyEntries, enemyEntries, numArchiveEntries, archiveEntries, primidFaceType);
                if (g_emManager == nullptr) {
                    delete[] enemyEntries;
                    delete[] archiveEntries;
                    soArchiveDb::remove(1);
                }
            }
        }
    }
}

void emManager::remove() {
    delete g_emManager;
    g_emManager = nullptr;
}

emManager* emManager::getInstance() {
    return g_emManager;
}

emManager::emManager(u32 numEnemyEntries, Entry* enemyEntries, u32 numArchiveEntries, Entry* archiveEntries, u8 primidFaceType) {
    m_numEnemyEntries = numEnemyEntries;
    m_enemyEntries = enemyEntries;
    for (u32 i = 0; i < m_numEnemyEntries; i++) {
        m_enemyEntries[i].clear();
    }
    m_nextEnemyCreateId = 0;
    m_numArchiveEntries = numArchiveEntries;
    m_archiveEntries = archiveEntries;
    for (u32 i = 0; i < m_numArchiveEntries; i++) {
        m_archiveEntries[i].clear();
    }
    m_nextArchiveCreateId = 0;
    m_primidFaceType = primidFaceType;
}

void emManager::Entry::clear() {
    m_dataPtr = nullptr;
    m_isActive = false;
    m_enemyKind = static_cast<EnemyKind>(emInfo::getInstance()->getInvalidKind());
    m_parentCreateId = 0xFFFF;
    m_createId = 0xFFFF;
    m_soundGroupOffset = -2;
}

emManager::~emManager() {
    removeEnemyAll();
    removeArchiveAll();
    delete[] m_enemyEntries;
    delete[] m_archiveEntries;
    soArchiveDb::remove(1);
    m_numEnemyEntries = 0;
    m_enemyEntries = nullptr;
    m_nextEnemyCreateId = 0;
    m_numArchiveEntries = 0;
    m_archiveEntries = nullptr;
    m_nextArchiveCreateId = 0;
    m_primidFaceType = 0;
}

int emManager::createEnemy(emCreate* create) {
    int createId;
    EnemyKind enemyKind;
    Entry* entry;
    Enemy* enemy;
    if (emInfo::getInstance()->isInvalidKind(create->m_enemyKind) == true) {
        return -2;
    }
    getPreloadArchiveCountFromKind(create->m_enemyKind);
    int archiveId = getPreloadArchiveCreateIdFromKind(create->m_enemyKind);
    if (archiveId < 0) {
        return -5;
    }
    if (!isCompArchive(archiveId)) {
        return -5;
    }
    int index = getEmptyEnemyEntryIndex();
    if (index < 0) {
        return -3;
    }
    entry = getEnemyEntry(index);
    if (entry == nullptr) {
        return -3;
    }
    createId = getNextEnemyCreateId();
    enemy = Enemy::create(createId, create);
    if (enemy == nullptr) {
        return -4;
    }
    enemyKind = create->m_enemyKind;
    entry->clear();
    entry->m_dataPtr = enemy;
    entry->m_isActive = true;
    entry->m_enemyKind = enemyKind;
    entry->m_parentCreateId = create->m_parentCreateId;
    entry->m_createId = createId;
    Enemy::start(enemy, create);
    return createId;
}

#pragma dont_inline on
bool emManager::isParent(int parentCreateId, int createId) const {
    Entry* entry = g_emManager->getEntryEnemyPtrFromId(createId);
    return entry->m_parentCreateId == parentCreateId;
}
#pragma dont_inline reset

bool emManager::clearParentCallback(int parentCreateId, int createId) {
    if (g_emManager->isParent(parentCreateId, createId) == true) {
        Entry* entry = g_emManager->getEntryEnemyPtrFromId(createId);
        if (entry == nullptr) {
            return true;
        }
        entry->m_parentCreateId = 0xFFFF;
    }
    return true;
}

void emManager::removeEnemy(int id) {
    Entry* entry = getEntryEnemyPtrFromId(id);
    if (entry != nullptr && entry->m_dataPtr != nullptr) {
        Enemy::remove(static_cast<Enemy*>(entry->m_dataPtr));
        forEachEnemy(id, clearParentCallback);
        entry->clear();
    }
}

void emManager::forEachEnemy(u32 createId, bool (*func)(int, int)) {
    if (createId == 0xFFFF) {
        return;
    }
    for (u32 i = 0; i < m_numEnemyEntries; i++) {
        if (i == createId) {
            continue;
        }
        Entry* entry = getEnemyEntry(i);
        if (entry != nullptr && entry->m_isActive) {
            if (!func(createId, entry->m_createId)) {
                return;
            }
        }
    }
}

void emManager::removeEnemyAll() {
    for (u32 i = 0; i < m_numEnemyEntries; i++) {
        Entry* entry = getEnemyEntry(i);
        if (entry != nullptr && entry->m_isActive == true) {
            removeEnemy(entry->m_createId);
        }
    }
}

emManager::Entry* emManager::getEnemyEntry(u32 index) const {
    if (index >= m_numEnemyEntries) {
        return nullptr;
    }
    return &m_enemyEntries[index];
}

emManager::Entry* emManager::getEntryEnemyPtrFromId(u32 createId) const {
    if (createId == 0xFFFF) {
        return nullptr;
    }
    for (u32 i = 0; i < m_numEnemyEntries; i++) {
        Entry* entry = getEnemyEntry(i);
        if (entry != nullptr && entry->m_isActive && entry->m_createId == createId) {
            return entry;
        }
    }
    return nullptr;
}

int emManager::getEmptyEnemyEntryIndex() const {
    for (u32 i = 0; i < m_numEnemyEntries; i++) {
        Entry* entry = getEnemyEntry(i);
        if (entry != nullptr && !entry->m_isActive) {
            return i;
        }
    }
    return -1;
}

Enemy* emManager::getEnemyPtrFromId(int createId) const {
    Entry* entry = getEntryEnemyPtrFromId(createId);
    if (entry == nullptr) {
        return nullptr;
    }
    if (entry->m_isActive == false) {
        return nullptr;
    }
    return static_cast<Enemy*>(entry->m_dataPtr);
}

Enemy* emManager::getEnemyPtr(int createId) const {
    return static_cast<Enemy*>(getEntryEnemyPtrFromId(createId)->m_dataPtr);
}

bool emManager::isEnemyCreatable() const {
    return getEmptyEnemyEntryIndex() >= 0;
}

u32 emManager::getEnemyCount() const {
    u32 count = 0;
    for (u32 i = 0; i < m_numEnemyEntries; i++) {
        Entry* entry = getEnemyEntry(i);
        if (entry != nullptr && entry->m_isActive) {
            count++;
        }
    }
    return count;
}

u32 emManager::getEnemyCountFromKind(EnemyKind enemyKind) const {
    u32 count = 0;
    if (emInfo::getInstance()->isInvalidKind(enemyKind) == true) {
        return 0;
    }
    for (u32 i = 0; i < m_numEnemyEntries; i++) {
        Entry* entry = getEnemyEntry(i);
        if (entry != nullptr && entry->m_isActive) {
            Enemy* enemy = static_cast<Enemy*>(entry->m_dataPtr);
            if (enemy != nullptr && enemyKind == enemy->getEnemyKind()) {
                count++;
            }
        }
    }
    return count;
}

int emManager::getParentCreateIdFromId(u32 createId) const {
    if (createId == 0xFFFF) {
        return 0xFFFF;
    }
    Entry* entry = getEntryEnemyPtrFromId(createId);
    if (entry == nullptr) {
        return 0xFFFF;
    }
    if (entry->m_isActive == false) {
        return 0xFFFF;
    }
    return entry->m_parentCreateId;
}

bool emManager::isEnemyExist(u32 id) const {
    if (id == 0xFFFF) {
        return false;
    }
    Entry* entry = getEntryEnemyPtrFromId(id);
    if (entry == nullptr) {
        return false;
    }
    if (entry->m_isActive == false) {
        return false;
    }
    return entry->m_dataPtr;
}

int emManager::getEnemyCreateIdFromAreaId(int areaId) const {
    for (u32 i = 0; i < m_numEnemyEntries; i++) {
        Entry* entry = getEnemyEntry(i);
        if (entry != nullptr && entry->m_isActive) {
            Enemy* enemy = static_cast<Enemy*>(entry->m_dataPtr);
            if (enemy != nullptr && soExternalValueAccesser::getAreaIndexFromId(enemy, areaId) != -1) {
                return entry->m_createId;
            }
        }
    }
    return 0xFFFF;
}

void emManager::Entry::set(void* dataPtr, EnemyKind enemyKind, int createId, int soundGroupOffset) {
    clear();
    m_dataPtr = dataPtr;
    m_isActive = true;
    m_enemyKind = enemyKind;
    m_parentCreateId = 0xFFFF;
    m_createId = createId;
    m_soundGroupOffset = soundGroupOffset;
}

#ifdef MATCHING
int emManager::preloadArchive(gfArchive* param, gfArchive* brres, gfArchive* enmCommon, gfArchive* primFaceBrres, EnemyKind enemyKind, bool isSoundRequest) {
#else
int emManager::preloadArchive(gfArchive* param, gfArchive* brres, gfArchive* enmCommon, gfArchive* primFaceBrres, EnemyKind enemyKind, bool isSoundRequest, HeapType heapType) {
#endif
    if (emInfo::getInstance()->isInvalidKind(enemyKind) == true) {
        return -2;
    }
    if (getPreloadArchiveCountFromKind(enemyKind) >= 1) {
        return -1;
    }
    int index = getEmptyPreloadArchiveEntryIndex();
    if (index < 0) {
        return -3;
    }
    Entry* entry = getPreloadArchiveEntry(index);
    if (entry == nullptr) {
        return -3;
    }
    int createId = getNextArchiveCreateId();
    emArchive* archive = new (Heaps::EnemyInstance) emArchive(param, brres, enmCommon, primFaceBrres, enemyKind);
    if (archive == nullptr) {
        return -4;
    }
    u32 seId = emInfo::getInstance()->getSEId(enemyKind);
    int soundGroupOffset = -2;
    if (seId != -1) {
        soundGroupOffset = g_sndSystem->loadSoundGroup(static_cast<SndGroupID>(seId), 0xC, isSoundRequest);
        if (soundGroupOffset == -2) {
            return -4;
        }
    }
    entry->set(archive, enemyKind, createId, soundGroupOffset);
    return createId;
}

bool emManager::isCompArchive(int id) const {
    Entry* entry = getEntryPreloadArchivePtrFromId(id);
    if (entry == nullptr) {
        return false;
    }
    emArchive* archive = static_cast<emArchive*>(entry->m_dataPtr);
    if (archive == nullptr) {
        return false;
    }
    if (!archive->isComp()) {
        return false;
    }
    if (entry->m_soundGroupOffset >= 0) {
        u32 seId = emInfo::getInstance()->getSEId(entry->m_enemyKind);
        if (seId != -1 && !g_sndSystem->isSoundGroupLoadFinished(static_cast<SndGroupID>(seId))) {
            return false;
        }
    }
    return true;
}

bool emManager::isCompArchiveAll() const {
    for (u32 i = 0; i < m_numArchiveEntries; i++) {
        Entry* entry = getPreloadArchiveEntry(i);
        if (entry != nullptr && entry->m_isActive) {
            if (!isCompArchive(entry->m_createId)) {
                return false;
            }
        }
    }
    return true;
}

void emManager::removeArchive(int id) {
    Entry* entry = getEntryPreloadArchivePtrFromId(id);
    if (entry != nullptr && entry->m_dataPtr != nullptr) {
        delete static_cast<emArchive*>(entry->m_dataPtr);
        if (entry->m_soundGroupOffset >= 0) {
            g_sndSystem->freeGroup(entry->m_soundGroupOffset, 0xC);
        }
        entry->clear();
    }
}

void emManager::removeArchiveAll() {
    for (u32 i = 0; i < m_numArchiveEntries; i++) {
        Entry* entry = getPreloadArchiveEntry(i);
        if (entry != nullptr && entry->m_isActive == true) {
            removeArchive(entry->m_createId);
        }
    }
}

emManager::Entry* emManager::getPreloadArchiveEntry(u32 index) const {
    if (index >= m_numArchiveEntries) {
        return nullptr;
    }
    return &m_archiveEntries[index];
}

emManager::Entry* emManager::getEntryPreloadArchivePtrFromId(u32 createId) const {
    for (u32 i = 0; i < m_numArchiveEntries; i++) {
        Entry* entry = getPreloadArchiveEntry(i);
        if (entry != nullptr && entry->m_isActive && entry->m_createId == createId) {
            return entry;
        }
    }
    return nullptr;
}

int emManager::getEmptyPreloadArchiveEntryIndex() const {
    for (u32 i = 0; i < m_numArchiveEntries; i++) {
        Entry* entry = getPreloadArchiveEntry(i);
        if (entry != nullptr && !entry->m_isActive) {
            return i;
        }
    }
    return -1;
}

u32 emManager::getPreloadArchiveCountFromKind(EnemyKind enemyKind) const {
    u32 count = 0;
    if (emInfo::getInstance()->isInvalidKind(enemyKind) == true) {
        return 0;
    }
    for (u32 i = 0; i < m_numArchiveEntries; i++) {
        Entry* entry = getPreloadArchiveEntry(i);
        if (entry != nullptr && entry->m_isActive && entry->m_dataPtr != nullptr && entry->m_enemyKind == enemyKind) {
            count++;
        }
    }
    return count;
}

emArchive* emManager::getPreloadArchivePtrFromKind(EnemyKind enemyKind) const {
    if (emInfo::getInstance()->isInvalidKind(enemyKind) == true) {
        return nullptr;
    }
    for (u32 i = 0; i < m_numArchiveEntries; i++) {
        Entry* entry = getPreloadArchiveEntry(i);
        if (entry != nullptr && entry->m_isActive) {
            emArchive* archive = static_cast<emArchive*>(entry->m_dataPtr);
            if (archive != nullptr && entry->m_enemyKind == enemyKind) {
                return archive;
            }
        }
    }
    return nullptr;
}

int emManager::getPreloadArchiveCreateIdFromKind(EnemyKind enemyKind) const {
    if (emInfo::getInstance()->isInvalidKind(enemyKind) == true) {
        return 0;
    }
    for (u32 i = 0; i < m_numArchiveEntries; i++) {
        Entry* entry = getPreloadArchiveEntry(i);
        if (entry != nullptr && entry->m_isActive && entry->m_enemyKind == enemyKind) {
            return entry->m_createId;
        }
    }
    return -5;
}
