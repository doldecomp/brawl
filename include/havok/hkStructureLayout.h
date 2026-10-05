#pragma once

#include <havok/hkArray.h>
#include <havok/hkClass.h>
#include <havok/hkMap.h>

// Computes member offsets / object sizes of reflected classes for a given target platform layout.
struct hkStructureLayout {
    struct LayoutRules {
        u8 m_bytesInPointer;                 // 0x00
        hkBool m_littleEndian;               // 0x01
        u8 m_reusePaddingOptimization;       // 0x02
        u8 m_emptyBaseClassOptimization;     // 0x03
    };

    LayoutRules m_rules;  // 0x00

    static LayoutRules HostLayoutRules;

    hkStructureLayout();
    void computeMemberOffsetsInplace(hkClass* klass, hkPointerMapBase<hkUlong>& done);
};
