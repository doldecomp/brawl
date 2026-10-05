#include <havok/hkClass.h>

extern const hkClass hkMotionClass;
extern const hkClass hkMotionStateClass;
extern const hkClass hkReferencedObjectClass;

static const hkClassEnumItem hkMotionMotionTypeEnumItems[] = {
    {0, "MOTION_INVALID"},
    {1, "MOTION_DYNAMIC"},
    {2, "MOTION_SPHERE_INERTIA"},
    {3, "MOTION_STABILIZED_SPHERE_INERTIA"},
    {4, "MOTION_BOX_INERTIA"},
    {5, "MOTION_STABILIZED_BOX_INERTIA"},
    {6, "MOTION_KEYFRAMED"},
    {7, "MOTION_FIXED"},
    {8, "MOTION_THIN_BOX_INERTIA"},
    {9, "MOTION_MAX_ID"},
};

static const hkClassEnum hkMotionClass_Enums[] = {
    {"MotionType", hkMotionMotionTypeEnumItems, 10},
};

static const hkClassEnum* hkMotionClass_Enum0 = &hkMotionClass_Enums[0];

static const hkClassMember hkMotionClass_Members[] = {
    {"type", 0, hkMotionClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x8},
    {"motionState", &hkMotionStateClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"inertiaAndMassInv", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0xD0},
    {"linearVelocity", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0xE0},
    {"angularVelocity", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0xF0},
};

const hkClass hkMotionClass("hkMotion", &hkReferencedObjectClass, 0x100, 0, 0, hkMotionClass_Enums, 1, hkMotionClass_Members, 5, 0);
