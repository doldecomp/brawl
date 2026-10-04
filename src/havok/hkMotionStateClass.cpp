#include <havok/hkClass.h>

extern const hkClass hkMotionStateClass;
extern const hkClass hkSweptTransformClass;

static const hkClassMember hkMotionStateClass_Members[] = {
    {"transform", 0, 0, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"sweptTransform", &hkSweptTransformClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x40},
    {"deltaAngle", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x90},
    {"objectRadius", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xA0},
    {"maxLinearVelocity", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xA4},
    {"maxAngularVelocity", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xA8},
    {"linearDamping", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xAC},
    {"angularDamping", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xB0},
    {"deactivationClass", 0, 0, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0xB4},
    {"deactivationCounter", 0, 0, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0xB6},
};

const hkClass hkMotionStateClass("hkMotionState", 0, 0xC0, 0, 0, 0, 0, hkMotionStateClass_Members, 10, 0);
