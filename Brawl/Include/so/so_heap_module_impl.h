#pragma once

#include <StaticAssert.h>
#include <so/so_heap_module.h>
#include <sr/sr_common.h>
#include <types.h>

class soHeapModuleImpl : public soHeapModule {
    Heaps::HeapType m_instanceHeap;
    Heaps::HeapType m_modelInstanceHeap;
    Heaps::HeapType m_motionInstanceHeap;
    s32 m_heapSlotNo;
public:
    soHeapModuleImpl(Heaps::HeapType instHeap, Heaps::HeapType modelInstHeap,
            Heaps::HeapType motionInstHeap, s32 heapSlotNo);

    HeapType getInstanceHeap() const {
        return m_instanceHeap;
    }

    void setInstanceHeap(HeapType heap) {
        m_instanceHeap = heap;
    }

    HeapType getNWModelInstanceHeap() const {
        return m_modelInstanceHeap;
    }

    HeapType getNWMotionInstanceHeap() const {
        return m_motionInstanceHeap;
    }

    u32 getSlotNo() const {
        return m_heapSlotNo;
    }

    ~soHeapModuleImpl() { }
};
static_assert(sizeof(soHeapModuleImpl) == 0x18, "Class is wrong size!");
