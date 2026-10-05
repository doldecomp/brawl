#pragma once

#include <havok/hkClass.h>
#include <types.h>

extern const hkClass hkMultiThreadLockClass;

// Debug lock used to detect unsynchronised multi-threaded access to Havok objects.
struct hkMultiThreadLock {
    enum AccessType {
        HK_ACCESS_IGNORE = 0,
        HK_ACCESS_RO = 1,
        HK_ACCESS_RW = 2,
    };
    enum ReadMode {
        THIS_OBJECT_ONLY = 0,
        RECURSIVE = 1,
    };

    u32 m_threadId;     // 0x00
    u16 m_lockCount;    // 0x04
    u16 m_lockBitStack; // 0x06

    static void staticInit();
    static void staticQuit();
    void disableChecks();

    static struct hkMultiThreadLockMarker* s_checkBuffer;
};
