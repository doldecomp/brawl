#include <havok/hkClass.h>

extern const hkClass hk2dAngConstraintAtomClass;
extern const hkClass hkAngConstraintAtomClass;
extern const hkClass hkAngFrictionConstraintAtomClass;
extern const hkClass hkAngLimitConstraintAtomClass;
extern const hkClass hkAngMotorConstraintAtomClass;
extern const hkClass hkBallSocketConstraintAtomClass;
extern const hkClass hkBridgeAtomsClass;
extern const hkClass hkBridgeConstraintAtomClass;
extern const hkClass hkConeLimitConstraintAtomClass;
extern const hkClass hkConstraintAtomClass;
extern const hkClass hkLinConstraintAtomClass;
extern const hkClass hkLinFrictionConstraintAtomClass;
extern const hkClass hkLinLimitConstraintAtomClass;
extern const hkClass hkLinMotorConstraintAtomClass;
extern const hkClass hkLinSoftConstraintAtomClass;
extern const hkClass hkMassChangerModifierConstraintAtomClass;
extern const hkClass hkModifierConstraintAtomClass;
extern const hkClass hkMovingSurfaceModifierConstraintAtomClass;
extern const hkClass hkOverwritePivotConstraintAtomClass;
extern const hkClass hkPulleyConstraintAtomClass;
extern const hkClass hkRagdollMotorConstraintAtomClass;
extern const hkClass hkSetLocalRotationsConstraintAtomClass;
extern const hkClass hkSetLocalTransformsConstraintAtomClass;
extern const hkClass hkSetLocalTranslationsConstraintAtomClass;
extern const hkClass hkSoftContactModifierConstraintAtomClass;
extern const hkClass hkStiffSpringConstraintAtomClass;
extern const hkClass hkTwistLimitConstraintAtomClass;
extern const hkClass hkViscousSurfaceModifierConstraintAtomClass;
extern const hkClass hkConstraintDataClass;
extern const hkClass hkConstraintMotorClass;

static const hkClassEnumItem hkConstraintAtomAtomTypeEnumItems[] = {
    {0, "TYPE_INVALID"},
    {1, "TYPE_BRIDGE"},
    {2, "TYPE_SET_LOCAL_TRANSFORMS"},
    {3, "TYPE_SET_LOCAL_TRANSLATIONS"},
    {4, "TYPE_SET_LOCAL_ROTATIONS"},
    {5, "TYPE_BALL_SOCKET"},
    {6, "TYPE_STIFF_SPRING"},
    {7, "TYPE_LIN"},
    {8, "TYPE_LIN_SOFT"},
    {9, "TYPE_LIN_LIMIT"},
    {10, "TYPE_LIN_FRICTION"},
    {11, "TYPE_LIN_MOTOR"},
    {12, "TYPE_2D_ANG"},
    {13, "TYPE_ANG"},
    {14, "TYPE_ANG_LIMIT"},
    {15, "TYPE_TWIST_LIMIT"},
    {16, "TYPE_CONE_LIMIT"},
    {17, "TYPE_ANG_FRICTION"},
    {18, "TYPE_ANG_MOTOR"},
    {19, "TYPE_RAGDOLL_MOTOR"},
    {20, "TYPE_PULLEY"},
    {21, "TYPE_OVERWRITE_PIVOT"},
    {22, "TYPE_CONTACT"},
    {23, "TYPE_MODIFIER_SOFT_CONTACT"},
    {24, "TYPE_MODIFIER_MASS_CHANGER"},
    {25, "TYPE_MODIFIER_VISCOUS_SURFACE"},
    {26, "TYPE_MODIFIER_MOVING_SURFACE"},
    {27, "TYPE_MAX"},
};

static const hkClassEnumItem hkConstraintAtomCallbackRequestEnumItems[] = {
    {0, "CALLBACK_REQUEST_NONE"},
    {1, "CALLBACK_REQUEST_CONTACT_POINT"},
    {2, "CALLBACK_REQUEST_SETUP_PPU_ONLY"},
};

static const hkClassEnum hkConstraintAtomClass_Enums[] = {
    {"AtomType", hkConstraintAtomAtomTypeEnumItems, 28},
    {"CallbackRequest", hkConstraintAtomCallbackRequestEnumItems, 3},
};

