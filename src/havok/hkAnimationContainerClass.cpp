#include <havok/hkClass.h>

extern const hkClass hkAnimationContainerClass;
extern const hkClass hkAnimationBindingClass;
extern const hkClass hkBoneAttachmentClass;
extern const hkClass hkMeshBindingClass;
extern const hkClass hkSkeletalAnimationClass;
extern const hkClass hkSkeletonClass;

static const hkClassMember hkAnimationContainerClass_Members[] = {
    {"skeletons", &hkSkeletonClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x0},
    {"animations", &hkSkeletalAnimationClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x8},
    {"bindings", &hkAnimationBindingClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x10},
    {"attachments", &hkBoneAttachmentClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x18},
    {"skins", &hkMeshBindingClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x20},
};

const hkClass hkAnimationContainerClass("hkAnimationContainer", 0, 0x28, 0, 0, 0, 0, hkAnimationContainerClass_Members, 5, 0);
