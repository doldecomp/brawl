#pragma once

#include <StaticAssert.h>
#include <em/em_archive.h>
#include <em/enemy.h>
#include <types.h>

class emManager {

    template <typename T>
    class Entry {
        char _0[0x4];
        EnemyKind m_enemyKind;
        int m_parentCreateId;
        int m_createId;
        int m_soundGroupOffset;
        T* m_dataPtr;
    };
    static_assert(sizeof(Entry<Enemy>) == 0x18, "Class is wrong size!");

    u32 m_numEnemyEntries;
    Entry<Enemy>* m_enemyEntries;
    char _8[4];
    u32 m_numArchiveEntries;
    Entry<emArchive>* m_archiveEntries;
    char _20[4];
    u8 m_primidFaceType;
    char _25[3];

    virtual ~emManager();

public:
    bool isCompArchive(int id);
    bool isCompArchiveAll();
    int getPreloadArchiveCountFromKind(EnemyKind enemyKind);
    int getPreloadArchiveCreateIdFromKind(EnemyKind enemyKind);
    emArchive* getPreloadArchivePtrFromKind(EnemyKind enemyKind);
#ifdef MATCHING
    int preloadArchive(gfArchive* param, gfArchive* brres, gfArchive* enmCommon, gfArchive* primFaceBrres, EnemyKind enemyKind, bool isSoundRequest);
#else
    int preloadArchive(gfArchive* param, gfArchive* brres, gfArchive* enmCommon, gfArchive* primFaceBrres, EnemyKind enemyKind, bool isSoundRequest, HeapType heapType = Heaps::StageResource); // Custom optional parameters for specifying what heap to load enemy resources into
#endif
    int createEnemy(emCreate* create);
    void removeEnemy(int id);
    bool isEnemyExist(int id);
    void removeEnemyAll();
    void removeArchiveAll();
    void removeArchive(int id);
    static void create(u32 numEntries1, u32 numEntries2, u8 primidFaceType);
    static void remove();
    u32 getEnemyCount();
    u32 getEnemyCountFromKind(EnemyKind enemyKind);
    Enemy* getEnemyPtrFromId(int createId);
    Entry<emArchive>* getEntryPreloadArchivePtrFromId(int createId);
    static emManager* getInstance();
};
static_assert(sizeof(emManager) == 32, "Class is wrong size!");
