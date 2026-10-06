#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class ftAreaModuleImpl {
public:
class GimmickTermInfo {
public:
    struct { u32 unk0, unk4; } unk0;
    struct { u32 unk0, unk4; } unk8;
    u32 unk10;
    struct { u32 unk0, unk4; } unk14;
    struct { u32 unk0, unk4; } unk1c;
    struct { u32 unk0, unk4; } unk24;
    u8 unk2c;
    u16 unk2e;
};
};
static_assert(sizeof(ftAreaModuleImpl::GimmickTermInfo) == 48, "Class is wrong size!");
