#include <havok/hkClass.h>

extern const hkClass hkCylinderShapeClass;
extern const hkClass hkConvexShapeClass;

static const hkClassEnumItem hkCylinderShapeVertexIdEncodingEnumItems[] = {
    {7, "VERTEX_ID_ENCODING_IS_BASE_A_SHIFT"},
    {6, "VERTEX_ID_ENCODING_SIN_SIGN_SHIFT"},
    {5, "VERTEX_ID_ENCODING_COS_SIGN_SHIFT"},
    {4, "VERTEX_ID_ENCODING_IS_SIN_LESSER_SHIFT"},
    {15, "VERTEX_ID_ENCODING_VALUE_MASK"},
};

static const hkClassEnum hkCylinderShapeClass_Enums[] = {
    {"VertexIdEncoding", hkCylinderShapeVertexIdEncodingEnumItems, 5},
};

static const hkClassMember hkCylinderShapeClass_Members[] = {
    {"cylRadius", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"cylBaseRadiusFactorForHeightFieldCollisions", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x14},
    {"vertexA", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x20},
    {"vertexB", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x30},
    {"perpendicular1", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x40},
    {"perpendicular2", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x50},
};

static const u32 hkCylinderShapeClass_Default[] = {0xFFFFFFFF, 0x00000018, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x3F4CCCCD, 0x00000000};

const hkClass hkCylinderShapeClass("hkCylinderShape", &hkConvexShapeClass, 0x60, 0, 0, hkCylinderShapeClass_Enums, 1, hkCylinderShapeClass_Members, 6, hkCylinderShapeClass_Default);
