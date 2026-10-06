#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class ftInstanceManager {
public:
class InstanceInfo {
public:
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkc;
    u32 unk10;
    u32 unk14;
};
};
static_assert(sizeof(ftInstanceManager::InstanceInfo) == 24, "Class is wrong size!");
