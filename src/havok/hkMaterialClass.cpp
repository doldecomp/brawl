#include <havok/hkClass.h>

extern const hkClass hkMaterialClass;

static const hkClassEnumItem hkMaterialResponseTypeEnumItems[] = {
    {0, "RESPONSE_INVALID"},
    {1, "RESPONSE_SIMPLE_CONTACT"},
    {2, "RESPONSE_REPORTING"},
    {3, "RESPONSE_NONE"},
    {4, "RESPONSE_MAX_ID"},
};

static const hkClassEnum hkMaterialClass_Enums[] = {
    {"ResponseType", hkMaterialResponseTypeEnumItems, 5},
};

static const hkClassEnum* hkMaterialClass_Enum0 = &hkMaterialClass_Enums[0];

static const hkClassMember hkMaterialClass_Members[] = {
    {"responseType", 0, hkMaterialClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x0},
    {"friction", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"restitution", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkMaterialClass("hkMaterial", 0, 0xC, 0, 0, hkMaterialClass_Enums, 1, hkMaterialClass_Members, 3, 0);
