#include <havok/hkClass.h>

extern const hkClass hkSphereShapeClass;
extern const hkClass hkConvexShapeClass;

const hkClass hkSphereShapeClass("hkSphereShape", &hkConvexShapeClass, 0x10, 0, 0, 0, 0, 0, 0, 0);
