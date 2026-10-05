#include <havok/hkClass.h>

extern const hkClass hkCapsuleShapeClass;
extern const hkClass hkConvexShapeClass;

static const hkClassEnumItem hkCapsuleShapeRayHitTypeEnumItems[] = {
    {0, "HIT_CAP0"},
    {1, "HIT_CAP1"},
    {2, "HIT_BODY"},
};

static const hkClassEnum hkCapsuleShapeClass_Enums[] = {
    {"RayHitType", hkCapsuleShapeRayHitTypeEnumItems, 3},
};

static const hkClassMember hkCapsuleShapeClass_Members[] = {
    {"vertexA", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"vertexB", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x20},
};

const hkClass hkCapsuleShapeClass("hkCapsuleShape", &hkConvexShapeClass, 0x30, 0, 0, hkCapsuleShapeClass_Enums, 1, hkCapsuleShapeClass_Members, 2, 0);
