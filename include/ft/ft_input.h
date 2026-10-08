#pragma once

// Local shadow of BrawlHeaders' ft/ft_input.h: same layout, plus the fields and member functions the fighter manager uses.
// An ftInput is the controller (human pad or CPU) feeding one fighter entry.

#include <StaticAssert.h>
#include <types.h>

class ftEntry;

class ftInput {
public:
    bool unk0_80 : 1; // read by ftManager::getFighterOperationStatus
    bool unk0_40 : 1;
    bool unk0_20 : 1;
    bool unk0_10 : 1;
    bool unk0_08 : 1;
    bool unk0_04 : 1;
    bool unk0_02 : 1;
    bool unk0_01 : 1;
    char _0x1[3];
    ftEntry* m_entry;
    u8 unk8;
    char _0x9[23];

    void setWhole(int status);
    int getType();
    void setType(s8 type);
    void setCpuType(int cpuType);
};
static_assert(sizeof(ftInput) == 0x20, "Class is wrong size!");
