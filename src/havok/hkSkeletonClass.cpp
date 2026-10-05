#include <havok/hkClass.h>

extern const hkClass hkSkeletonClass;
extern const hkClass hkBoneClass;

static const hkClassMember hkSkeletonClass_Members[] = {
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"parentIndices", 0, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0x4},
    {"bones", &hkBoneClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0xC},
    {"referencePose", 0, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0x14},
};

const hkClass hkSkeletonClass("hkSkeleton", 0, 0x1C, 0, 0, 0, 0, hkSkeletonClass_Members, 4, 0);
