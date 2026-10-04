#include <havok/hkClass.h>

extern const hkClass hkxVertexBufferClass;
extern const hkClass hkxVertexFormatClass;

static const hkClassMember hkxVertexBufferClass_Members[] = {
    {"vertexData", 0, 0, hkClassMember::TYPE_HOMOGENEOUSARRAY, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"format", &hkxVertexFormatClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0xC},
};

const hkClass hkxVertexBufferClass("hkxVertexBuffer", 0, 0x10, 0, 0, 0, 0, hkxVertexBufferClass_Members, 2, 0);
