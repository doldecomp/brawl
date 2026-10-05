#include <havok/hkClass.h>

extern const hkClass hkConvexTranslateShapeClass;
extern const hkClass hkConvexShapeClass;
extern const hkClass hkSingleShapeContainerClass;

static const hkClassMember hkConvexTranslateShapeClass_Members[] = {
    {"childShape", &hkSingleShapeContainerClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"translation", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x20},
};

const hkClass hkConvexTranslateShapeClass("hkConvexTranslateShape", &hkConvexShapeClass, 0x30, 0, 0, 0, 0, hkConvexTranslateShapeClass_Members, 2, 0);
