#pragma once

// Local shadow of BrawlHeaders: restore the photo-controller callback slots.
#include <StaticAssert.h>
#include <ut/ut_list.h>

class cmPhotoCallBack : public utListNode {
public:
    cmPhotoCallBack();
    virtual ~cmPhotoCallBack()
#ifdef FT_MARTH_PHOTO_CALLBACK_NOINLINE
        __attribute__((never_inline)) // MATCH-ONLY: Marth tears down the photo base out of line.
#endif
    { }
    virtual void photoMoved();
    virtual void photoExit();
};

class soPhotoCallBack : public cmPhotoCallBack {
public:
    virtual ~soPhotoCallBack() { }
    void addCallback();
    void removeCallBack();
};
static_assert(sizeof(soPhotoCallBack) == 0xc, "Class is the wrong size!");
