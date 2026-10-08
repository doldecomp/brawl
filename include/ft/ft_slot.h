#pragma once

// Local shadow of BrawlHeaders' ft/ft_slot.h (include/ comes first on the include path): same layout, plus the
// member functions the fighter manager calls. A slot holds the loaded resources (models, motions, sounds) of one
// player's chosen character, one slot per player (0x4D4 bytes each, array in ftSlotManager).

#include <StaticAssert.h>
#include <types.h>
#include <gm/gm_lib.h>
#include <memory.h>

class ftSlot {
public:
    virtual ~ftSlot();
    char _0x15b[0x157];
    u8 m_costumeId;
    u8 m_isUnused; // HYPOTHESIS: the slot is not assigned to any player (ftSlotManager::searchUnUseSlot looks for it)
    char _0x15d[3];
    gmCharacterKind m_characterKind;
    HeapType m_instanceHeapType;
    HeapType m_resourceHeapType;
    char _0x16c[8];
    int m_slotNo;
    char _0x178[0x354];
    HeapType m_pokeTrainerInstanceHeap; // 0x4CC, read by ftManager::getPokeTrainerInstanceHeap
    char _0x4d0[4];

    bool isReady();
    bool isReadyRemove();
    bool isReadyKirbyCopyResource(int kirbyKind, int unk);
    bool isLoaded(u32 flags);
    // Loads a resource group; the fighter manager passes 0x2000 for entry and 0x4000 for result resources.
    void notifyKirbyCopySetup(int unk);
    void notifyKirbyCopyCancel(int unk);
    int getKirbyResourceCount();
    int getKirbyResourceKind(int index);
    void load(int resId, u32 flags, int unk);
    void loadBootResource2ndary(int resId);
    void pushItem(int itemId);
    void remove(int resId, u32 flags, int unk);
    void removeAll();
};
static_assert(sizeof(ftSlot) == 0x4d4, "Class is wrong size!");
