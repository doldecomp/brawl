#include <havok/hkClass.h>

extern const hkClass hkShapeCollectionClass;
extern const hkClass hkShapeClass;

static const hkClassMember hkShapeCollectionClass_Members[] = {
    {"disableWelding", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

const hkClass hkShapeCollectionClass("hkShapeCollection", &hkShapeClass, 0x14, 0, 1, 0, 0, hkShapeCollectionClass_Members, 1, 0);
