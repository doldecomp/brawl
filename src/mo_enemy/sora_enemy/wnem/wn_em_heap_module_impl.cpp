#include <sr/sr_common.h>
#include <em/wnem/wn_em_heap_module_impl.h>

wnemHeapModuleImpl g_wnemHeapModule(Heaps::WeaponInstance, Heaps::StageResource);

wnemHeapModuleImpl::wnemHeapModuleImpl(HeapType p1, HeapType p2)
    : unk8(p1), unkC(p2) { }

// Note: This emits the code for soHeapModule's inlined methods
static void unused() {
    wnemHeapModuleImpl m(Heaps::SystemFW, Heaps::SystemFW);
    m.setInstanceHeap(Heaps::SystemFW);
}

u32 wnemHeapModuleImpl::getSlotNo() const { return 0; }

#pragma dont_inline on
wnemHeapModuleImpl::~wnemHeapModuleImpl() { }
#pragma dont_inline reset
