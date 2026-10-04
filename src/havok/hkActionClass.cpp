#include <havok/hkClass.h>

extern const hkClass hkActionClass;
extern const hkClass hkReferencedObjectClass;

static const hkClassMember hkActionClass_Members[] = {
    {"world", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x8},
    {"island", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0xC},
    {"userData", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x14},
};

const hkClass hkActionClass("hkAction", &hkReferencedObjectClass, 0x18, 0, 0, 0, 0, hkActionClass_Members, 4, 0);
