#include <havok/hkClass.h>

extern const hkClass hkConstraintMotorClass;
extern const hkClass hkReferencedObjectClass;

static const hkClassEnumItem hkConstraintMotorMotorTypeEnumItems[] = {
    {0, "TYPE_INVALID"},
    {1, "TYPE_POSITION"},
    {2, "TYPE_VELOCITY"},
    {3, "TYPE_SPRING_DAMPER"},
    {4, "TYPE_MAX"},
};

static const hkClassEnum hkConstraintMotorClass_Enums[] = {
    {"MotorType", hkConstraintMotorMotorTypeEnumItems, 5},
};

static const hkClassEnum* hkConstraintMotorClass_Enum0 = &hkConstraintMotorClass_Enums[0];

static const hkClassMember hkConstraintMotorClass_Members[] = {
    {"type", 0, hkConstraintMotorClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x8},
};

const hkClass hkConstraintMotorClass("hkConstraintMotor", &hkReferencedObjectClass, 0xC, 0, 0, hkConstraintMotorClass_Enums, 1, hkConstraintMotorClass_Members, 1, 0);
