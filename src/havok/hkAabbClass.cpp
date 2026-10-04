#include <havok/hkClass.h>

extern const hkClass hkAabbClass;

static const hkClassMember hkAabbClass_Members[] = {
    {"min", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"max", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

const hkClass hkAabbClass("hkAabb", 0, 0x20, 0, 0, 0, 0, hkAabbClass_Members, 2, 0);
