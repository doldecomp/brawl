#include <havok/hkMultiThreadLock.h>
#include <havok/hkMemory.h>

// HYPOTHESIS: one byte marker object allocated while thread checking is initialised.
struct hkMultiThreadLockMarker {
    char m_dummy;

    static void* operator new(unsigned long nbytes) {
        return hkMemory::getInstance().allocateChunk(nbytes, 0x13);
    }
    static void operator delete(void* p) {
        hkMemory::getInstance().deallocateChunk(p, sizeof(hkMultiThreadLockMarker), 0x13);
    }
    hkMultiThreadLockMarker() {}

    static void release(hkMultiThreadLockMarker* p) {
        if (p != 0) {
            operator delete(p);
        }
    }
};

hkMultiThreadLockMarker* hkMultiThreadLock::s_checkBuffer = 0;

void hkMultiThreadLock::staticInit() {
    s_checkBuffer = new hkMultiThreadLockMarker();
}

void hkMultiThreadLock::staticQuit() {
    if (s_checkBuffer != 0) {
        hkMultiThreadLockMarker::release(s_checkBuffer);
        s_checkBuffer = 0;
    }
}

void hkMultiThreadLock::disableChecks() {
    m_threadId = 0xFFFFFFD1;
}

static const hkClassEnumItem hkMultiThreadLockAccessTypeEnumItems[] = {
    {0, "HK_ACCESS_IGNORE"},
    {1, "HK_ACCESS_RO"},
    {2, "HK_ACCESS_RW"},
};

static const hkClassEnumItem hkMultiThreadLockReadModeEnumItems[] = {
    {0, "THIS_OBJECT_ONLY"},
    {1, "RECURSIVE"},
};

static const hkClassEnum hkMultiThreadLockClass_Enums[] = {
    {"AccessType", hkMultiThreadLockAccessTypeEnumItems, 3},
    {"ReadMode", hkMultiThreadLockReadModeEnumItems, 2},
};

static const hkClassMember hkMultiThreadLockClass_Members[] = {
    {"threadId", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_UINT32, 0, 0, 0x0},
    {"lockCount", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_INT16, 0, 0, 0x4},
    {"lockBitStack", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_UINT16, 0, 0, 0x6},
};

const hkClass hkMultiThreadLockClass("hkMultiThreadLock", 0, 8, 0, 0, hkMultiThreadLockClass_Enums, 2,
                                     hkMultiThreadLockClass_Members, 3, 0);
