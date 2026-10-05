#include <havok/hkClass.h>

extern const hkClass hkPropertyClass;
extern const hkClass hkPropertyValueClass;

static const hkClassMember hkPropertyValueClass_Members[] = {
    {"data", 0, 0, hkClassMember::TYPE_UINT64, hkClassMember::TYPE_VOID, 0, 0, 0x0},
};

const hkClass hkPropertyValueClass("hkPropertyValue", 0, 0x8, 0, 0, 0, 0, hkPropertyValueClass_Members, 1, 0);

static const hkClassMember hkPropertyClass_Members[] = {
    {"key", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"alignmentPadding", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"value", &hkPropertyValueClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkPropertyClass("hkProperty", 0, 0x10, 0, 0, 0, 0, hkPropertyClass_Members, 3, 0);
