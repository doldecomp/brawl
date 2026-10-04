#include <havok/hkClass.h>

extern const hkClass hkClassClass;
extern const hkClass hkClassEnumClass;
extern const hkClass hkClassMemberClass;

static const hkClassEnumItem hkClassSignatureFlagsEnumItems[] = {
    {1, "SIGNATURE_LOCAL"},
};

static const hkClassEnum hkClassEnums[] = {
    {"SignatureFlags", hkClassSignatureFlagsEnumItems, 1},
};

static const hkClassMember hkClassClass_Members[] = {
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0},
    {"parent", &hkClassClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 4},
    {"objectSize", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 8},
    {"numImplementedInterfaces", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0xC},
    {"declaredEnums", &hkClassEnumClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x10},
    {"declaredMembers", &hkClassMemberClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x18},
    {"defaults", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x20},
};

const hkClass hkClassClass("hkClass", 0, sizeof(hkClass), 0, 0, hkClassEnums, 1, hkClassClass_Members, 7, 0);
