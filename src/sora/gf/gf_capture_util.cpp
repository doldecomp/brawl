#include <gf/gf_capture_util.h>
#include <gf/gf_heap_manager.h>
#include <revolution/TMCC_JPEG/encapi.h>
#include <sr/sr_common.h>

void gfJpegEncodeWork::run() {
    void* r31 = gfHeapManager::alloc(unk340_2, 0x1C00);
    unk340_1 = 1;
    s32 local10;
    do {
        TMCCJPEGEncGetQFactor(r31, unk350, unk342, unk344, unk348, unk34C, &unk354, &local10);
        if (unk354 > unk34C) {
            unk34C -= 0x2800;
        }
    } while (unk354 > unk34C);
    TMCCJPEGEncEncode(r31, unk350, unk342, unk344, unk348, local10, unk358, unk34C, &unk354);
    gfHeapManager::free(r31);
    unk340_1 = 2;
}
