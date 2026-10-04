#pragma once

#include <ft/ft_class_info.h>
#include <ft/ft_entry.h>
#include <sr/sr_common.h>
#include <types.h>

// Per-character class info. Registers itself in the class info table on construction
// and creates the fighter object on demand.
//   K: fighter kind, T: fighter class (e.g. ftMarth)
template <ftKind K, class T>
class ftClassInfoImpl : public ftClassInfo {
public:
    ftClassInfoImpl() {
        setClassInfo(K, this);
    }

    virtual ~ftClassInfoImpl() {
        setClassInfo(K, &g_ftClassInfoNull);
    }

    virtual Fighter* create(s32 entryId,
                            Heaps::HeapType instHeap,
                            Heaps::HeapType nwModelInstHeap,
                            Heaps::HeapType nwMotionInstHeap) const {
        return new (instHeap) T(entryId, instHeap, nwModelInstHeap, nwMotionInstHeap);
    }
};
