#include <havok/hkClass.h>

extern const hkClass hkTypedBroadPhaseHandleClass;
extern const hkClass hkBroadPhaseHandleClass;

static const hkClassMember hkTypedBroadPhaseHandleClass_Members[] = {
    {"type", 0, 0, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"ownerOffset", 0, 0, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0x5},
    {"objectQualityType", 0, 0, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0x6},
    {"collisionFilterInfo", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkTypedBroadPhaseHandleClass("hkTypedBroadPhaseHandle", &hkBroadPhaseHandleClass, 0xC, 0, 0, 0, 0, hkTypedBroadPhaseHandleClass_Members, 4, 0);
