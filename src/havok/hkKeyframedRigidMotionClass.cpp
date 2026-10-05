#include <havok/hkClass.h>

extern const hkClass hkKeyframedRigidMotionClass;
extern const hkClass hkMaxSizeMotionClass;
extern const hkClass hkMotionClass;

static const hkClassMember hkKeyframedRigidMotionClass_Members[] = {
    {"savedMotion", &hkMaxSizeMotionClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x100},
    {"savedQualityTypeIndex", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x104},
};

const hkClass hkKeyframedRigidMotionClass("hkKeyframedRigidMotion", &hkMotionClass, 0x110, 0, 0, 0, 0, hkKeyframedRigidMotionClass_Members, 2, 0);

const hkClass hkMaxSizeMotionClass("hkMaxSizeMotion", &hkKeyframedRigidMotionClass, 0x110, 0, 0, 0, 0, 0, 0, 0);
