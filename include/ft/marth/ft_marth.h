#pragma once

#include <ft/fighter.h>
#include <sr/sr_common.h>
#include <types.h>

class ftMarth : public Fighter {
    u8 unk194[0x8574 - 0x194];
public:
    ftMarth(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
