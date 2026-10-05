#include <havok/hkClass.h>

extern const hkClass hkMeshBindingClass;
extern const hkClass hkMeshBindingMappingClass;
extern const hkClass hkSkeletonClass;
extern const hkClass hkxMeshClass;

static const hkClassMember hkMeshBindingMappingClass_Members[] = {
    {"mapping", 0, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0x0},
};

const hkClass hkMeshBindingMappingClass("hkMeshBindingMapping", 0, 0x8, 0, 0, 0, 0, hkMeshBindingMappingClass_Members, 1, 0);

static const hkClassMember hkMeshBindingClass_Members[] = {
    {"mesh", &hkxMeshClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x0},
    {"skeleton", &hkSkeletonClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x4},
    {"mappings", &hkMeshBindingMappingClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x8},
    {"inverseWorldBindPose", 0, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_TRANSFORM, 0, 0, 0x10},
};

const hkClass hkMeshBindingClass("hkMeshBinding", 0, 0x18, 0, 0, 0, 0, hkMeshBindingClass_Members, 4, 0);
