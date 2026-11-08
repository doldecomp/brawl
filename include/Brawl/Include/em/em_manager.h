#pragma once

#include <StaticAssert.h>
#include <em/em_archive.h>
#include <em/enemy.h>
#include <types.h>

class emManager {
public:
    class Entry {
    public:
        bool m_isActive;
        EnemyKind m_enemyKind;
        int m_parentCreateId;
        int m_createId;
        int m_soundGroupOffset;
        void* m_dataPtr;

        void clear();
        void set(void* dataPtr, EnemyKind enemyKind, int createId, int soundGroupOffset);
    };
    static_assert(sizeof(Entry) == 0x18, "Class is wrong size!");

private:
    u32 m_numEnemyEntries;
    Entry* m_enemyEntries;
    int m_nextEnemyCreateId;
    u32 m_numArchiveEntries;
    Entry* m_archiveEntries;
    int m_nextArchiveCreateId;
    u8 m_primidFaceType;
    char _25[3];

    emManager(u32 numEnemyEntries, Entry* enemyEntries, u32 numArchiveEntries, Entry* archiveEntries, u8 primidFaceType);
    virtual ~emManager();

    static bool clearParentCallback(int parentCreateId, int createId);
    int getNextEnemyCreateId() { return m_nextEnemyCreateId++; }
    int getNextArchiveCreateId() { return m_nextArchiveCreateId++; }

public:
    bool isCompArchive(int id) const;
    bool isCompArchiveAll() const;
    u32 getPreloadArchiveCountFromKind(EnemyKind enemyKind) const;
    int getPreloadArchiveCreateIdFromKind(EnemyKind enemyKind) const;
    emArchive* getPreloadArchivePtrFromKind(EnemyKind enemyKind) const;
#ifdef MATCHING
    int preloadArchive(gfArchive* param, gfArchive* brres, gfArchive* enmCommon, gfArchive* primFaceBrres, EnemyKind enemyKind, bool isSoundRequest);
#else
    int preloadArchive(gfArchive* param, gfArchive* brres, gfArchive* enmCommon, gfArchive* primFaceBrres, EnemyKind enemyKind, bool isSoundRequest, HeapType heapType = Heaps::StageResource); // Custom optional parameters for specifying what heap to load enemy resources into
#endif
    int createEnemy(emCreate* create);
    bool isParent(int parentCreateId, int createId) const;
    void forEachEnemy(u32 createId, bool (*func)(int, int));
    void removeEnemy(int id);
    bool isEnemyExist(u32 id) const;
    void removeEnemyAll();
    void removeArchiveAll();
    void removeArchive(int id);
    static void create(u32 numEntries1, u32 numEntries2, u8 primidFaceType);
    static void remove();
    u32 getEnemyCount() const;
    u32 getEnemyCountFromKind(EnemyKind enemyKind) const;
    Enemy* getEnemyPtrFromId(int createId) const;
    Enemy* getEnemyPtr(int createId) const;
    int getParentCreateIdFromId(u32 createId) const;
    int getEnemyCreateIdFromAreaId(int areaId) const;
    bool isEnemyCreatable() const;
    Entry* getEnemyEntry(u32 index) const;
    Entry* getEntryEnemyPtrFromId(u32 createId) const;
    int getEmptyEnemyEntryIndex() const;
    Entry* getPreloadArchiveEntry(u32 index) const;
    Entry* getEntryPreloadArchivePtrFromId(u32 createId) const;
    int getEmptyPreloadArchiveEntryIndex() const;
    static emManager* getInstance();
};
static_assert(sizeof(emManager) == 32, "Class is wrong size!");

extern emManager* g_emManager;
