#include <havok/hkClass.h>

extern const hkClass hkBoxShapeClass;
extern const hkClass hkConvexShapeClass;

static const hkClassMember hkBoxShapeClass_Members[] = {
    {"halfExtents", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

const hkClass hkBoxShapeClass("hkBoxShape", &hkConvexShapeClass, 0x20, 0, 0, 0, 0, hkBoxShapeClass_Members, 1, 0);
