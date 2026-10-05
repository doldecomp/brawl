#include <havok/hkClass.h>

extern const hkClass hkCollisionFilterClass;
extern const hkClass hkReferencedObjectClass;

const hkClass hkCollisionFilterClass("hkCollisionFilter", &hkReferencedObjectClass, 0x18, 0, 4, 0, 0, 0, 0, 0);
