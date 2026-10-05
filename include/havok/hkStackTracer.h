#pragma once

#include <havok/hkMemory.h>

// Stack tracing stub (no stack walking on this platform).
struct hkStackTracer : hkReferencedObject {
    HK_DECLARE_REF_ALLOCATOR(0x13)

    hkStackTracer();
    virtual ~hkStackTracer();

    typedef void (*OutputFunc)(const char* text, void* context);

    void dumpStackTrace(const unsigned long* trace, int numTrace, OutputFunc output, void* context);
    int getStackTrace(unsigned long* trace, int maxTrace);
};
