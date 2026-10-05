#include <havok/hkClass.h>

extern const hkClass hkxMeshSectionClass;
extern const hkClass hkxIndexBufferClass;
extern const hkClass hkxMaterialClass;
extern const hkClass hkxVertexBufferClass;

static const hkClassMember hkxMeshSectionClass_Members[] = {
    {"vertexBuffer", &hkxVertexBufferClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x0},
    {"indexBuffers", &hkxIndexBufferClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x4},
    {"material", &hkxMaterialClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0xC},
};

const hkClass hkxMeshSectionClass("hkxMeshSection", 0, 0x10, 0, 0, 0, 0, hkxMeshSectionClass_Members, 3, 0);
