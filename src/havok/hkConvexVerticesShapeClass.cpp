#include <havok/hkClass.h>

extern const hkClass hkConvexVerticesShapeClass;
extern const hkClass hkConvexVerticesShapeFourVectorsClass;
extern const hkClass hkConvexShapeClass;

static const hkClassMember hkConvexVerticesShapeFourVectorsClass_Members[] = {
    {"x", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"y", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"z", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x20},
};

const hkClass hkConvexVerticesShapeFourVectorsClass("hkConvexVerticesShapeFourVectors", 0, 0x30, 0, 0, 0, 0, hkConvexVerticesShapeFourVectorsClass_Members, 3, 0);

static const hkClassMember hkConvexVerticesShapeClass_Members[] = {
    {"aabbHalfExtents", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"aabbCenter", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x20},
    {"rotatedVertices", &hkConvexVerticesShapeFourVectorsClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x30},
    {"numVertices", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x3C},
    {"planeEquations", 0, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0x40},
};

const hkClass hkConvexVerticesShapeClass("hkConvexVerticesShape", &hkConvexShapeClass, 0x50, 0, 0, 0, 0, hkConvexVerticesShapeClass_Members, 5, 0);
