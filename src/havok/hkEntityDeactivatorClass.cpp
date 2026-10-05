#include <havok/hkClass.h>

extern const hkClass hkEntityDeactivatorClass;
extern const hkClass hkReferencedObjectClass;

const hkClass hkEntityDeactivatorClass("hkEntityDeactivator", &hkReferencedObjectClass, 0x8, 0, 0, 0, 0, 0, 0, 0);
