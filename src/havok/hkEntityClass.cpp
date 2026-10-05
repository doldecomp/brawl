#include <havok/hkClass.h>

extern const hkClass hkEntityClass;
extern const hkClass hkEntityDeactivatorClass;
extern const hkClass hkMaterialClass;
extern const hkClass hkMaxSizeMotionClass;
extern const hkClass hkWorldObjectClass;

static const hkClassMember hkEntityClass_Members[] = {
    {"simulationIsland", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0x58},
    {"material", &hkMaterialClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x5C},
    {"deactivator", &hkEntityDeactivatorClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x68},
    {"constraintsMaster", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x6C},
    {"constraintsSlave", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x78},
    {"constraintRuntime", 0, 0, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0x84},
    {"storageIndex", 0, 0, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0x90},
    {"processContactCallbackDelay", 0, 0, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0x92},
    {"autoRemoveLevel", 0, 0, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0x94},
    {"motion", &hkMaxSizeMotionClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0xA0},
    {"solverData", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x1B0},
    {"collisionListeners", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x1B4},
    {"activationListeners", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x1C0},
    {"entityListeners", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x1CC},
    {"actions", 0, 0, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0x1D8},
    {"uid", 0, 0, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0x1E4},
};

static const u32 hkEntityClass_Default[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000040, 0xFFFFFFFF};

const hkClass hkEntityClass("hkEntity", &hkWorldObjectClass, 0x1F0, 0, 0, 0, 0, hkEntityClass_Members, 16, hkEntityClass_Default);
