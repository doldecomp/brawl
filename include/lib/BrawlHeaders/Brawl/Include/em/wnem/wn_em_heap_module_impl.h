#pragma once

#include <StaticAssert.h>
#include <so/so_heap_module.h>
#include <so/so_null.h>
#include <sr/sr_common.h>
#include <types.h>

class wnemHeapModuleImpl : public soHeapModule {
    HeapType unk8;
    HeapType unkC;
public:
    wnemHeapModuleImpl(HeapType p1, HeapType p2);
    virtual ~wnemHeapModuleImpl();
    virtual HeapType getInstanceHeap() const { return unk8; }
    virtual HeapType getNWModelInstanceHeap() const { return unkC; }
    virtual HeapType getNWMotionInstanceHeap() const { return unk8; }
    virtual u32 getSlotNo() const;
};
static_assert(sizeof(wnemHeapModuleImpl) == 0x10, "Class is wrong size!");

extern wnemHeapModuleImpl g_wnemHeapModule;
