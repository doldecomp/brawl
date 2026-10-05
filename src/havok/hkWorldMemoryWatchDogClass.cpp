#include <havok/hkClass.h>

extern const hkClass hkWorldMemoryWatchDogClass;
extern const hkClass hkReferencedObjectClass;

static const hkClassMember hkWorldMemoryWatchDogClass_Members[] = {
    {"memoryLimit", 0, 0, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0x8},
};

const hkClass hkWorldMemoryWatchDogClass("hkWorldMemoryWatchDog", &hkReferencedObjectClass, 0xC, 0, 0, 0, 0, hkWorldMemoryWatchDogClass_Members, 1, 0);
