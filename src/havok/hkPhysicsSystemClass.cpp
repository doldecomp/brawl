#include <havok/hkClass.h>

extern const hkClass hkPhysicsSystemClass;
extern const hkClass hkActionClass;
extern const hkClass hkConstraintInstanceClass;
extern const hkClass hkPhantomClass;
extern const hkClass hkReferencedObjectClass;
extern const hkClass hkRigidBodyClass;

static const hkClassMember hkPhysicsSystemClass_Members[] = {
    {"rigidBodies", &hkRigidBodyClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x8},
    {"constraints", &hkConstraintInstanceClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x14},
    {"actions", &hkActionClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x20},
    {"phantoms", &hkPhantomClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x2C},
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x38},
    {"userData", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x3C},
    {"active", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x40},
};

static const u32 hkPhysicsSystemClass_Default[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0000001C, 0x01000000};

const hkClass hkPhysicsSystemClass("hkPhysicsSystem", &hkReferencedObjectClass, 0x44, 0, 0, 0, 0, hkPhysicsSystemClass_Members, 7, hkPhysicsSystemClass_Default);
