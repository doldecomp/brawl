#include <havok/hkClass.h>

extern const hkClass hkPhantomClass;
extern const hkClass hkWorldObjectClass;

static const hkClassMember hkPhantomClass_Members[] = {
    {"overlapListeners", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x58},
    {"phantomListeners", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x64},
};

const hkClass hkPhantomClass("hkPhantom", &hkWorldObjectClass, 0x70, 0, 0, 0, 0, hkPhantomClass_Members, 2, 0);
