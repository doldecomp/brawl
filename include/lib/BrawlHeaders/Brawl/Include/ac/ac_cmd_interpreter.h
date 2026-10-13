#pragma once

#include <StaticAssert.h>
#include <ac/ac_anim_cmd_impl.h>
#include <so/so_array.h>
#include <so/so_null.h>
#include <types.h>

// TODO: confirm whether this class is really needed
class acCmdInterpreterBase {
public:
    virtual bool dispatchCmdIf(const acAnimCmd* cmd);
    virtual s32 dispatchCmdSwitch(const acAnimCmd* cmd) const;
    virtual void interpretNotSystemCmd();
    virtual bool isBreakInterpret();
    virtual bool isSleepStackData(s32 kind) const;
    virtual bool isSkipEnd() const;
};

struct acCmdInterpreterStackData {
    // TODO: identify exact meaning of knd0 and knd7:
    // knd0: used for isBreakInterpret, Wait
    // knd7: if unk30Field2 = 2, used for Wait to determine how much to wait, if at all
    enum Kind {
        Invalid = -1,
        knd0 = 0,
        Frame = 1,
        Loop = 2,
        ReturnAddress = 3,
        IfCondition = 4,
        Switch = 5,
        While = 6,
        knd7 = 7,
    };

    acCmdInterpreterStackData(Kind knd = Invalid, s32 id = 0, bool bd = false,
                              const acAnimCmdConv* ad = nullptr, float fd = 0.0f) :
        kind(knd), intData(id), boolData(bd), addressData(ad), floatData(fd) { }

    Kind kind;
    s32 intData; // Loop count, or result of dispatchCmdSwitch
    bool boolData; // If condition result, "found Case" flag for Switch
    const acAnimCmdConv* addressData; // target address for jumps
    float floatData; // some data for wait time calculations
};

class acCmdInterpreter : private acCmdInterpreterBase {
    float m_fixedTimeStep;
    float m_lastTimeStep;
    const acAnimCmdConv* m_currentCmd;
    const acAnimCmdConv* m_copyCurrentCmd; // purpose unclear
    acAnimCmdImpl m_animCmd; // usually kept in sync with m_currentCmd
    soArrayVector<acCmdInterpreterStackData, 8>* m_stack;
    float m_currentFrame;
    float unk28;
    float m_overshoot;
    const s32 m_interpretMode:2; // -2 or -1 -> skip all commands, 0 -> use m_fixedTimeStep
    s32 unk30Field2:3; // related to isSkipEnd
    u8 m_dontAdvance;
    u8 unk32; // appears to be unused
    u8 m_reset;

public:
    acCmdInterpreter(soArrayVector<acCmdInterpreterStackData, 8>* stk,
        s32 mode, acAnimCmdConv* initCmd, const u8* resetMode, float fixedTimeStep);
    ~acCmdInterpreter();

    virtual bool dispatchCmdIf(const acAnimCmd* cmd) { return true; }
    virtual s32 dispatchCmdSwitch(const acAnimCmd* cmd) const;
    virtual void interpretNotSystemCmd();
    virtual bool isBreakInterpret();
    virtual bool isSleepStackData(s32 kind) const;
    virtual bool isSkipEnd() const;

    void interpretCmd(float timeStep);
    void resetInterpreter(float frame, const acAnimCmdConv *initCmd);
    void skipCmd();
    acCmdInterpreterStackData* getLastSystemStackData();
    void popSystemStack();
    void pushSystemStack(const acCmdInterpreterStackData& stackData);
    void skipNextIfGroup(bool skippingIfBlock);
    void skipNextSwitchGroup(bool doNotSkipCases);
    void skipNextNotSwitchGroup();
    void skipNextLoopGroup();
    void skipNextWhileGroup();
    const acAnimCmd* getCurrentCmd();
    bool testCurrentCmd() const;
    void advanceCurrentCmd();
    const acAnimCmd* updateCurrentCmd();
    s32 getIdxOfStackData(acCmdInterpreterStackData::Kind kind) const;
    void interpretOneCmd();
    void popStackToSize(s32 i);
    void systemCmdFuncWaitSub(float waitTime);
    void systemCmdFuncEnd();
    void systemCmdFuncWait();
    void systemCmdFuncFrame();
    void systemCmdFuncFrameClr();
    void systemCmdFuncLoop();
    void systemCmdFuncPool();
    void systemCmdFuncBreak();
    void systemCmdFuncCall();
    void systemCmdFuncReturn();
    void systemCmdFuncJump();
    void systemCmdFuncIf();
    void systemCmdFuncIfAnd();
    void systemCmdFuncIfOr();
    void systemCmdFuncElsIf();
    void systemCmdFuncElse();
    void systemCmdFuncEndIf();
    void systemCmdFuncSwitch();
    void systemCmdFuncCase();
    void systemCmdFuncDefault();
    void systemCmdFuncEndSwitch();
    void systemCmdFuncWhile();
    void systemCmdFuncWhileAnd();
    void systemCmdFuncWhileOr();
    void systemCmdFuncEndWhile();
    void systemCmdFuncBreakSwitch();
};
static_assert(sizeof(acCmdInterpreter) == 0x34, "Class is the wrong size!");
