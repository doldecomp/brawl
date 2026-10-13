#pragma once

#include <types.h>

struct gfRumble {
    void lbSetRumble(s32, s32, s32, s32, s32);
    void lbStopRumble(s32);
    void HSD_PadRumbleRemove(s32);
    void HSD_PadRumbleRemoveId(s32, s32, s32);
    void HSD_PadRumbleRemoveMask(s32, u32);
};
// TODO size
