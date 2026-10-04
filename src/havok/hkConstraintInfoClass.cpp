#include <havok/hkClass.h>

extern const hkClass hkConstraintInfoClass;

static const hkClassMember hkConstraintInfoClass_Members[] = {
    {"maxSizeOfJacobians", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"sizeOfJacobians", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"sizeOfSchemas", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"numSolverResults", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0xC},
};

const hkClass hkConstraintInfoClass("hkConstraintInfo", 0, 0x10, 0, 0, 0, 0, hkConstraintInfoClass_Members, 4, 0);
