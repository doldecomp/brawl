#pragma once

// Local shadow of BrawlHeaders: restore the photo-controller callback slots.
#include <StaticAssert.h>
#include <ut/ut_list.h>

class cmPhotoCallBack : public utListNode {
public:
    cmPhotoCallBack();
#if defined(FT_MARTH_PHOTO_CALLBACK_NOINLINE) && defined(FT_REL_LINK_EXTERN)
    virtual ~cmPhotoCallBack(); // MATCH-ONLY: Marth calls the sora_melee destructor (out of line, no weak copy here).
#else
    virtual ~cmPhotoCallBack()
#ifdef FT_MARTH_PHOTO_CALLBACK_NOINLINE
        __attribute__((never_inline)) // MATCH-ONLY: Marth tears down the photo base out of line.
#endif
    { }
#endif
#if defined(FT_MARTH_PHOTO_CALLBACK_NOINLINE) && defined(FT_REL_LINK_EXTERN)
    // MATCH-ONLY/HYPOTHESIS: pure in the REL (the weak soPhotoCallBack vtable has zero words in both slots).
    virtual void photoMoved() = 0;
    virtual void photoExit() = 0;
#else
    virtual void photoMoved();
    virtual void photoExit();
#endif
};

class soPhotoCallBack : public cmPhotoCallBack {
public:
    virtual ~soPhotoCallBack() { }
    void addCallback();
    void removeCallBack();
};
static_assert(sizeof(soPhotoCallBack) == 0xc, "Class is the wrong size!");
