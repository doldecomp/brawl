#include <havok/hkClass.h>

extern const hkClass hkSphereRepShapeClass;
extern const hkClass hkShapeClass;

const hkClass hkSphereRepShapeClass("hkSphereRepShape", &hkShapeClass, 0xC, 0, 0, 0, 0, 0, 0, 0);
