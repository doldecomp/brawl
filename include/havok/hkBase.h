#pragma once

#include <types.h>

// Havok 4.0 base object hierarchy (reconstructed from asm).
// No RTTI: vtable slot 0/1 are unused, slot 2 is the virtual destructor.
typedef int hkResult;
enum { HK_SUCCESS = 0, HK_FAILURE = 1 };

struct hkStatisticsCollector;

struct hkBaseObject {
    virtual ~hkBaseObject();
};

struct hkReferencedObject : hkBaseObject {
    u16 m_memSizeAndFlags; // 0x04
    s16 m_referenceCount;  // 0x06

    virtual ~hkReferencedObject();
    virtual void calcStatistics(hkStatisticsCollector* collector) const;
};
