#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <memory.h>
#include <ft/ft_entry.h>
#include <ft/fighter.h>

struct ftCreate {
    int m_entryId;
    ftKind m_kind;
    HeapType m_instanceHeapType;
    HeapType m_nwModelInstanceHeapType;
    HeapType m_nwMotionInstanceHeapType;
};

class ftInstanceManager;
extern ftInstanceManager g_ftInstanceManager;
class ftInstanceManager {
    char _0x0[0x18c];
public:
    Fighter* create(ftCreate* create);

    inline static ftInstanceManager* getInstance() { return &g_ftInstanceManager; }
};
static_assert(sizeof(ftInstanceManager) == 0x18c, "Class is wrong size!");