static const hkClassEnum* hkConstraintAtomClass_Enum0 = &hkConstraintAtomClass_Enums[0];

static const hkClassMember hkConstraintAtomClass_Members[] = {
    {"type", 0, hkConstraintAtomClass_Enum0, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 16, 0x0},
};

const hkClass hkConstraintAtomClass("hkConstraintAtom", 0, 0x2, 0, 0, hkConstraintAtomClass_Enums, 2, hkConstraintAtomClass_Members, 1, 0);

static const hkClassMember hkBridgeConstraintAtomClass_Members[] = {
    {"buildJacobianFunc", 0, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"constraintData", &hkConstraintDataClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x8},
};

const hkClass hkBridgeConstraintAtomClass("hkBridgeConstraintAtom", &hkConstraintAtomClass, 0xC, 0, 0, 0, 0, hkBridgeConstraintAtomClass_Members, 2, 0);

static const hkClassMember hkBridgeAtomsClass_Members[] = {
    {"bridgeAtom", &hkBridgeConstraintAtomClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x0},
};

const hkClass hkBridgeAtomsClass("hkBridgeAtoms", 0, 0xC, 0, 0, 0, 0, hkBridgeAtomsClass_Members, 1, 0);

const hkClass hkBallSocketConstraintAtomClass("hkBallSocketConstraintAtom", &hkConstraintAtomClass, 0x2, 0, 0, 0, 0, 0, 0, 0);

static const hkClassMember hkStiffSpringConstraintAtomClass_Members[] = {
    {"length", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x4},
};

const hkClass hkStiffSpringConstraintAtomClass("hkStiffSpringConstraintAtom", &hkConstraintAtomClass, 0x8, 0, 0, 0, 0, hkStiffSpringConstraintAtomClass_Members, 1, 0);

static const hkClassMember hkSetLocalTransformsConstraintAtomClass_Members[] = {
    {"transformA", 0, 0, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"transformB", 0, 0, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0x50},
};

const hkClass hkSetLocalTransformsConstraintAtomClass("hkSetLocalTransformsConstraintAtom", &hkConstraintAtomClass, 0x90, 0, 0, 0, 0, hkSetLocalTransformsConstraintAtomClass_Members, 2, 0);

static const hkClassMember hkSetLocalTranslationsConstraintAtomClass_Members[] = {
    {"translationA", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"translationB", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x20},
};

const hkClass hkSetLocalTranslationsConstraintAtomClass("hkSetLocalTranslationsConstraintAtom", &hkConstraintAtomClass, 0x30, 0, 0, 0, 0, hkSetLocalTranslationsConstraintAtomClass_Members, 2, 0);

static const hkClassMember hkSetLocalRotationsConstraintAtomClass_Members[] = {
    {"rotationA", 0, 0, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"rotationB", 0, 0, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, 0x40},
};

const hkClass hkSetLocalRotationsConstraintAtomClass("hkSetLocalRotationsConstraintAtom", &hkConstraintAtomClass, 0x70, 0, 0, 0, 0, hkSetLocalRotationsConstraintAtomClass_Members, 2, 0);

