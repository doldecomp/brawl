#include <em/wnem/wn_em_heap_module_impl.h>

wnemHeapModuleImpl g_wnemHeapModule(Heaps::WeaponInstance, Heaps::StageResource);

wnemHeapModuleImpl::wnemHeapModuleImpl(HeapType p1, HeapType p2)
    : unk8(p1), unkC(p2) { }
