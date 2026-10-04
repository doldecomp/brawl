#include <havok/hkClass.h>

extern const hkClass hkBoneAttachmentClass;

static const hkClassMember hkBoneAttachmentClass_Members[] = {
    {"boneFromAttachment", 0, 0, hkClassMember::TYPE_MATRIX4, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"attachment", 0, 0, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0x40},
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x48},
    {"boneIndex", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x4C},
};

const hkClass hkBoneAttachmentClass("hkBoneAttachment", 0, 0x50, 0, 0, 0, 0, hkBoneAttachmentClass_Members, 4, 0);
