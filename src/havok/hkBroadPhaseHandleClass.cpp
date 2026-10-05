#include <havok/hkClass.h>

extern const hkClass hkBroadPhaseHandleClass;

static const hkClassMember hkBroadPhaseHandleClass_Members[] = {
    {"id", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x0},
};

const hkClass hkBroadPhaseHandleClass("hkBroadPhaseHandle", 0, 0x4, 0, 0, 0, 0, hkBroadPhaseHandleClass_Members, 1, 0);
