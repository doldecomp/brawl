#pragma once
#include <gr/gr_yakumono.h>

// Common layout and virtual entries verified against Pirate Ship ground objects.
class grPirates : public grYakumono {
protected:
    u8 m_state;
    u8 unk151[3];
    float m_timer;
    float* m_ctrlFrame;
    void* unk15C;
public:
    virtual ~grPirates();
    virtual void setCtrlFrame(void* frame);
    virtual void setEventTotalFrame(void* frame);
};
static_assert(sizeof(grPirates) == 0x160, "grPirates layout");
