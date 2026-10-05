#include <havok/hkScratchpad.h>

hkScratchpad* hkScratchpad::create() {
    hkFakeScratchpad* p =
        (hkFakeScratchpad*)hkMemory::getInstance().allocateChunk(0x4020, HK_MEMORY_CLASS_BASE);
    p->m_memSizeAndFlags = 0x4020;
    ::new (p) hkFakeScratchpad();
    return p;
}

static hkSingletonInitNode hkScratchpad_initNode((void* (*)())hkScratchpad::create,
                                          (void**)&hkSingleton<hkScratchpad>::s_instance);

template <>
hkScratchpad* hkSingleton<hkScratchpad>::s_instance = 0;
