#include <havok/hkClass.h>

extern const hkClass hkRigidBodyClass;
extern const hkClass hkEntityClass;

const hkClass hkRigidBodyClass("hkRigidBody", &hkEntityClass, 0x1F0, 0, 0, 0, 0, 0, 0, 0);
