#pragma once

#include <gf/gf_thread.h>
#include <types.h>

// TODO: fields might be public and/or volatile
class gfMonitorThread : public gfThread {
    u32 unk340;
    u8 unk344[0x4];
    s64 m_lastDrawTime;
    bool unk350_b7 : 1;
    bool unk350_b6 : 1;
public:
    virtual void run();
};
// TODO size assertion
