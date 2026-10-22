#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <ft/ft_slot.h>

class ftSlotManager;
extern ftSlotManager* g_ftSlotManager;
class ftSlotManager {
public:
    ftSlot* m_slots;
    u32 m_slotCount;
    char _0x8[0x538];

    inline static ftSlotManager* getInstance() { return g_ftSlotManager; }
};
static_assert(sizeof(ftSlotManager) == 0x540, "Class is wrong size!");

