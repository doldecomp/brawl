#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <gm/gm_lib.h>
#include <memory.h>

class ftSlot {
public:
    virtual ~ftSlot();
    char _0x15b[0x157];
    u8 m_costumeId;
    u8 _0x15c;
    char _0x15d[3];
    gmCharacterKind m_characterKind;
    HeapType m_instanceHeapType;
    HeapType m_resourceHeapType;
    char _0x16c[8];
    int m_slotNo;
    char _0x178[0x35C];
};
static_assert(sizeof(ftSlot) == 0x4d4, "Class is wrong size!");