#include <havok/hkClass.h>

extern const hkClass hkAnimationBindingClass;
extern const hkClass hkSkeletalAnimationClass;

static const hkClassEnumItem hkAnimationBindingBlendHintEnumItems[] = {
    {0, "NORMAL"},
    {1, "ADDITIVE"},
};

static const hkClassEnum hkAnimationBindingClass_Enums[] = {
    {"BlendHint", hkAnimationBindingBlendHintEnumItems, 2},
};

static const hkClassEnum* hkAnimationBindingClass_Enum0 = &hkAnimationBindingClass_Enums[0];

static const hkClassMember hkAnimationBindingClass_Members[] = {
    {"animation", &hkSkeletalAnimationClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x0},
    {"animationTrackToBoneIndices", 0, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0x4},
    {"blendHint", 0, hkAnimationBindingClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0xC},
};

static const u32 hkAnimationBindingClass_Default[] = {0xFFFFFFFF, 0xFFFFFFFF, 0x0000000C, 0x00000000};

const hkClass hkAnimationBindingClass("hkAnimationBinding", 0, 0x10, 0, 0, hkAnimationBindingClass_Enums, 1, hkAnimationBindingClass_Members, 3, hkAnimationBindingClass_Default);
