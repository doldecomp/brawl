#include <havok/hkClass.h>

extern const hkClass hkClassVersion1Class;
extern const hkClass hkClassClass;
extern const hkClass hkClassEnumClass;
extern const hkClass hkClassMemberClass;

static const hkClassMember hkClassVersion1Class_Members[] = {
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"parent", &hkClassClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x4},
    {"objectSize", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"numImplementedInterfaces", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0xC},
    {"declaredEnums", &hkClassEnumClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x10},
    {"declaredMembers", &hkClassMemberClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x18},
    {"hasVtable", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x20},
};

const hkClass hkClassVersion1Class("hkClass", 0, 0x24, 0, 0, 0, 0, hkClassVersion1Class_Members, 7, 0);
