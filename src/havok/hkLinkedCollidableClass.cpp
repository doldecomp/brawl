#include <havok/hkClass.h>

extern const hkClass hkLinkedCollidableClass;
extern const hkClass hkCollidableClass;

static const hkClassMember hkLinkedCollidableClass_Members[] = {
    {"collisionEntries", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x24},
};

const hkClass hkLinkedCollidableClass("hkLinkedCollidable", &hkCollidableClass, 0x30, 0, 0, 0, 0, hkLinkedCollidableClass_Members, 1, 0);
