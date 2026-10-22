#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <ft/ft_entry.h>
#include <so/so_array.h>

class ftEntryManager;
extern ftEntryManager* g_ftEntryManager;
class ftEntryManager {
    ftEntry* m_entries;
    u32 m_entryCount;
    soArrayVector<ftEntry*, 9> m_entryArrayVector;
    char _0x38[20];
public:
    virtual ~ftEntryManager();

    ftEntry* getEntity(u32 entryId);

    inline static ftEntryManager* getInstance() { return g_ftEntryManager; }
};
static_assert(sizeof(ftEntryManager) == 0x50, "Class is wrong size!");

