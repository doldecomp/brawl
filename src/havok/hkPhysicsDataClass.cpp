#include <havok/hkClass.h>

extern const hkClass hkPhysicsDataClass;
extern const hkClass hkPhysicsSystemClass;
extern const hkClass hkReferencedObjectClass;
extern const hkClass hkWorldCinfoClass;

static const hkClassMember hkPhysicsDataClass_Members[] = {
    {"worldCinfo", &hkWorldCinfoClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x8},
    {"systems", &hkPhysicsSystemClass, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0xC},
};

const hkClass hkPhysicsDataClass("hkPhysicsData", &hkReferencedObjectClass, 0x18, 0, 0, 0, 0, hkPhysicsDataClass_Members, 2, 0);
