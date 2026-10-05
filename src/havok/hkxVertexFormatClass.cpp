#include <havok/hkClass.h>

extern const hkClass hkxVertexFormatClass;

static const hkClassMember hkxVertexFormatClass_Members[] = {
    {"stride", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"positionOffset", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x1},
    {"normalOffset", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"tangentOffset", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x3},
    {"binormalOffset", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"numBonesPerVertex", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x5},
    {"boneIndexOffset", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x6},
    {"boneWeightOffset", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x7},
    {"numTextureChannels", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"tFloatCoordOffset", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x9},
    {"tQuantizedCoordOffset", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0xA},
    {"colorOffset", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0xB},
};

const hkClass hkxVertexFormatClass("hkxVertexFormat", 0, 0xC, 0, 0, 0, 0, hkxVertexFormatClass_Members, 12, 0);
