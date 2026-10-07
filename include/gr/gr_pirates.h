#pragma once

#include <gr/gr_yakumono.h>

// Layout verified against the Pirate Ship ground constructor and update routines.
class grPirates : public grYakumono {
protected:
    u8 m_state;                // 0x150
    u8 unk151[3];
    float m_timer;             // 0x154
    u32 unk158;
    u32 unk15C;

public:
    // Verified appended vtable entries; work pointers remain opaque.
    virtual void setCtrlFrame(void* frame);
    virtual void setEventTotalFrame(void* frame);
    virtual void updateYakumono(float deltaFrame);
    virtual void updateJoint(float deltaFrame);
    virtual void updateCollision(float deltaFrame);
    virtual void updateActive(float deltaFrame);
    virtual void updateSE(float deltaFrame);
    virtual void updateAI(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setHit();
    virtual void setAttack();
    virtual void setMotion(u32 motion, u32 loop, bool force, float* endFrame);
};
static_assert(sizeof(grPirates) == 0x160, "grPirates layout");
