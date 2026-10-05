#include <havok/hkClass.h>

extern const hkClass hkMeshShapeClass;
extern const hkClass hkMeshShapeSubpartClass;
extern const hkClass hkShapeCollectionClass;

static const hkClassEnumItem hkMeshShapeIndexStridingTypeEnumItems[] = {
    {0, "INDICES_INVALID"},
    {1, "INDICES_INT16"},
    {2, "INDICES_INT32"},
    {3, "INDICES_MAX_ID"},
};

static const hkClassEnumItem hkMeshShapeMaterialIndexStridingTypeEnumItems[] = {
    {0, "MATERIAL_INDICES_INVALID"},
    {1, "MATERIAL_INDICES_INT8"},
    {2, "MATERIAL_INDICES_INT16"},
    {3, "MATERIAL_INDICES_MAX_ID"},
};

static const hkClassEnum hkMeshShapeClass_Enums[] = {
    {"IndexStridingType", hkMeshShapeIndexStridingTypeEnumItems, 4},
    {"MaterialIndexStridingType", hkMeshShapeMaterialIndexStridingTypeEnumItems, 4},
};

static const hkClassEnum* hkMeshShapeSubpartClass_Enum0 = &hkMeshShapeClass_Enums[0];

static const hkClassMember hkMeshShapeSubpartClass_Members[] = {
    {"vertexBase", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x0},
    {"vertexStriding", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"numVertices", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"indexBase", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0xC},
    {"stridingType", 0, hkMeshShapeSubpartClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x10},
    {"materialIndexStridingType", 0, hkMeshShapeSubpartClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x11},
    {"indexStriding", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x14},
    {"numTriangles", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x18},
    {"materialIndexBase", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x1C},
    {"materialIndexStriding", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x20},
    {"materialBase", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x24},
    {"materialStriding", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x28},
    {"numMaterials", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x2C},
};

static const hkClassMember hkMeshShapeClass_Members[] = {
    {"scaling", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x20},
    {"numBitsForSubpartIndex", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x30},
    {"subparts", &hkMeshShapeSubpartClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x34},
    {"radius", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x40},
    {"pad", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 3, 0, 0x44},
};

const hkClass hkMeshShapeSubpartClass("hkMeshShapeSubpart", 0, 0x30, 0, 0, 0, 0, hkMeshShapeSubpartClass_Members, 13, 0);

const hkClass hkMeshShapeClass("hkMeshShape", &hkShapeCollectionClass, 0x50, 0, 0, hkMeshShapeClass_Enums, 2, hkMeshShapeClass_Members, 5, 0);
