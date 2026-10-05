#include <havok/hkClass.h>

extern const hkClass hkRootLevelContainerClass;
extern const hkClass hkRootLevelContainerNamedVariantClass;

static const hkClassMember hkRootLevelContainerNamedVariantClass_Members[] = {
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"className", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"variant", 0, 0, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkRootLevelContainerNamedVariantClass("hkRootLevelContainerNamedVariant", 0, 0x10, 0, 0, 0, 0, hkRootLevelContainerNamedVariantClass_Members, 3, 0);

static const hkClassMember hkRootLevelContainerClass_Members[] = {
    {"namedVariants", &hkRootLevelContainerNamedVariantClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x0},
};

const hkClass hkRootLevelContainerClass("hkRootLevelContainer", 0, 0x8, 0, 0, 0, 0, hkRootLevelContainerClass_Members, 1, 0);
