#include <havok/hkClass.h>

extern const hkClass hkSkeletonMapperDataChainMappingClass;
extern const hkClass hkSkeletonMapperDataClass;
extern const hkClass hkSkeletonMapperDataSimpleMappingClass;
extern const hkClass hkSkeletonClass;

static const hkClassMember hkSkeletonMapperDataSimpleMappingClass_Members[] = {
    {"boneA", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"boneB", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"aFromBTransform", 0, 0, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

static const hkClassMember hkSkeletonMapperDataChainMappingClass_Members[] = {
    {"startBoneA", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"endBoneA", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"startBoneB", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"endBoneB", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x6},
    {"startAFromBTransform", 0, 0, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"endAFromBTransform", 0, 0, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0x40},
};

static const hkClassMember hkSkeletonMapperDataClass_Members[] = {
    {"skeletonA", &hkSkeletonClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x0},
    {"skeletonB", &hkSkeletonClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x4},
    {"simpleMappings", &hkSkeletonMapperDataSimpleMappingClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x8},
    {"chainMappings", &hkSkeletonMapperDataChainMappingClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x14},
    {"unmappedBones", 0, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0x20},
    {"keepUnmappedLocal", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x2C},
};

const hkClass hkSkeletonMapperDataSimpleMappingClass("hkSkeletonMapperDataSimpleMapping", 0, 0x40, 0, 0, 0, 0, hkSkeletonMapperDataSimpleMappingClass_Members, 3, 0);

const hkClass hkSkeletonMapperDataChainMappingClass("hkSkeletonMapperDataChainMapping", 0, 0x70, 0, 0, 0, 0, hkSkeletonMapperDataChainMappingClass_Members, 6, 0);

const hkClass hkSkeletonMapperDataClass("hkSkeletonMapperData", 0, 0x30, 0, 0, 0, 0, hkSkeletonMapperDataClass_Members, 6, 0);
