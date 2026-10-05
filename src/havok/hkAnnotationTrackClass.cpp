#include <havok/hkClass.h>

extern const hkClass hkAnnotationTrackAnnotationClass;
extern const hkClass hkAnnotationTrackClass;

static const hkClassMember hkAnnotationTrackAnnotationClass_Members[] = {
    {"time", 0, 0, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"text", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x4},
};

const hkClass hkAnnotationTrackAnnotationClass("hkAnnotationTrackAnnotation", 0, 0x8, 0, 0, 0, 0, hkAnnotationTrackAnnotationClass_Members, 2, 0);

static const hkClassMember hkAnnotationTrackClass_Members[] = {
    {"name", 0, 0, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0x0},
    {"annotations", &hkAnnotationTrackAnnotationClass, 0, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0x4},
};

const hkClass hkAnnotationTrackClass("hkAnnotationTrack", 0, 0xC, 0, 0, 0, 0, hkAnnotationTrackClass_Members, 2, 0);
