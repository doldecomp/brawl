#include <havok/hkClass.h>

extern const hkClass hkWorldCinfoClass;
extern const hkClass hkAabbClass;
extern const hkClass hkCollisionFilterClass;
extern const hkClass hkReferencedObjectClass;
extern const hkClass hkWorldMemoryWatchDogClass;

static const hkClassEnumItem hkWorldCinfoSolverTypeEnumItems[] = {
    {0, "SOLVER_TYPE_INVALID"},
    {1, "SOLVER_TYPE_2ITERS_SOFT"},
    {2, "SOLVER_TYPE_2ITERS_MEDIUM"},
    {3, "SOLVER_TYPE_2ITERS_HARD"},
    {4, "SOLVER_TYPE_4ITERS_SOFT"},
    {5, "SOLVER_TYPE_4ITERS_MEDIUM"},
    {6, "SOLVER_TYPE_4ITERS_HARD"},
    {7, "SOLVER_TYPE_8ITERS_SOFT"},
    {8, "SOLVER_TYPE_8ITERS_MEDIUM"},
    {9, "SOLVER_TYPE_8ITERS_HARD"},
    {10, "SOLVER_TYPE_MAX_ID"},
};

static const hkClassEnumItem hkWorldCinfoSimulationTypeEnumItems[] = {
    {0, "SIMULATION_TYPE_INVALID"},
    {1, "SIMULATION_TYPE_DISCRETE"},
    {2, "SIMULATION_TYPE_CONTINUOUS"},
    {3, "SIMULATION_TYPE_MULTITHREADED"},
};

static const hkClassEnumItem hkWorldCinfoContactPointGenerationEnumItems[] = {
    {0, "CONTACT_POINT_ACCEPT_ALWAYS"},
    {1, "CONTACT_POINT_REJECT_DUBIOUS"},
    {2, "CONTACT_POINT_REJECT_MANY"},
};

static const hkClassEnumItem hkWorldCinfoBroadPhaseBorderBehaviourEnumItems[] = {
    {0, "BROADPHASE_BORDER_ASSERT"},
    {1, "BROADPHASE_BORDER_FIX_ENTITY"},
    {2, "BROADPHASE_BORDER_REMOVE_ENTITY"},
    {3, "BROADPHASE_BORDER_DO_NOTHING"},
};

static const hkClassEnum hkWorldCinfoClass_Enums[] = {
    {"SolverType", hkWorldCinfoSolverTypeEnumItems, 11},
    {"SimulationType", hkWorldCinfoSimulationTypeEnumItems, 4},
    {"ContactPointGeneration", hkWorldCinfoContactPointGenerationEnumItems, 3},
    {"BroadPhaseBorderBehaviour", hkWorldCinfoBroadPhaseBorderBehaviourEnumItems, 4},
};

static const hkClassEnum* hkWorldCinfoClass_Enum2 = &hkWorldCinfoClass_Enums[1];

static const hkClassEnum* hkWorldCinfoClass_Enum1 = &hkWorldCinfoClass_Enums[2];

static const hkClassEnum* hkWorldCinfoClass_Enum0 = &hkWorldCinfoClass_Enums[3];

static const hkClassMember hkWorldCinfoClass_Members[] = {
    {"gravity", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"broadPhaseQuerySize", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x20},
    {"contactRestingVelocity", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x24},
    {"broadPhaseBorderBehaviour", 0, hkWorldCinfoClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x28},
    {"broadPhaseWorldAabb", &hkAabbClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x30},
    {"collisionTolerance", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x50},
    {"collisionFilter", &hkCollisionFilterClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x54},
    {"expectedMaxLinearVelocity", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x58},
    {"expectedMinPsiDeltaTime", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x5C},
    {"memoryWatchDog", &hkWorldMemoryWatchDogClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x60},
    {"broadPhaseNumMarkers", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x64},
    {"contactPointGeneration", 0, hkWorldCinfoClass_Enum1, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x68},
    {"solverTau", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x6C},
    {"solverDamp", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x70},
    {"solverIterations", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x74},
    {"solverMicrosteps", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x78},
    {"iterativeLinearCastEarlyOutDistance", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x7C},
    {"iterativeLinearCastMaxIterations", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x80},
    {"highFrequencyDeactivationPeriod", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x84},
    {"lowFrequencyDeactivationPeriod", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x88},
    {"shouldActivateOnRigidBodyTransformChange", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x8C},
    {"toiCollisionResponseRotateNormal", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x90},
    {"enableDeactivation", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x94},
    {"simulationType", 0, hkWorldCinfoClass_Enum2, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x95},
    {"enableSimulationIslands", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x96},
    {"processActionsInSingleThread", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x97},
    {"frameMarkerPsiSnap", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x98},
};

static const u32 hkWorldCinfoClass_Default[] = {0x0000006C, 0x0000007C, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000080, 0xFFFFFFFF, 0x00000084, 0x00000088, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0000008C, 0x00000090, 0x00000094, 0x00000098, 0x0000009C, 0x000000A0, 0x000000A4, 0x000000A8, 0xFFFFFFFF, 0x000000A9, 0xFFFFFFFF, 0x000000AA, 0x000000AB, 0x000000AC, 0x00000000, 0xC11CCCCD, 0x00000000, 0x00000000, 0x00000400, 0x3DCCCCCD, 0x43480000, 0x3D088889, 0x3F19999A, 0x00000004, 0x00000001, 0x3C23D70A, 0x00000014, 0x3E4CCCCD, 0x41200000, 0x01010101, 0x38D1B717};

const hkClass hkWorldCinfoClass("hkWorldCinfo", &hkReferencedObjectClass, 0xA0, 0, 0, hkWorldCinfoClass_Enums, 4, hkWorldCinfoClass_Members, 27, hkWorldCinfoClass_Default);
