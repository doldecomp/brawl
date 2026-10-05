#include <havok/hkClass.h>

extern const hkClass hkSkeletonMapperClass;
extern const hkClass hkReferencedObjectClass;
extern const hkClass hkSkeletonMapperDataClass;

static const hkClassEnumItem hkSkeletonMapperConstraintSourceEnumItems[] = {
    {0, "NO_CONSTRAINTS"},
    {1, "REFERENCE_POSE"},
    {2, "CURRENT_POSE"},
};

static const hkClassEnum hkSkeletonMapperClass_Enums[] = {
    {"ConstraintSource", hkSkeletonMapperConstraintSourceEnumItems, 3},
};

static const hkClassMember hkSkeletonMapperClass_Members[] = {
    {"mapping", &hkSkeletonMapperDataClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkSkeletonMapperClass("hkSkeletonMapper", &hkReferencedObjectClass, 0x38, 0, 0, hkSkeletonMapperClass_Enums, 1, hkSkeletonMapperClass_Members, 1, 0);
