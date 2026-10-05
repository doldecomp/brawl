#include <havok/hkClass.h>

extern const hkClass hkMultiThreadLockClass;

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

const hkClass hkMultiThreadLockClass("hkMultiThreadLock", 0, 0x8, 0, 0, hkMultiThreadLockClass_Enums, 2, hkMultiThreadLockClass_Members, 3, 0);
