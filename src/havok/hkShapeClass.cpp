#include <havok/hkClass.h>

extern const hkClass hkShapeClass;
extern const hkClass hkReferencedObjectClass;

static const hkClassMember hkShapeClass_Members[] = {
    {"userData", 0, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkShapeClass("hkShape", &hkReferencedObjectClass, 0xC, 0, 0, 0, 0, hkShapeClass_Members, 1, 0);
