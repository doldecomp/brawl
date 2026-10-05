#include <havok/hkClass.h>

extern const hkClass hkBoneClass;

static const hkClassMember hkBoneClass_Members[] = {
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"lockTranslation", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x4},
};

const hkClass hkBoneClass("hkBone", 0, 0x8, 0, 0, 0, 0, hkBoneClass_Members, 2, 0);
