#include <havok/hkClass.h>

extern const hkClass hkGenericConstraintDataSchemeClass;
extern const hkClass hkConstraintInfoClass;
extern const hkClass hkConstraintMotorClass;

static const hkClassMember hkGenericConstraintDataSchemeClass_Members[] = {
    {"info", &hkConstraintInfoClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"data", 0, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0x10},
    {"commands", 0, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0x1C},
    {"modifiers", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x28},
    {"motors", &hkConstraintMotorClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x34},
};

const hkClass hkGenericConstraintDataSchemeClass("hkGenericConstraintDataScheme", 0, 0x40, 0, 0, 0, 0, hkGenericConstraintDataSchemeClass_Members, 5, 0);
