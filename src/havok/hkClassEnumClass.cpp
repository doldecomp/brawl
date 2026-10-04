#include <havok/hkClass.h>

extern const hkClass hkClassEnumClass;
extern const hkClass hkClassEnumItemClass;

static const hkClassMember hkClassEnumItemClass_Members[] = {
    {"value", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x4},
};

const hkClass hkClassEnumItemClass("hkClassEnumItem", 0, 0x8, 0, 0, 0, 0, hkClassEnumItemClass_Members, 2, 0);

static const hkClassMember hkClassEnumClass_Members[] = {
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"items", &hkClassEnumItemClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x4},
};

const hkClass hkClassEnumClass("hkClassEnum", 0, 0xC, 0, 0, 0, 0, hkClassEnumClass_Members, 2, 0);
