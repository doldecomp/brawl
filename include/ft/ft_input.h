#pragma once

// Local shadow of BrawlHeaders' ft/ft_input.h: same layout, plus the fields and member functions the fighter manager uses.
// An ftInput is the controller (human pad or CPU) feeding one fighter entry.

#include <StaticAssert.h>
#include <types.h>

class ftEntry;

// HYPOTHESIS: the controller object behind ftInput::getInput; its vtable pointer sits at +4 and the rumble calls
// are virtual slots 7 and 10 (offsets 0x24 and 0x30 in the vtable).
class ftInputController {
public:
    int unk0;
    virtual void unk_v0();
    virtual void unk_v1();
    virtual u64 getButtons1();
    virtual u64 getButtons0();
    virtual int getControllerKind();
    virtual void unk_v5();
    virtual void unk_v6();
    virtual void setRumble(int unk1, int unk2, int unk3, u8 unk4);
    virtual void unk_v8();
    virtual void unk_v9();
    virtual void stopRumble(int unk1, int unk2);
};

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

    ftInputController* getInput();
    void setWhole(int status);
    int getType();
    void setType(s8 type);
    void setCpuType(int cpuType);
};
static_assert(sizeof(ftInput) == 0x20, "Class is wrong size!");
