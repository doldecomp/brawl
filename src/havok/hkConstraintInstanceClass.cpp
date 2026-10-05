#include <havok/hkClass.h>

extern const hkClass hkConstraintInstanceClass;
extern const hkClass hkConstraintDataClass;
extern const hkClass hkEntityClass;
extern const hkClass hkModifierConstraintAtomClass;
extern const hkClass hkReferencedObjectClass;

static const hkClassEnumItem hkConstraintInstanceConstraintPriorityEnumItems[] = {
    {0, "PRIORITY_INVALID"},
    {1, "PRIORITY_PSI"},
    {2, "PRIORITY_TOI"},
    {3, "PRIORITY_TOI_HIGHER"},
    {4, "PRIORITY_TOI_FORCED"},
};

static const hkClassEnumItem hkConstraintInstanceInstanceTypeEnumItems[] = {
    {0, "TYPE_NORMAL"},
    {1, "TYPE_CHAIN"},
};

static const hkClassEnumItem hkConstraintInstanceAddReferencesEnumItems[] = {
    {0, "DO_NOT_ADD_REFERENCES"},
    {1, "DO_ADD_REFERENCES"},
};

static const hkClassEnum hkConstraintInstanceClass_Enums[] = {
    {"ConstraintPriority", hkConstraintInstanceConstraintPriorityEnumItems, 5},
    {"InstanceType", hkConstraintInstanceInstanceTypeEnumItems, 2},
    {"AddReferences", hkConstraintInstanceAddReferencesEnumItems, 2},
};

static const hkClassEnum* hkConstraintInstanceClass_Enum0 = &hkConstraintInstanceClass_Enums[0];

static const hkClassMember hkConstraintInstanceClass_Members[] = {
    {"owner", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x8},
    {"data", &hkConstraintDataClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0xC},
    {"constraintModifiers", &hkModifierConstraintAtomClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x10},
    {"entities", &hkEntityClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 2, 0, 0x14},
    {"priority", 0, hkConstraintInstanceClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x1C},
    {"wantRuntime", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x1D},
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x20},
    {"userData", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x24},
    {"internal", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x28},
};

const hkClass hkConstraintInstanceClass("hkConstraintInstance", &hkReferencedObjectClass, 0x2C, 0, 0, hkConstraintInstanceClass_Enums, 3, hkConstraintInstanceClass_Members, 9, 0);
