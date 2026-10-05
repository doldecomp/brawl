#include <havok/hkClass.h>

extern const hkClass hkGenericConstraintDataClass;
extern const hkClass hkBridgeAtomsClass;
extern const hkClass hkConstraintDataClass;
extern const hkClass hkGenericConstraintDataSchemeClass;

static const hkClassMember hkGenericConstraintDataClass_Members[] = {
    {"atoms", &hkBridgeAtomsClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0xC},
    {"scheme", &hkGenericConstraintDataSchemeClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x18},
};

const hkClass hkGenericConstraintDataClass("hkGenericConstraintData", &hkConstraintDataClass, 0x58, 0, 0, 0, 0, hkGenericConstraintDataClass_Members, 2, 0);
