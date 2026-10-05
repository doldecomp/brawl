#include <havok/hkClass.h>

extern const hkClass hkClassMemberClass;
extern const hkClass hkClassClass;
extern const hkClass hkClassEnumClass;

static const hkClassEnumItem hkClassMemberTypeEnumItems[] = {
    {0, "TYPE_VOID"},
    {1, "TYPE_BOOL"},
    {2, "TYPE_CHAR"},
    {3, "TYPE_INT8"},
    {4, "TYPE_UINT8"},
    {5, "TYPE_INT16"},
    {6, "TYPE_UINT16"},
    {7, "TYPE_INT32"},
    {8, "TYPE_UINT32"},
    {9, "TYPE_INT64"},
    {10, "TYPE_UINT64"},
    {11, "TYPE_REAL"},
    {12, "TYPE_VECTOR4"},
    {13, "TYPE_QUATERNION"},
    {14, "TYPE_MATRIX3"},
    {15, "TYPE_ROTATION"},
    {16, "TYPE_QSTRANSFORM"},
    {17, "TYPE_MATRIX4"},
    {18, "TYPE_TRANSFORM"},
    {19, "TYPE_ZERO"},
    {20, "TYPE_POINTER"},
    {21, "TYPE_FUNCTIONPOINTER"},
    {22, "TYPE_ARRAY"},
    {23, "TYPE_INPLACEARRAY"},
    {24, "TYPE_ENUM"},
    {25, "TYPE_STRUCT"},
    {26, "TYPE_SIMPLEARRAY"},
    {27, "TYPE_HOMOGENEOUSARRAY"},
    {28, "TYPE_VARIANT"},
    {29, "TYPE_CSTRING"},
    {30, "TYPE_MAX"},
};

static const hkClassEnumItem hkClassMemberFlagsEnumItems[] = {
    {1, "POINTER_OPTIONAL"},
    {2, "POINTER_VOIDSTAR"},
    {8, "ENUM_8"},
    {16, "ENUM_16"},
    {32, "ENUM_32"},
    {64, "ARRAY_RAWDATA"},
};

static const hkClassEnumItem hkClassMemberRangeEnumItems[] = {
    {0, "INVALID"},
    {1, "DEFAULT"},
    {2, "ABS_MIN"},
    {4, "ABS_MAX"},
    {8, "SOFT_MIN"},
    {16, "SOFT_MAX"},
    {32, "RANGE_MAX"},
};

static const hkClassEnum hkClassMemberClass_Enums[] = {
    {"Type", hkClassMemberTypeEnumItems, 31},
    {"Flags", hkClassMemberFlagsEnumItems, 6},
    {"Range", hkClassMemberRangeEnumItems, 7},
};

static const hkClassEnum* hkClassMemberClass_Enum0 = &hkClassMemberClass_Enums[0];

static const hkClassMember hkClassMemberClass_Members[] = {
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"class", &hkClassClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x4},
    {"enum", &hkClassEnumClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x8},
    {"type", 0, hkClassMemberClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0xC},
    {"subtype", 0, hkClassMemberClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0xD},
    {"cArraySize", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0xE},
    {"flags", 0, 0, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"offset", 0, 0, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0x12},
};

const hkClass hkClassMemberClass("hkClassMember", 0, 0x14, 0, 0, hkClassMemberClass_Enums, 3, hkClassMemberClass_Members, 8, 0);
