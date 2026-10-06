#pragma once

#include <StaticAssert.h>
#include <types.h>

// Local copy layout used only by abstract array instantiations; SDK unchanged.
// HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
class soArticleEventObserverCopyBase { public: virtual ~soArticleEventObserverCopyBase(); };
class soArticleEventObserver : public soArticleEventObserverCopyBase {
public:
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u32 unkc;
};
static_assert(sizeof(soArticleEventObserver) == 16, "Class is wrong size!");
