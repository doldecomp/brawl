#include <havok/hkClass.h>

extern const hkClass hkAnimatedReferenceFrameClass;
extern const hkClass hkReferencedObjectClass;

const hkClass hkAnimatedReferenceFrameClass("hkAnimatedReferenceFrame", &hkReferencedObjectClass, 0x8, 0, 0, 0, 0, 0, 0, 0);
