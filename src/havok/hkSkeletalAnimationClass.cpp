#include <havok/hkClass.h>

extern const hkClass hkSkeletalAnimationClass;
extern const hkClass hkAnimatedReferenceFrameClass;
extern const hkClass hkAnnotationTrackClass;
extern const hkClass hkReferencedObjectClass;

static const hkClassMember hkSkeletalAnimationClass_Members[] = {
    {"duration", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x8},
    {"numberOfTracks", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0xC},
    {"extractedMotion", &hkAnimatedReferenceFrameClass, 0, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0x10},
    {"annotationTracks", &hkAnnotationTrackClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0x14},
};

const hkClass hkSkeletalAnimationClass("hkSkeletalAnimation", &hkReferencedObjectClass, 0x1C, 0, 0, 0, 0, hkSkeletalAnimationClass_Members, 4, 0);
