#include <so/so_heap_module_impl.h>
#include <sr/sr_common.h>
#include <types.h>

soHeapModuleImpl::soHeapModuleImpl(Heaps::HeapType instHeap,
        Heaps::HeapType modelInstHeap, Heaps::HeapType motionInstHeap,
        s32 heapSlotNo) {
    m_instanceHeap = instHeap;
    m_modelInstanceHeap = modelInstHeap;
    m_motionInstanceHeap = motionInstHeap;
    m_heapSlotNo = heapSlotNo;
}
