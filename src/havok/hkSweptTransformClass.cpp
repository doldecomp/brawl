#include <havok/hkClass.h>

extern const hkClass hkSweptTransformClass;

static const hkClassMember hkSweptTransformClass_Members[] = {
    {"centerOfMass0", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"centerOfMass1", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"rotation0", 0, 0, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0x20},
    {"rotation1", 0, 0, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0x30},
    {"centerOfMassLocal", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x40},
};

const hkClass hkSweptTransformClass("hkSweptTransform", 0, 0x50, 0, 0, 0, 0, hkSweptTransformClass_Members, 5, 0);
