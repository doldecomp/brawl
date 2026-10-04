#include <havok/hkClass.h>

extern const hkClass hkCollidableClass;
extern const hkClass hkCdBodyClass;
extern const hkClass hkTypedBroadPhaseHandleClass;

static const hkClassMember hkCollidableClass_Members[] = {
    {"ownerOffset", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"broadPhaseHandle", &hkTypedBroadPhaseHandleClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x14},
    {"allowedPenetrationDepth", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x20},
};

const hkClass hkCollidableClass("hkCollidable", &hkCdBodyClass, 0x24, 0, 0, 0, 0, hkCollidableClass_Members, 3, 0);
