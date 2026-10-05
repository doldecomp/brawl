#include <havok/hkClass.h>

extern const hkClass hkRigidBodyDeactivatorClass;
extern const hkClass hkEntityDeactivatorClass;

static const hkClassEnumItem hkRigidBodyDeactivatorDeactivatorTypeEnumItems[] = {
    {0, "DEACTIVATOR_INVALID"},
    {1, "DEACTIVATOR_NEVER"},
    {2, "DEACTIVATOR_SPATIAL"},
    {3, "DEACTIVATOR_MAX_ID"},
};

static const hkClassEnum hkRigidBodyDeactivatorClass_Enums[] = {
    {"DeactivatorType", hkRigidBodyDeactivatorDeactivatorTypeEnumItems, 4},
};

const hkClass hkRigidBodyDeactivatorClass("hkRigidBodyDeactivator", &hkEntityDeactivatorClass, 0x8, 0, 0, hkRigidBodyDeactivatorClass_Enums, 1, 0, 0, 0);
