#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class ftSlotManager {
public:
class FlexHeapInfo {
public:
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkc;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
};
};
static_assert(sizeof(ftSlotManager::FlexHeapInfo) == 24, "Class is wrong size!");
