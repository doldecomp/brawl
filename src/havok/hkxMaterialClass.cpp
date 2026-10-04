#include <havok/hkClass.h>

extern const hkClass hkxMaterialClass;
extern const hkClass hkxMaterialTextureStageClass;

static const hkClassMember hkxMaterialTextureStageClass_Members[] = {
    {"texture", 0, 0, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"usageHint", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkxMaterialTextureStageClass("hkxMaterialTextureStage", 0, 0xC, 0, 0, 0, 0, hkxMaterialTextureStageClass_Members, 2, 0);

static const hkClassEnumItem hkxMaterialTextureTypeEnumItems[] = {
    {0, "TEX_UNKNOWN"},
    {1, "TEX_DIFFUSE"},
    {2, "TEX_REFLECTION"},
    {3, "TEX_BUMP"},
    {4, "TEX_NORMAL"},
    {5, "TEX_DISPLACEMENT"},
};

static const hkClassEnum hkxMaterialClass_Enums[] = {
    {"TextureType", hkxMaterialTextureTypeEnumItems, 6},
};

static const hkClassMember hkxMaterialClass_Members[] = {
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"stages", &hkxMaterialTextureStageClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x4},
    {"diffuseColor", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"ambientColor", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x20},
    {"specularColor", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x30},
    {"emissiveColor", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x40},
    {"subMaterials", &hkxMaterialClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x50},
    {"extraData", 0, 0, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0x58},
};

const hkClass hkxMaterialClass("hkxMaterial", 0, 0x60, 0, 0, hkxMaterialClass_Enums, 1, hkxMaterialClass_Members, 8, 0);
