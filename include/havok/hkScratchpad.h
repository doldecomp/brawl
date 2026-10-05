#pragma once

#include <havok/hkSingleton.h>
#include <new>

struct hkScratchpad : hkSingleton<hkScratchpad> {
    char* m_buffer; // 0x08
    int m_size;     // 0x0C
    bool m_inUse;   // 0x10

    hkScratchpad() : m_buffer((char*)this + 0x20), m_size(0x4000), m_inUse(false) {}

    static hkScratchpad* create();
};

// Fake scratchpad: a plain heap block (header + 0x4000 byte buffer).
struct hkFakeScratchpad : hkScratchpad {};
