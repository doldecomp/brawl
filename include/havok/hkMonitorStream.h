#pragma once

#include <havok/hkMemory.h>

// Per-thread performance monitor stream (timer begin/end commands).
struct hkMonitorStream {
    char* m_start;        // 0x00
    char* unk4;           // 0x04
    char* unk8;           // 0x08
    char* unkC;           // 0x0C
    hkBool m_isBufferAllocatedOnHeap; // 0x10

    hkMonitorStream() {}

    static void init();
    void quit();

    static hkMonitorStream s_instance;
};
