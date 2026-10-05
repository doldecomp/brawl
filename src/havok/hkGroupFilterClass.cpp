#include <havok/hkClass.h>

extern const hkClass hkGroupFilterClass;
extern const hkClass hkCollisionFilterClass;

static const hkClassMember hkGroupFilterClass_Members[] = {
    {"nextFreeSystemGroup", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x18},
    {"collisionLookupTable", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 32, 0, 0x1C},
};

const hkClass hkGroupFilterClass("hkGroupFilter", &hkCollisionFilterClass, 0x9C, 0, 0, 0, 0, hkGroupFilterClass_Members, 2, 0);
