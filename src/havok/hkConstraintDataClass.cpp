#include <havok/hkClass.h>

extern const hkClass hkConstraintDataClass;
extern const hkClass hkReferencedObjectClass;

static const hkClassEnumItem hkConstraintDataConstraintTypeEnumItems[] = {
    {0, "CONSTRAINT_TYPE_BALLANDSOCKET"},
    {1, "CONSTRAINT_TYPE_HINGE"},
    {2, "CONSTRAINT_TYPE_LIMITEDHINGE"},
    {3, "CONSTRAINT_TYPE_POINTTOPATH"},
    {6, "CONSTRAINT_TYPE_PRISMATIC"},
    {7, "CONSTRAINT_TYPE_RAGDOLL"},
    {8, "CONSTRAINT_TYPE_STIFFSPRING"},
    {9, "CONSTRAINT_TYPE_WHEEL"},
    {10, "CONSTRAINT_TYPE_GENERIC"},
    {11, "CONSTRAINT_TYPE_CONTACT"},
    {12, "CONSTRAINT_TYPE_BREAKABLE"},
    {13, "CONSTRAINT_TYPE_MALLEABLE"},
    {14, "CONSTRAINT_TYPE_POINTTOPLANE"},
    {15, "CONSTRAINT_TYPE_PULLEY"},
    {18, "CONSTRAINT_TYPE_HINGE_LIMITS"},
    {19, "CONSTRAINT_TYPE_RAGDOLL_LIMITS"},
    {100, "BEGIN_CONSTRAINT_CHAIN_TYPES"},
    {100, "CONSTRAINT_TYPE_STIFF_SPRING_CHAIN"},
    {101, "CONSTRAINT_TYPE_BALL_SOCKET_CHAIN"},
    {102, "CONSTRAINT_TYPE_POWERED_CHAIN"},
};

static const hkClassEnum hkConstraintDataClass_Enums[] = {
    {"ConstraintType", hkConstraintDataConstraintTypeEnumItems, 20},
};

static const hkClassMember hkConstraintDataClass_Members[] = {
    {"userData", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkConstraintDataClass("hkConstraintData", &hkReferencedObjectClass, 0xC, 0, 0, hkConstraintDataClass_Enums, 1, hkConstraintDataClass_Members, 1, 0);
