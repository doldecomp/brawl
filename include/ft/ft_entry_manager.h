#pragma once

// Local shadow of BrawlHeaders' ft/ft_entry_manager.h: same layout, members made accessible to the fighter manager,
// plus the member functions it calls. An entry is one fighter participant (up to 9); the manager owns them.

#include <StaticAssert.h>
#include <types.h>
#include <ft/ft_entry.h>
#include <so/so_array.h>

class ftEntryManager;
extern ftEntryManager* g_ftEntryManager;
class ftEntryManager {
public:
    ftEntry* m_entries;
    u32 m_entryCount;
    soArrayVector<ftEntry*, 9> m_entryArrayVector;
    char _0x38[4];
    bool m_isProcessHeartSwap; // 0x3C
    char _0x3d[15];

    ftEntryManager(int entryCapacity);
    virtual ~ftEntryManager();

    ftEntry* getEntity(u32 entryId);
    bool isValid(int entryId);
    void startSwap(int entryId1, int entryId2);
    void endSwap(bool unk);
    void processHit();
    int enumEntryId(int entryId);
    int enumIncludeEntryId(int entryId);
    int getEntryIdFromPlayerNo(int playerNo);
    int getEntryIdFromAreaId(int areaId);
    int getEntryIdFromTaskId(int taskId, int* outInstanceIndex);

    inline static ftEntryManager* getInstance() { return g_ftEntryManager; }
};
static_assert(sizeof(ftEntryManager) == 0x50, "Class is wrong size!");
