#include <havok/hkClass.h>

extern const hkClass hkRagdollInstanceClass;
extern const hkClass hkConstraintInstanceClass;
extern const hkClass hkReferencedObjectClass;
extern const hkClass hkRigidBodyClass;
extern const hkClass hkSkeletonClass;

static const hkClassMember hkRagdollInstanceClass_Members[] = {
    {"rigidBodies", &hkRigidBodyClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x8},
    {"constraints", &hkConstraintInstanceClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x14},
    {"skeleton", &hkSkeletonClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x20},
};

const hkClass hkRagdollInstanceClass("hkRagdollInstance", &hkReferencedObjectClass, 0x24, 0, 0, 0, 0, hkRagdollInstanceClass_Members, 3, 0);