static const hkClassMember hkOverwritePivotConstraintAtomClass_Members[] = {
    {"copyToPivotBFromPivotA", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
};

const hkClass hkOverwritePivotConstraintAtomClass("hkOverwritePivotConstraintAtom", &hkConstraintAtomClass, 0x4, 0, 0, 0, 0, hkOverwritePivotConstraintAtomClass_Members, 1, 0);

static const hkClassMember hkLinConstraintAtomClass_Members[] = {
    {"axisIndex", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
};

const hkClass hkLinConstraintAtomClass("hkLinConstraintAtom", &hkConstraintAtomClass, 0x4, 0, 0, 0, 0, hkLinConstraintAtomClass_Members, 1, 0);

static const hkClassMember hkLinSoftConstraintAtomClass_Members[] = {
    {"axisIndex", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"tau", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"damping", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkLinSoftConstraintAtomClass("hkLinSoftConstraintAtom", &hkConstraintAtomClass, 0xC, 0, 0, 0, 0, hkLinSoftConstraintAtomClass_Members, 3, 0);

static const hkClassMember hkLinLimitConstraintAtomClass_Members[] = {
    {"axisIndex", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"min", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"max", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkLinLimitConstraintAtomClass("hkLinLimitConstraintAtom", &hkConstraintAtomClass, 0xC, 0, 0, 0, 0, hkLinLimitConstraintAtomClass_Members, 3, 0);

static const hkClassMember hk2dAngConstraintAtomClass_Members[] = {
    {"freeRotationAxis", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
};

const hkClass hk2dAngConstraintAtomClass("hk2dAngConstraintAtom", &hkConstraintAtomClass, 0x4, 0, 0, 0, 0, hk2dAngConstraintAtomClass_Members, 1, 0);

static const hkClassMember hkAngConstraintAtomClass_Members[] = {
    {"firstConstrainedAxis", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"numConstrainedAxes", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x3},
};

const hkClass hkAngConstraintAtomClass("hkAngConstraintAtom", &hkConstraintAtomClass, 0x4, 0, 0, 0, 0, hkAngConstraintAtomClass_Members, 2, 0);

static const hkClassMember hkAngLimitConstraintAtomClass_Members[] = {
    {"isEnabled", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"limitAxis", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x3},
    {"minAngle", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"maxAngle", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"angularLimitsTauFactor", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xC},
};

static const u32 hkAngLimitConstraintAtomClass_Default[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000014, 0x3F800000};

const hkClass hkAngLimitConstraintAtomClass("hkAngLimitConstraintAtom", &hkConstraintAtomClass, 0x10, 0, 0, 0, 0, hkAngLimitConstraintAtomClass_Members, 5, hkAngLimitConstraintAtomClass_Default);

static const hkClassMember hkTwistLimitConstraintAtomClass_Members[] = {
    {"isEnabled", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"twistAxis", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x3},
    {"refAxis", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"minAngle", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"maxAngle", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xC},
    {"angularLimitsTauFactor", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

static const u32 hkTwistLimitConstraintAtomClass_Default[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000018, 0x3F800000};

const hkClass hkTwistLimitConstraintAtomClass("hkTwistLimitConstraintAtom", &hkConstraintAtomClass, 0x14, 0, 0, 0, 0, hkTwistLimitConstraintAtomClass_Members, 6, hkTwistLimitConstraintAtomClass_Default);

static const hkClassEnumItem hkConeLimitConstraintAtomMeasurementModeEnumItems[] = {
    {0, "ZERO_WHEN_VECTORS_ALIGNED"},
    {1, "ZERO_WHEN_VECTORS_PERPENDICULAR"},
};

static const hkClassEnum hkConeLimitConstraintAtomClass_Enums[] = {
    {"MeasurementMode", hkConeLimitConstraintAtomMeasurementModeEnumItems, 2},
};

static const hkClassEnum* hkConeLimitConstraintAtomClass_Enum1 = &hkConeLimitConstraintAtomClass_Enums[0];

static const hkClassMember hkConeLimitConstraintAtomClass_Members[] = {
    {"isEnabled", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"twistAxisInA", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x3},
    {"refAxisInB", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"angleMeasurementMode", 0, hkConeLimitConstraintAtomClass_Enum1, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, 8, 0x5},
    {"minAngle", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"maxAngle", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xC},
    {"angularLimitsTauFactor", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

static const u32 hkConeLimitConstraintAtomClass_Default[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0000001C, 0x3F800000};

const hkClass hkConeLimitConstraintAtomClass("hkConeLimitConstraintAtom", &hkConstraintAtomClass, 0x14, 0, 0, hkConeLimitConstraintAtomClass_Enums, 1, hkConeLimitConstraintAtomClass_Members, 7, hkConeLimitConstraintAtomClass_Default);

static const hkClassMember hkAngFrictionConstraintAtomClass_Members[] = {
    {"isEnabled", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"firstFrictionAxis", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x3},
    {"numFrictionAxes", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"maxFrictionTorque", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkAngFrictionConstraintAtomClass("hkAngFrictionConstraintAtom", &hkConstraintAtomClass, 0xC, 0, 0, 0, 0, hkAngFrictionConstraintAtomClass_Members, 4, 0);

static const hkClassMember hkAngMotorConstraintAtomClass_Members[] = {
    {"isEnabled", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"motorAxis", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x3},
    {"initializedOffset", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"previousTargetAngleOffset", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x6},
    {"correspondingAngLimitSolverResultOffset", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"targetAngle", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xC},
    {"motor", &hkConstraintMotorClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x10},
};

const hkClass hkAngMotorConstraintAtomClass("hkAngMotorConstraintAtom", &hkConstraintAtomClass, 0x14, 0, 0, 0, 0, hkAngMotorConstraintAtomClass_Members, 7, 0);

static const hkClassMember hkRagdollMotorConstraintAtomClass_Members[] = {
    {"isEnabled", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"initializedOffset", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"previousTargetAnglesOffset", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x6},
    {"targetFrameAinB", 0, 0, hkClassMember::TYPE_MATRIX3, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"motors", &hkConstraintMotorClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 3, 0, 0x40},
};

const hkClass hkRagdollMotorConstraintAtomClass("hkRagdollMotorConstraintAtom", &hkConstraintAtomClass, 0x50, 0, 0, 0, 0, hkRagdollMotorConstraintAtomClass_Members, 5, 0);

static const hkClassMember hkLinFrictionConstraintAtomClass_Members[] = {
    {"isEnabled", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"frictionAxis", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x3},
    {"maxFrictionForce", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x4},
};

const hkClass hkLinFrictionConstraintAtomClass("hkLinFrictionConstraintAtom", &hkConstraintAtomClass, 0x8, 0, 0, 0, 0, hkLinFrictionConstraintAtomClass_Members, 3, 0);

static const hkClassMember hkLinMotorConstraintAtomClass_Members[] = {
    {"isEnabled", 0, 0, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"motorAxis", 0, 0, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0x3},
    {"initializedOffset", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"previousTargetPositionOffset", 0, 0, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0x6},
    {"targetPosition", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"motor", &hkConstraintMotorClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0xC},
};

const hkClass hkLinMotorConstraintAtomClass("hkLinMotorConstraintAtom", &hkConstraintAtomClass, 0x10, 0, 0, 0, 0, hkLinMotorConstraintAtomClass_Members, 6, 0);

static const hkClassMember hkPulleyConstraintAtomClass_Members[] = {
    {"fixedPivotAinWorld", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"fixedPivotBinWorld", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x20},
    {"ropeLength", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x30},
    {"leverageOnBodyB", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x34},
};

const hkClass hkPulleyConstraintAtomClass("hkPulleyConstraintAtom", &hkConstraintAtomClass, 0x40, 0, 0, 0, 0, hkPulleyConstraintAtomClass_Members, 4, 0);

static const hkClassMember hkModifierConstraintAtomClass_Members[] = {
    {"modifierAtomSize", 0, 0, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0x2},
    {"childSize", 0, 0, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0x4},
    {"child", &hkConstraintAtomClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x8},
};

const hkClass hkModifierConstraintAtomClass("hkModifierConstraintAtom", &hkConstraintAtomClass, 0xC, 0, 0, 0, 0, hkModifierConstraintAtomClass_Members, 3, 0);

static const hkClassMember hkSoftContactModifierConstraintAtomClass_Members[] = {
    {"tau", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xC},
    {"maxAcceleration", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

const hkClass hkSoftContactModifierConstraintAtomClass("hkSoftContactModifierConstraintAtom", &hkModifierConstraintAtomClass, 0x20, 0, 0, 0, 0, hkSoftContactModifierConstraintAtomClass_Members, 2, 0);

static const hkClassMember hkMassChangerModifierConstraintAtomClass_Members[] = {
    {"factorA", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0xC},
    {"factorB", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

const hkClass hkMassChangerModifierConstraintAtomClass("hkMassChangerModifierConstraintAtom", &hkModifierConstraintAtomClass, 0x20, 0, 0, 0, 0, hkMassChangerModifierConstraintAtomClass_Members, 2, 0);

const hkClass hkViscousSurfaceModifierConstraintAtomClass("hkViscousSurfaceModifierConstraintAtom", &hkModifierConstraintAtomClass, 0x10, 0, 0, 0, 0, 0, 0, 0);

static const hkClassMember hkMovingSurfaceModifierConstraintAtomClass_Members[] = {
    {"velocity", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

const hkClass hkMovingSurfaceModifierConstraintAtomClass("hkMovingSurfaceModifierConstraintAtom", &hkModifierConstraintAtomClass, 0x20, 0, 0, 0, 0, hkMovingSurfaceModifierConstraintAtomClass_Members, 1, 0);

