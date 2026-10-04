#include <havok/hkClass.h>

extern const hkClass hkBaseObjectClass;

static const hkClassMember hkReferencedObjectClass_Members[] = {
    {"memSizeAndFlags", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_UINT16, 0, 0, 4},
    {"referenceCount", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_INT16, 0, 0, 6},
};

extern const hkClass hkReferencedObjectClass;
const hkClass hkReferencedObjectClass("hkReferencedObject", &hkBaseObjectClass, 8, 0, 0, 0, 0,
                                      hkReferencedObjectClass_Members, 2, 0);
