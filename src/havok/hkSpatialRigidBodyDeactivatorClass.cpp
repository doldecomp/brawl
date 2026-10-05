#include <havok/hkClass.h>

extern const hkClass hkSpatialRigidBodyDeactivatorClass;
extern const hkClass hkSpatialRigidBodyDeactivatorSampleClass;
extern const hkClass hkRigidBodyDeactivatorClass;

static const hkClassMember hkSpatialRigidBodyDeactivatorSampleClass_Members[] = {
    {"refPosition", 0, 0, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"refRotation", 0, 0, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0x10},
};

const hkClass hkSpatialRigidBodyDeactivatorSampleClass("hkSpatialRigidBodyDeactivatorSample", 0, 0x20, 0, 0, 0, 0, hkSpatialRigidBodyDeactivatorSampleClass_Members, 2, 0);

static const hkClassMember hkSpatialRigidBodyDeactivatorClass_Members[] = {
    {"highFrequencySample", &hkSpatialRigidBodyDeactivatorSampleClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x10},
    {"lowFrequencySample", &hkSpatialRigidBodyDeactivatorSampleClass, 0, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0x30},
    {"radiusSqrd", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x50},
    {"minHighFrequencyTranslation", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x54},
    {"minHighFrequencyRotation", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x58},
    {"minLowFrequencyTranslation", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x5C},
    {"minLowFrequencyRotation", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x60},
};

const hkClass hkSpatialRigidBodyDeactivatorClass("hkSpatialRigidBodyDeactivator", &hkRigidBodyDeactivatorClass, 0x70, 0, 0, 0, 0, hkSpatialRigidBodyDeactivatorClass_Members, 7, 0);
