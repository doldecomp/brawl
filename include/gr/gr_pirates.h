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
};
static_assert(sizeof(grPirates) == 0x160, "grPirates layout");
