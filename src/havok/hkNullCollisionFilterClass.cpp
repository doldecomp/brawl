#include <havok/hkClass.h>

extern const hkClass hkNullCollisionFilterClass;
extern const hkClass hkCollisionFilterClass;

const hkClass hkNullCollisionFilterClass("hkNullCollisionFilter", &hkCollisionFilterClass, 0x18, 0, 0, 0, 0, 0, 0, 0);
