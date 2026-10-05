#include <havok/hkClass.h>

extern const hkClass hkxIndexBufferClass;

static const hkClassEnumItem hkxIndexBufferIndexTypeEnumItems[] = {
    {0, "INDEX_TYPE_INVALID"},
    {1, "INDEX_TYPE_TRI_LIST"},
    {2, "INDEX_TYPE_TRI_STRIP"},
    {3, "INDEX_TYPE_TRI_FAN"},
    {4, "INDEX_TYPE_MAX_ID"},
};

static const hkClassEnum hkxIndexBufferClass_Enums[] = {
    {"IndexType", hkxIndexBufferIndexTypeEnumItems, 5},
};

static const hkClassEnum* hkxIndexBufferClass_Enum0 = &hkxIndexBufferClass_Enums[0];

static const hkClassMember hkxIndexBufferClass_Members[] = {
    {"indexType", 0, hkxIndexBufferClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x0},
    {"indices16", 0, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0x4},
    {"indices32", 0, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0xC},
    {"vertexBaseOffset", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x14},
    {"length", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x18},
};

const hkClass hkxIndexBufferClass("hkxIndexBuffer", 0, 0x1C, 0, 0, hkxIndexBufferClass_Enums, 1, hkxIndexBufferClass_Members, 5, 0);
