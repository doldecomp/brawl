#include <havok/hkClass.h>

extern const hkClass hkCdBodyClass;
extern const hkClass hkShapeClass;

static const hkClassMember hkCdBodyClass_Members[] = {
    {"shape", &hkShapeClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x0},
    {"shapeKey", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"motion", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x8},
    {"parent", &hkCdBodyClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0xC},
};

const hkClass hkCdBodyClass("hkCdBody", 0, 0x10, 0, 0, 0, 0, hkCdBodyClass_Members, 4, 0);
