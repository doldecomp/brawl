#include <havok/hkClass.h>

extern const hkClass hkxMeshClass;
extern const hkClass hkxMeshSectionClass;

static const hkClassMember hkxMeshClass_Members[] = {
    {"sections", &hkxMeshSectionClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x0},
};

const hkClass hkxMeshClass("hkxMesh", 0, 0x8, 0, 0, 0, 0, hkxMeshClass_Members, 1, 0);
