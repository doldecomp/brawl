#include <havok/hkClass.h>

extern const hkClass hkConvexShapeClass;
extern const hkClass hkSphereRepShapeClass;

static const hkClassMember hkConvexShapeClass_Members[] = {
    {"radius", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xC},
};

const hkClass hkConvexShapeClass("hkConvexShape", &hkSphereRepShapeClass, 0x10, 0, 0, 0, 0, hkConvexShapeClass_Members, 1, 0);
