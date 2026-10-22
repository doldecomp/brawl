#ifndef RVL_SDK_OS_LINK_H
#define RVL_SDK_OS_LINK_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

struct OSModuleHeader {
    u32 id;
    u32 linkNext;
    u32 linkPrev;
    u32 numSections;
    u32 sectionInfoOffset;
    u32 nameOffset;
    u32 nameSize;
    u32 version;

    u32 bssSize;
    u32 relOffset;
    u32 impOffset;
    u32 impSize;

    char prologSection;
    char epilogSection;
    char unresolvedSection;
    char bssSection;

    u32 prologOffset;
    u32 epilogOffset;
    u32 unresolvedOffset;

    u32 moduleAlign;
    u32 bssAlign;

    u32 commandOffset;
};

void __OSModuleInit(void);

bool OSUnlink(OSModuleHeader* module);

#ifdef __cplusplus
}
#endif
#endif
