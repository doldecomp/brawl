#include <havok/hkClass.h>

extern const hkClass hkShapeContainerClass;
extern const hkClass hkSingleShapeContainerClass;
extern const hkClass hkShapeClass;

const hkClass hkShapeContainerClass("hkShapeContainer", 0, 0x4, 0, 1, 0, 0, 0, 0, 0);

static const hkClassMember hkSingleShapeContainerClass_Members[] = {
    {"childShape", &hkShapeClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x4},
};

const hkClass hkSingleShapeContainerClass("hkSingleShapeContainer", &hkShapeContainerClass, 0x8, 0, 0, 0, 0, hkSingleShapeContainerClass_Members, 1, 0);
