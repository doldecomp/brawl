#include <havok/hkClass.h>

extern const hkClass hkWorldObjectClass;
extern const hkClass hkLinkedCollidableClass;
extern const hkClass hkMultiThreadLockClass;
extern const hkClass hkPropertyClass;
extern const hkClass hkReferencedObjectClass;

static const hkClassEnumItem hkWorldObjectBroadPhaseTypeEnumItems[] = {
    {0, "BROAD_PHASE_INVALID"},
    {1, "BROAD_PHASE_ENTITY"},
    {2, "BROAD_PHASE_PHANTOM"},
    {3, "BROAD_PHASE_BORDER"},
    {4, "BROAD_PHASE_MAX_ID"},
};

static const hkClassEnum hkWorldObjectClass_Enums[] = {
    {"BroadPhaseType", hkWorldObjectBroadPhaseTypeEnumItems, 5},
};

static const hkClassMember hkWorldObjectClass_Members[] = {
    {"world", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x8},
    {"userData", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0xC},
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"multithreadLock", &hkMultiThreadLockClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x14},
    {"collidable", &hkLinkedCollidableClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x1C},
    {"properties", &hkPropertyClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x4C},
};

const hkClass hkWorldObjectClass("hkWorldObject", &hkReferencedObjectClass, 0x58, 0, 0, hkWorldObjectClass_Enums, 1, hkWorldObjectClass_Members, 6, 0);
